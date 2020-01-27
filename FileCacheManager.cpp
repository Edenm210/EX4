//
// Created by eden on 14/01/2020.
//

#include "FileCacheManager.h"
// constructor
FileCacheManager::FileCacheManager() {}

FileCacheManager::~FileCacheManager() {}

//getting new T object (creating file)
void FileCacheManager::insert(string key, string obj) {

  try {
    pthread_mutex_lock(&mutex);

    // every T object has its own file
    ofstream outputFile(key + ".txt", std::ios::out);
    if (!outputFile) { throw ("can not open the output file"); }
    else {
      outputFile.write(obj.c_str(), obj.size()); // writing to the file
      outputFile.close();
    }
    pthread_mutex_unlock(&mutex);
  }
  catch (int e) {
    pthread_mutex_unlock(&mutex);

    throw;
  }
}


string FileCacheManager::get(string key) {
  pthread_mutex_lock(&mutex);

  try {
    string objectString, line;

    ifstream sourceFile(key + ".txt", std::ios::in);
    if (sourceFile.is_open()) {
      while (sourceFile.good()) {
        getline(sourceFile, line);
        objectString += line;
      }
      sourceFile.close();
    }
    pthread_mutex_unlock(&mutex);

    return objectString;
  }
  catch (int e) {
    pthread_mutex_unlock(&mutex);

    throw;
  }
}


bool FileCacheManager::existInCache (string key) {
  pthread_mutex_lock(&mutex);
  bool founded = true;
  ifstream sourceFile(key + ".txt", std::ios::in);
  // return if the key does not exist in cache
  if(!sourceFile){
    founded=false;
  }
  pthread_mutex_unlock(&mutex);
  return founded;
}
