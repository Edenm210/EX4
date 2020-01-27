//
// Created by eden on 14/01/2020.
//

#include <zconf.h>
#include "MySerialServer.h"
//mutex *mtx = new mutex;

MySerialServer::MySerialServer() {};

int MySerialServer::open(int port, ClientHandler &client_handler) {
  this->client_handler_ = &client_handler;
  int run;
  this->portNum = port;
  //blocks until server is connected
  run = initServer();
  while (run!=0) {
    run = initServer();
  }
}

int MySerialServer::acceptClient(sockaddr_in address, int socketfd) {

  while (true) {
    //TIMEOUT
    struct timeval tv;
    tv.tv_sec = 60;
    tv.tv_usec = 0;
    setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (const char *) &tv, sizeof tv);

    /// extracts the first connection request on the queue of pending connections for the listening socket, sockfd,
    /// creates a new connected socket, and returns a new file descriptor referring to that socket.
    /// At this point, connection is established between client and server, and they are ready to transfer data.
    client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);

    if (client_socket==-1) {
      std::cerr << "Error accepting client/TIMEOUT" << std::endl;
      stop();
      return -4;
    } else {
      cout << "Accepted client" << endl;
    }

    this->client_handler_->handleClient(client_socket);

    cout << "closing the client socket" << endl;
    close(client_socket);
  }

}

int MySerialServer::initServer() {

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

  ///It puts the server socket in a passive mode, where it waits for the client to approach the server to make a connection
  if (listen(socketfd, 5)==-1) {
    std::cerr << "Error during listening command" << std::endl;
    return -3;
  }
  cout << "Server is now listening..." << endl;

  thread *getClient = new thread(&MySerialServer::acceptClient, this, address, socketfd);
  getClient->join();

  return 0;
}

void MySerialServer::stop() {
  cout << "closing the Server socket" << endl;
  close(this->socketfd); //closing the listening socket
}




