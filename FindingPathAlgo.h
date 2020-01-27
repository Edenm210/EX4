//
// Created by eden on 19/01/2020.
//

#ifndef EX4__FINDINGPATHALGO_H_
#define EX4__FINDINGPATHALGO_H_

#include <queue>
#include "ISearcher.h"
template<class P>
//"abstract class" for searching alogs

class FindingPathAlgo : public ISearcher<P,vector<State<P>*>>{
 protected:
  int numOfEvaluatedNodes;
  P pathCost;
  vector<State<P>*> path;

 public:
  FindingPathAlgo() {
    this->numOfEvaluatedNodes = 0;
    this->pathCost = {}; // initialization
    this->path= {};
  }

  virtual FindingPathAlgo* copySearcher()=0;

  int getNumberOfNodesEvaluated(){
    return this->numOfEvaluatedNodes;
  }

  void buildPath(State<P> *init, State<P> *goal){
    this->path.clear();
    vector<State<P>*> upsidePath;
    this->pathCost=goal->getCostInPath();

    while(!(goal->isEqualTo(init))){

      upsidePath.push_back(goal);
      goal = goal->getFather();
    }
    upsidePath.push_back(goal);


    for(int i = upsidePath.size() - 1; i >= 0; i--){
      this->path.push_back(upsidePath[i]);
    }
  }







  //virtual vector<State<P>>* search(SearchableGraph<P> searchable) = 0;

};

#endif //EX4__FINDINGPATHALGO_H_
