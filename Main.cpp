//
// Created by eden on 20/01/2020.
//

#include "Main.h"
#include "MySerialServer.h"
#include "ObjectAdapter.h"
#include "BFS.h"
#include "DFS.h"
#include "BestFirstSearch.h"
#include "Astar.h"
#include "MatrixClientHandler.h"
#include "MyParallelServer.h"
#include "StringReverser.h"
#include "StringClientHandler.h"

int boot::Main :: main(int port){

  MyParallelServer server;

  CacheManager<string> *cache = new FileCacheManager();
  ISearcher<double,vector<State<double> *>>* astar = new Astar<double>();

  Solver<vector<string>, string> * solve = new ObjectAdapter<double>(astar);

  ClientHandler *ch = new MatrixClientHandler(solve, cache);

  server.open(port, *ch);

  delete ch;
  delete solve;
  delete cache;

  return 0;

}


