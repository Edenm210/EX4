

//
// Created by eden on 14/01/2020.
//

#ifndef EX4__MATRIXCLIENTHANDLER_H_
#define EX4__MATRIXCLIENTHANDLER_H_

#include <zconf.h>
#include "ClientHandler.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "Graph.h"
#include "SearchableGraph.h"
#include <cstring>
#include <vector>

class MatrixClientHandler : public ClientHandler {
 private:
  Solver<vector<string>, string> *solver;
  CacheManager<string> *cache_manager_;
  string solution;

 public:
  MatrixClientHandler(Solver<vector<string>, string> *s, CacheManager<string> *cm) :
      solver(s), cache_manager_(cm) {}

  MatrixClientHandler() {};

  ~MatrixClientHandler() {
    delete this->solver;
    delete this->cache_manager_;
  }

  ClientHandler *copyClient() {
    return new MatrixClientHandler(this->solver->copySolver(), this->cache_manager_);
  }

  void handleClient(int client_socket) override {
    char buffer[1024] = {0};
    vector<string> matrix;
    int j = 0;
    string token = "";
    string bufferStr;
    bool finisheRead = false;

    int valread;
    while (!finisheRead) {
      char buffer[1024] = {0};
      //receives data from the client
      valread = read(client_socket, buffer, 1024);
      if (valread==-1) {
        std::cerr << "Could not read from client" << std::endl;
      }
      bufferStr = buffer;

      for (int i = 0; i < bufferStr.length(); i++) {
        if (bufferStr[i]=='e') {
          finisheRead = true;
          break;
        } else {
          if (bufferStr[i]=='\n' || bufferStr[i]=='\r') {
            if (token!="") {
              matrix.push_back(token);
              token = "";
            } else {
              continue;
            }
          } else {
            token.append(1, buffer[i]);

          }
        }
      }
    }

    // creating a string so we can send it to hash
    string allString = "";
    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[i].size(); j++) {
        allString += to_string(matrix[i][j]) + ",";
      }
      allString += ";";
    }
    allString += ";";

    ///HASHING
    std::size_t str_hashed = std::hash<std::string>{}(allString);
    allString = to_string(str_hashed);

    allString.append("_" + this->solver->getSolverName());

    if (this->cache_manager_->existInCache(allString)) {
      this->solution = this->cache_manager_->get(allString);
      int isSend = write(client_socket, this->solution.c_str(), this->solution.length());

    } else {
      this->solution = this->solver->solve(matrix);
      if (this->solution=="") {
        this->solution = "There is no solution";
      }
      this->cache_manager_->insert(allString, this->solution);

      int isSend = write(client_socket, this->solution.c_str(), this->solution.length());
      if (isSend==-1) {
        std::cout << "Error sending message" << std::endl;
      }
    }
  }

};

#endif //EX4__MATRIXCLIENTHANDLER_H_
