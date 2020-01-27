//
// Created by eden on 23/01/2020.
//

#include <unistd.h>
#include "MyParallelServer.h"

#define TRUE   1

struct client_information {
  int socket;
  ClientHandler *clientHandler;
};

int MyParallelServer::open(int port, ClientHandler &client_handler) {
  this->client_handler_ = &client_handler;
  int run;
  this->portNum = port;
  //blocks until server is connected
  run = initServer();
  while (run!=0) {
    run = initServer();
  }

  ///It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection
  if (listen(socketfd, 10)==-1) {
    std::cerr << "Error during listening command" << std::endl;
    return -3;
  }
  cout << "Server is now listening..." << endl;

  start();

}

int MyParallelServer::initServer() {

  /// socket creation
  this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd==-1) {
    //error
    std::cerr << "Could not create a socket" << std::endl;
    return -1;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(portNum);

  /// bind function binds the socket to the address and port number specified in &address
  if (bind(socketfd, (struct sockaddr *) &address, sizeof(address))==-1) {
    std::cerr << "Could not bind the socket to an IP" << std::endl;
    return -2;
  }

  cout << "Server Connected" << endl;

  return 0;
}

MyParallelServer::MyParallelServer() {};

void MyParallelServer::acceptClient(sockaddr_in address, int socketfd) {

  while (!this->stopBool) {

    /// extracts the first connection request on the queue of pending connections for the listening socket, sockfd,
    /// creates a new connected socket, and returns a new file descriptor referring to that socket.
    /// At this point, connection is established between client and server, and they are ready to transfer data.
    int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket==-1) {
      std::cerr << "Error accepting client/TIMEOUT" << std::endl;
      this->stopBool = true;
    } else {
      cout << "Accepted client" << endl;
      thread *gotClient = new thread(&MyParallelServer::startClients, this, client_socket);
      gotClient->detach();
    }
  }
  stop();
}

void MyParallelServer::start() {

  //TIMEOUT
  struct timeval tv;
  tv.tv_sec = 60;
  tv.tv_usec = 0;
  setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

  this->thread_server = thread(&MyParallelServer::acceptClient, this, address, socketfd);
  this->thread_server.join();

}

void MyParallelServer::startClients(int client_socket) {
  ClientHandler *copyClient = this->client_handler_->copyClient();
  copyClient->handleClient(client_socket);

  cout << "closing the client socket" << endl;
  close(client_socket);
}

void MyParallelServer::stop() {
  cout << "closing the Server socket" << endl;
  close(this->socketfd);
}