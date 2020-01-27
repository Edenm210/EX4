//
// Created by eden on 14/01/2020.
//

#ifndef EX4__SERVER_H_
#define EX4__SERVER_H_

/**
 * Server Interface
 */
#include <netinet/in.h>
#include "ClientHandler.h"

namespace server_side {
class Server {
 protected:
  int portNum;
  int socketfd;
  int client_socket;
  sockaddr_in address;

 public:
  //getting port to listen to, opens the server and waiting for clients
  virtual int open(int port, ClientHandler &client_handler) = 0;
  //closes the server
  virtual void stop() = 0;
};

}

#endif //EX4__SERVER_H_
