//
// Created by eden on 23/01/2020.
//

#ifndef PROJECTFOUR__MYPARALLELSERVER_H_
#define PROJECTFOUR__MYPARALLELSERVER_H_

#include <stack>
#include <thread>
#include "Server.h"

using namespace std;


class MyParallelServer : public server_side::Server {
 private:
  thread thread_server;

  ClientHandler *client_handler_;
  bool stopBool = false;


 public:
  MyParallelServer();

  ~MyParallelServer() {
    delete client_handler_;
  };

  void startClients(int client_socket);

  void start();

  int open(int port, ClientHandler &client_handler) override;

  int initServer();
  //closes the server
  void stop() override;
  void acceptClient(sockaddr_in address, int socketfd);

};

#endif //PROJECTFOUR__MYPARALLELSERVER_H_
