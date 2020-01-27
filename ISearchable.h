//
// Created by eden on 19/01/2020.
//

#ifndef EX4__ISEARCHABLE_H_
#define EX4__ISEARCHABLE_H_

#include "State.h"

template<class T>
class ISearchable {
 public:
  virtual State<T> *getInitialState() = 0;
  virtual bool isGoalState(State<T> *state) = 0;
  virtual State<T> *getGoalState() = 0;
  virtual vector<State<T> *> getAllPossibleStates(State<T> *s) = 0;
  virtual void setBackTheCostInPathToInitial() = 0;
  virtual ~ISearchable() {}
};

#endif //EX4__ISEARCHABLE_H_
