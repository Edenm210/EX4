//
// Created by eden on 16/01/2020.
//

#ifndef EX4__STATE_H_
#define EX4__STATE_H_

#include <utility>
#include <vector>
using namespace std;

template<class T>
class State {
 private:
  pair<T, T> location;
  T value;
  T costInPath;
  State<T> *father;
  vector<State<T> *> neighbors;
  T fValue; // value for A star Algo


 public:
  // constructor
  State(pair<T, T> loc, T val) {
    this->location = loc;
    this->father = nullptr;
    this->value = val;
    this->costInPath = val;
    this->fValue = -1;
  }

  void addNeighbor(State<T> *s) {
    this->neighbors.push_back(s);
  }

  void setFather(State<T> *st) {
    this->father = st;
  }

  void setFvalue(T newVal) {
    this->fValue = newVal;
  }

  T getFvalue() {
    return this->fValue;
  }

   T getCostInPath(){
    return this->costInPath;
  };

  void setCostInPath(T newCost) {
    this->costInPath = newCost;
  };

  void startCostInPath() { // set back the cost in path
    this->costInPath = this->getValue();
  };

  State<T> *getFather() {
    return this->father;
  }

  vector<State<T> *> getNeighbors() {
    return this->neighbors;
  }

  T getValue() {
    return this->value;
  }

  pair<T, T> getLocation() {
    return this->location;
  }

  bool isEqualTo(State<T> *node) {
    return (this->getLocation().first==node->getLocation().first) &&
        (this->getLocation().second==node->getLocation().second);
  }

  ~State() {
    delete this->father;
  }
};

#endif //EX4__STATE_H_
