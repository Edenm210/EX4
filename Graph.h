//
// Created by eden on 16/01/2020.
//

#ifndef EX4__GRAPH_H_
#define EX4__GRAPH_H_

using namespace std;

#include <vector>
#include <string>
#include <iostream>
#include "State.h"

//the type of the values
template<class T>
class Graph{

 private:
  vector<vector<string>> stringMatrix;

  int numOfRows;
  int numOfColumns;

 public:
  Graph(vector<string> vec) {
    for (int i = 0; i < vec.size(); i++) {
      addRow(vec.at(i));
    }
    this->numOfRows = this->stringMatrix.size() - 2;
    this->numOfColumns = this->stringMatrix.at(0).size();
  };

  void addRow(string s) {
    vector<string> temp;
    int len = s.length();
    int i = 0, j;
    while (i < len) {
      if (s.at(i)==' ' || s.at(i)==',') {
        i++;
        continue;
      } else {
        j = i;
        string ch = "";
        while (s.at(j)!=' ' && s.at(j)!=',') {
          ch += (s.at(j));
          j++;
          if (j==len) {
            break;
          }
        }
        temp.push_back(ch);
      }
      i = j;
    }
    if (s!="" && s.compare("\r")!=0) {
      this->stringMatrix.push_back(temp);
    }
  }

  int getNumOfRows() {
    return this->numOfRows;
  }

  int getNumOfColumns() {
    return this->numOfColumns;
  }

  vector<vector<string>> getStringMatrix() {
    return this->stringMatrix;
  }

};

#endif //EX4__GRAPH_H_
