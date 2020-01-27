//
// Created by eden on 14/01/2020.
//

#ifndef EX4__SOLVER_H_
#define EX4__SOLVER_H_

#include "CacheManager.h"
template <class P, class S>

class Solver {

 public:
  virtual S solve(P problem)=0;

  virtual Solver* copySolver()=0;

  virtual string getSolverName()=0;

};

#endif //EX4__SOLVER_H_
