//
// Created by eden on 15/01/2020.
//

#ifndef EX4__STRINGREVERSER_H_
#define EX4__STRINGREVERSER_H_

#include "Solver.h"
#include <string>


class StringReverser : public Solver<string, string> {
 public:
  StringReverser(){};

  static string reverseStr(string &s);

  string solve(string problem) override;

  Solver* copySolver() override{};

  string getSolverName() override{
    return "stringReverse";
  };

  };

#endif //EX4__STRINGREVERSER_H_
