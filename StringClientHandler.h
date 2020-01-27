//
// Created by eden on 14/01/2020.
//

#ifndef EX4__STRINGCLIENTHANDLER_H_
#define EX4__STRINGCLIENTHANDLER_H_

#include <zconf.h>
#include "ClientHandler.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include <cstring>
#include <sys/socket.h>

template<typename P, typename S> //template T object
class StringClientHandler : public ClientHandler {
 private:
  Solver<P, S> *solver;
  CacheManager<S> *cache_manager_;
  S solution;

 public:
  StringClientHandler(Solver<P, S> *s, CacheManager<S> *cm) {
    this->solver = s;
    this->cache_manager_ = cm;
  };

  ~StringClientHandler() {
    delete this->solver;
    delete this->cache_manager_;
  }

  void handleClient(int client_socket) override {
    int j = 0;
    string allData = "";
    string token = "";
    char buffer[2048] = {0};

    int valread;
    //receives data from the client
    while (token.compare("end")!=0) {
      valread = read(client_socket, buffer, 1024);
      j = 0;
      while (buffer[j]!='\n' && buffer[j]!='\r') {
        token.append(1, buffer[j]);
        j++;
      }

      if (token.compare("end")!=0) {
        if (this->cache_manager_->existInCache(token)) //the solution exists in cache
        {
          this->solution = this->cache_manager_->get(token);
        } else {
          // sending to solver to solve the problem
          this->solution = this->solver->solve(token);
          cache_manager_->insert(token, this->solution); // updating the cache

          string s = this->solution.append("\n");
          char cstr[s.size() + 1];
          strcpy(cstr, s.c_str());

          //sends the solution string to server
          send(client_socket, cstr, strlen(cstr), 0);
        }
      } else {
        break;
      }
      token.clear();
    }
  }

  ClientHandler* copyClient() override{};

};

#endif //EX4__STRINGCLIENTHANDLER_H_
