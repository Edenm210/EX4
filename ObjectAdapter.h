//
// Created by eden on 16/01/2020.
//

#ifndef EX4__OBJECTADAPTER_H_
#define EX4__OBJECTADAPTER_H_

#include <vector>
#include "Solver.h"
#include "ISearcher.h"
#include "Graph.h"
template<class T> // problem type

class ObjectAdapter : public Solver<vector<string>, string> {
 private:
  ISearcher<T, vector<State<T> *>> *searcher;

 public:
  ObjectAdapter(ISearcher<T, vector<State<T> *>> *searcherObj) {
    this->searcher = searcherObj;
  }

  string solve(vector<string> matrix) override {
    ISearchable<T> *searchable = new SearchableGraph<T>(matrix);
    vector<State<T> *> solutionPath = this->searcher->search(searchable);
    if (solutionPath.empty()) {
      searchable->setBackTheCostInPathToInitial();
      return "No Path Found\n";
    } else {
      string strTemp = converPathToString(solutionPath);
      searchable->setBackTheCostInPathToInitial();

      return strTemp;
    }
  }

  string converPathToString(vector<State<T> *> s) {
    string solution = "";
    T cost = {};
    State<T> *prev = s[0];
    for (int i = 1; i < s.size(); i++) {
      if (s[i]->getLocation().first > prev->getLocation().first) {
        solution += "Down ";
      } else if (s[i]->getLocation().first < prev->getLocation().first) {
        solution += "Up ";
      } else if (s[i]->getLocation().second < prev->getLocation().second) {
        solution += "Left ";
      } else {
        solution += "Right ";
      }
      solution += "(" + to_string((int) s[i]->getCostInPath()) + ")";

      // if this is not the last node add ","
      if (i!=s.size() - 1) {
        solution += " ,";
      }
      prev = s[i];

    }
    return solution;
  }

  string getSolverName() {
    return this->searcher->getSearcherName();
  }

  Solver *copySolver() override {
    ObjectAdapter *b = new ObjectAdapter(this->searcher->copySearcher());
    return b;
  }

  ~ObjectAdapter() {
    delete this->searcher;
  }

};

#endif //EX4__OBJECTADAPTER_H_
