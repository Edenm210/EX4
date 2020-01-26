//
// Created by eden on 20/01/2020.
//

#ifndef EX4__BESTFIRSTSEARCH_H_
#define EX4__BESTFIRSTSEARCH_H_

#include "FindingPathAlgo.h"
#include <set>

template<class P> // the type of the problem
class BestFirstSearch : public FindingPathAlgo<P> {

  class Compare {
   public:
    bool operator()(State<P> *left, State<P> *right) {
      return (left->getCostInPath()) > (right->getCostInPath());
    }
  };

 private:
  std::priority_queue<State<P> *, vector<State<P> *>, Compare> openNodes;
  std::set<pair<P, P>> closedNodes;

 public:
  BestFirstSearch() : FindingPathAlgo<P>() {
    this->closedNodes = {};
  }

  vector<State<P> *> search(ISearchable<P> *searchable) override {

    this->clearInfo(); // clearing all information from previous rounds

    State<P> *initial = searchable->getInitialState();

    this->openNodes.push(initial); // inserting the initial vertex to openList

    while (!this->openNodes.empty()) {
      // removing minimum node from priority queue
      State<P> *minNode = this->popOpenPrioQ();
      this->closedNodes.insert(minNode->getLocation()); // inserting the node to the visited

      if (searchable->isGoalState(minNode) && (searchable->getGoalState()->getValue() !=-1)) { // we reached to the goal node
        this->buildPath(initial, searchable->getGoalState());

        break;
      } else { // neighbors
        vector<State<P> *> neighbors = searchable->getAllPossibleStates(minNode);
        for (int i = 0; i < neighbors.size(); i++) {
          State<P> *neigh = neighbors.at(i);
          P newCost = neigh->getValue() + minNode->getCostInPath();

          if ((!inClosedList(neigh)) && (!inOpenQueue(neigh))) { // not in closed and not in open
            neigh->setFather(minNode);
            neigh->setCostInPath(newCost);
            this->openNodes.push(neigh);
          } else if (!(inClosedList(neigh))) {
            if (neigh->getCostInPath() > newCost) {
              neigh->setFather(minNode);
              neigh->setCostInPath(newCost);
              updateOpenQueue(neigh);
            }
          }

        }
      }
    }

    return this->path;
  }

  void updateOpenQueue(State<P> *node) {

    priority_queue<State<P> *, vector<State<P> *>, Compare> temp;
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

  std::string getSearcherName() {
    return "BestFirstSearch";
  }

  FindingPathAlgo<P> *copySearcher() {
    return new BestFirstSearch<P>();
  }

  void clearInfo() {
    this->closedNodes.clear();
    this->numOfEvaluatedNodes = 0;
    this->pathCost = 0;
    this->path.clear();
    while (!this->openNodes.empty()) {
      this->openNodes.pop();
    }
  }

};

#endif //EX4__BESTFIRSTSEARCH_H_
