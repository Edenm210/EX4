//
// Created by eden on 14/01/2020.
//

#ifndef EX4__MYSERIALSERVER_H_
#define EX4__MYSERIALSERVER_H_

#include <thread>
#include "Server.h"

class MySerialServer : public server_side::Server {
 private:
  ClientHandler *client_handler_;

  int portNum;
  int socketfd;

 public:
  MySerialServer();

  ~MySerialServer() {
    delete client_handler_;
  };



  int open(int port, ClientHandler &client_handler) override;

  int initServer();
  //closes the server
  void stop() override;
  int acceptClient(sockaddr_in address, int socketfd);

};

#endif //EX4__MYSERIALSERVER_H_
