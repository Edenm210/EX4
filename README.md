# **Algorithms Project**

This project was created by Eden Moshe as an assignment in Advance Programming course in Computer Science degree studying.

## Author:
- **Eden Moshe**  
  
  ## Intrudoction:
  The goal of this project is to create a program that solves a given problem. the input will be a matrix with initial and goal points     and the solution will be the path between them that will be found using a search algorithm.
  This project is a showcase to our programming experience. It contains: Client-Server communication programming, design patterns,   templates, data streaming, selection and implementation of algorithms and parallel programming using Threads.
  
  ## Description:
   
  - Server-Client Communication:
    - the program starts with creating a server thread that runs in the background, receives data from clients and reads it line by            line. the listening port is provided by CMD argument.
      The server can receive clients either in serial or parallel form.
      when no client is connected for 60 seconds the server stops listening and the program ends.
    - The data received from the client is a generic problem for the server to solve. In our case the problem is to find the lowest cost       path from source to goal points in a matrix.
    - the server first check if the problem has been solved before and the solution exists in the data base files, in that case it will       return the solution to the client without solving again. Otherwise, the problem will be solved using the best search algorithm,         the solution will be stored in the data base files and sent to client.
  
    - Each client's treatment is done by a separate thread.
  
  - The search algorithms implemented are: A*, Best first search, BFS, DFS.
  
  - Following an empirical experiment (described in the attached file), it was found that for the lowest-cost path matrix problem, algorithm A* returns the best solution     of from all other algorithm- the lowest cost path while evaluating the lowest number of vertices.
    This is why the algorithm chosen to solve the problems is the most efficient algorithm - A*.
 
  - Multiple Design Patterns were used in this program, such as Bridge and Object Adapter.
    The SOLID programming principle such as Open/Close, Single responsibility and Dependency inversion are kept.
        
  ## Run Instructions:
  * Open the linux terminal and compile the program:
    ```
    * g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
    ```
  * Run the program with a port number (the server listening port) using the following command (in the linux terminal): 
    ```
    * ./a.out PORT_NUM
    ```
  * Connect to the server as a client and send the matrix problem you want to solve. the solution will be sent back to you after calculating.
    the matrix problem should be in the following pattern:
       * matrix (line-by-line separated by commas)
       * start point
       * goal point
       * "end"


  ## Files
  * main.cpp
  * Main.cpp
  * Main.h

  ##### Algorithms files:
  * Astar.h
  * BestFirstSearch.h
  * BFS.h
  * DFS.h
  * FindingPathAlgo.h

  ##### Cache files:
  * CacheManager.h
  * FileCacheManager.cpp
  * FileCacheManager.h

  ##### Client handler files:
  * ClientHandler.h
  * MatrixClientHandler.h
  * StringClientHandler.h

  ##### Structure files:
  * Graph.h
  * State.h
  
  ##### Searching files:
  * ISearchable.h
  * ISearcher.h
  * SearchableGraph.h
  
  ##### Solver files:
  * Solver.h
  * ObjectAdapter.h
  * StringReverser.cpp
  * StringReverser.h

  ##### Server files:
  * Server.h
  * MyParallelServer.h
  * MyParallelServer.cpp
  * MySerialServer.h
  * MySerialServer.cpp
  
  ## Attached Files
     * Experiment_result_graphs
    
    ##### Experiment input file:
     * input_Matrix

    ##### solutions files:
     * output_Astar
     * output_BestFirstSearch
     * output_BFS
     * output_DFS


## Links
* GitHub: https://github.com/Edenm210/EX4
