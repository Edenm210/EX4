//
// Created by eden on 23/01/2020.
//

#ifndef PROJECTFOUR__ASTAR_H_
#define PROJECTFOUR__ASTAR_H_

#include <queue>
#include <set>
#include "FindingPathAlgo.h"

using namespace std;
template<class P> // the type of the problem

class Astar : public FindingPathAlgo<P> {

  class CompareStar {
   public:
    bool operator()(State<P> *left, State<P> *right) {
      return ((left->getFvalue()) > (right->getFvalue()));
    }
  };

 private:
  std::priority_queue<State<P> *, vector<State<P> *>, CompareStar> openNodes;
  std::set<pair<P, P>> closedNodes;

  /// g - from initial to current node - CostInPath
  /// h - from current to destination node -
  /// f = g + h

 public:
  Astar() : FindingPathAlgo<P>() {
    this->closedNodes = {};
  }

  std::string getSearcherName() {
    return "Astar";
  }


  vector<State<P> *> search(ISearchable<P> *searchable) override {
    State<P> *goal = searchable->getGoalState();

    this->clearInfo(); // clearing all information from previous rounds

    State<P> *initial = searchable->getInitialState();

    this->openNodes.push(initial); // inserting the initial vertex to openList
    initial->setFvalue(0);

    while (!this->openNodes.empty()) {
      // removing minimum node from priority queue
      State<P> *minNode = this->popOpenPrioQ();

      if (searchable->isGoalState(minNode) && (searchable->getGoalState()->getValue() !=-1)) { // we reached to the goal node
        this->buildPath(initial, searchable->getGoalState());

        break;

      } else {
        this->closedNodes.insert(minNode->getLocation()); // inserting the node to the visited

        vector<State<P> *> neighbors = searchable->getAllPossibleStates(minNode);
        for (int i = 0; i < neighbors.size(); i++) {
          State<P> *neigh = neighbors.at(i);
          P newCost = neigh->getValue() + minNode->getCostInPath();

          // if the node is a block or in the closed list - do nothing
          if (neigh->getValue()==-1 || inClosedList(neigh)) {
            continue;
          } else {
            if ((!inOpenQueue(neigh))){ // not in open queue
              neigh->setCostInPath(newCost);
              neigh->setFather(minNode);
              calculatingF(neigh, searchable->getInitialState());
              this->openNodes.push(neigh);

            } else { // already in queue
              if (neigh->getCostInPath() > newCost) {
                neigh->setFather(minNode);
                neigh->setCostInPath(newCost);
                calculatingF(neigh, searchable->getInitialState());
                updateOpenQueue(neigh); // updating the queue order
              }

            }

          }

        }

      }
    }
    return this->path;
  }

  P calculatingH(State<P> *currentNode, State<P> *goalNode) {
    P left = abs(currentNode->getLocation().first - goalNode->getLocation().first);
    P right = abs(currentNode->getLocation().second - goalNode->getLocation().second);

    return (left + right);
  }

  void calculatingF(State<P> *node, State<P> *goalNode) {
    P g_val = node->getCostInPath();
    P h_val = calculatingH(node, goalNode);
    node->setFvalue(g_val+h_val);
  }

  void updateOpenQueue(State<P> *node) {
    priority_queue<State<P> *, vector<State<P> *>, CompareStar> temp;
    while (!this->openNodes.empty()) {
      temp.push(this->openNodes.top());
      this->openNodes.pop();
    }

    while (!temp.empty()) {
      this->openNodes.push(temp.top());
      temp.pop();
    }
  }

  bool inOpenQueue(State<P> *node) {
    bool exist = false;
    //int index = -1;
    vector<State<P> *> temp = {};
    while (!this->openNodes.empty()) {
      temp.push_back(this->openNodes.top());
      this->openNodes.pop();
    }

    for (int i = 0; i < temp.size(); i++) {
      if (temp.at(i)->isEqualTo(node)) {
        exist = true;
      }
      this->openNodes.push(temp.at(i)); // moving it back to the queue
    }
    return exist;
  }

  bool inClosedList(State<P> *node) {
    return this->closedNodes.find(node->getLocation())!=this->closedNodes.end();
  }

  State<P> *popOpenPrioQ() {
    this->numOfEvaluatedNodes++;
    State<P> *node = this->openNodes.top();
    this->openNodes.pop();
    return node;
  }

  FindingPathAlgo<P>* copySearcher(){
    return new Astar<P>();
  }

  void clearInfo() {
    this->closedNodes.clear();
    this->numOfEvaluatedNodes=0;
    this->pathCost = 0;
    this->path.clear();
    while (!this->openNodes.empty()) {
      this->openNodes.pop();
    }
  }

};

#endif //PROJECTFOUR__ASTAR_H_
