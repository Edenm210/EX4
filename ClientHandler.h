//
// Created by eden on 14/01/2020.
//

#ifndef EX4__CLIENTHANDLER_H_
#define EX4__CLIENTHANDLER_H_
#include <iostream>

using namespace std;

/**
 * ClientHandler Interface
 */
class ClientHandler {

 public:
  virtual void handleClient(int client_socket)=0;

  virtual ClientHandler* copyClient()=0;

};


#endif //EX4__CLIENTHANDLER_H_
