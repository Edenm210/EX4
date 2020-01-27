//
// Created by eden on 16/01/2020.
//

#ifndef EX4__SEARCHABLEGRAPH_H_
#define EX4__SEARCHABLEGRAPH_H_

#include <string>
#include "State.h"
#include "ISearchable.h"
#include "Graph.h"

/**
 * Searchable Interface
 */
template<class T> // values type in the graph

class SearchableGraph : public ISearchable<T> {
 private:
  vector<vector<State<T> *>> matrix;

  State<T> *initialState;
  State<T> *goalState;

 public:
  //CONSTRUCTOR
  SearchableGraph(vector<string> vec) {
    Graph<T> *g = new Graph<T>(vec); // string matrix
    SearchableGraph::createGraph(g);
  }

  void setBackTheCostInPathToInitial() {
    for (int i = 0; i < this->matrix.size(); i++) {
      for (int j = 0; j < this->matrix[i].size(); j++) {
        State<T> *st = (this->matrix.at(i)).at(j);
        st->startCostInPath();
      }
    }
  }

  State<T> *getInitialState() {
    return this->initialState;
  }

  void setInitialState(State<T> **state) {
    this->initialState = *state;
  }

  void setGoalState(State<T> **state) {
    this->goalState = *state;
  }

  bool isGoalState(State<T> *state) {
    return (this->goalState->isEqualTo(state));
  }

  State<T> *getGoalState() {
    return this->goalState;
  }

  virtual vector<State<T> *> getAllPossibleStates(State<T> *s) {
    return s->getNeighbors();
  }

  void createGraph(Graph<T> *g) {
    int rows_num = g->getNumOfRows();
    int columns_num = g->getNumOfColumns();
    vector<vector<string>> string_matrix = g->getStringMatrix();

    for (int i = 0; i < rows_num; i++) {
      vector<State<T> *> line;
      this->matrix.push_back(line); //inserting a vector to the matrix so we can edit it inside
      for (int j = 0; j < columns_num; j++) {
        double val = stod(string_matrix.at(i).at(j));
        State<T> *st = new State<T>(make_pair(i, j), val);
        this->matrix.at(i).push_back(st);
      }
    }

    // filling the neighbores
    for (int i = 0; i < rows_num; i++) {
      for (int j = 0; j < columns_num; j++) {
        State<T> *st = (this->matrix.at(i)).at(j);

        if (st->getValue()==-1) {
          continue; // not filling any neighbore
        }
        if (j - 1 >= 0) {
          st->addNeighbor(this->matrix[i][j - 1]);
        }
        if (j + 1 < columns_num) {
          st->addNeighbor(this->matrix[i][j + 1]);
        }
        if (i + 1 < rows_num) {
          st->addNeighbor(this->matrix[i + 1][j]);
        }
        // checking neighbores in limits
        if (i - 1 >= 0) {
          st->addNeighbor(this->matrix[i - 1][j]);
        }
      }
    }

    int indexI = stoi(string_matrix.at(rows_num).at(0));
    int indexJ = stoi(string_matrix.at(rows_num).at(1));
    if ((indexI >= 0 && indexI < rows_num) && (indexJ >= 0 && indexJ < columns_num)) {
      State<T> *p = this->matrix.at(indexI).at(indexJ);
      this->setInitialState(&p);
    } else {
      std::cerr << "the initial point inserted is invalid" << std::endl;
    }

    indexI = stoi(string_matrix.at(rows_num + 1).at(0));
    indexJ = stoi(string_matrix.at(rows_num + 1).at(1));
    if ((indexI >= 0 && indexI < rows_num) && (indexJ >= 0 && indexJ < columns_num)) {
      State<T> *p2 = this->matrix.at(indexI).at(indexJ);
      this->setGoalState(&p2);
    } else {
      std::cerr << "the goal point inserted is invalid" << std::endl;
    }
  }

};

#endif //EX4__SEARCHABLEGRAPH_H_
