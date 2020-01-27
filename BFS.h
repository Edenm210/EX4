//
// Created by eden on 19/01/2020.
//

#ifndef EX4__BFS_H_
#define EX4__BFS_H_

#include <set>
#include "FindingPathAlgo.h"

using namespace std;

template<class P> // the type of the problem

class BFS : public FindingPathAlgo<P> {
 private:
  queue<State<P>*> openNodes;
  std::set<pair<P, P>> alreadyVisited;

 public:
  // calling the father constructor
  BFS() : FindingPathAlgo<P>() {
    this->alreadyVisited={};
    this->openNodes={};
  }

  vector<State<P> *> search(ISearchable<P> *searchable) override {
    this->clearInfo(); // clearing all information from previous rounds
    State<P> *initial = searchable->getInitialState();

    this->alreadyVisited.insert(initial->getLocation()); // the initial vertex visited
    this->openNodes.push(initial); // inserting the initial vertex to openList

    while (!this->openNodes.empty()) {
      // removing node from the queue
      State<P> *minNode = this->popOpenQueue();

      if (searchable->isGoalState(minNode) && (searchable->getGoalState()->getValue() !=-1)) { // we reached to the goal node
        this->buildPath(initial,searchable->getGoalState());
        break;
      } else {
        vector<State<P> *> neighbors = searchable->getAllPossibleStates(minNode);
        for (int i = 0; i < neighbors.size(); i++) {
          State<P>* neigh = neighbors.at(i);
          // the node not visited
          if(!nodeHasBeenVisited(neigh)) {
            //this->pathCost+=neigh->getValue();

            this->alreadyVisited.insert(neigh->getLocation()); // inserting the node to the visited
            neigh->setFather(minNode);
            neigh->setCostInPath(neigh->getValue()+neigh->getFather()->getCostInPath());
            this->openNodes.push(neigh); // inserting to openList

          }
        }
      }
    }

    return this->path;
  }

  bool nodeHasBeenVisited(State<P> *node) {
    // the node is in alreadyVisited
    return this->alreadyVisited.find(node->getLocation())!=this->alreadyVisited.end();
  }

  State<P>* popOpenQueue() {
    this->numOfEvaluatedNodes++;
    State<P>* node = this->openNodes.front();
    this->openNodes.pop();
    return node;
  }

  std::string getSearcherName() {
    return "BFS";
  }

  FindingPathAlgo<P>* copySearcher(){
    return new BFS<P>();
  }

  void clearInfo() {
    this->alreadyVisited.clear();
    this->numOfEvaluatedNodes=0;
    this->pathCost = 0;
    this->path.clear();
    while (!this->openNodes.empty()) {
      this->openNodes.pop();
    }
  }
};

#endif //EX4__BFS_H_


