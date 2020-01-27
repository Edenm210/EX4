//
// Created by eden on 14/01/2020.
//

#ifndef EX4__FILECACHEMANAGER_H_
#define EX4__FILECACHEMANAGER_H_

#include <unordered_map>
#include <list>
#include <functional>
#include <fstream>
#include "CacheManager.h"

class FileCacheManager : public CacheManager<string> {

 public:
  FileCacheManager();
  ~FileCacheManager();

  void insert(string key, string obj);

  string get(string key);

  bool existInCache (string key);



  };

#endif //EX4__FILECACHEMANAGER_H_
