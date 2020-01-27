//
// Created by eden on 15/01/2020.
//

#include "StringReverser.h"

string StringReverser::solve(string problem) {
  return StringReverser::reverseStr(problem);
}

// Function to reverse a string
string StringReverser::reverseStr(string &s) {
  string rev;
  for (int i = s.size() - 1; i >= 0; i--) {
    rev = rev.append(1, s[i]);
  };

  return rev;
}

