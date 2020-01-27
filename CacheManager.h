//
// Created by eden on 14/01/2020.
//

#ifndef EX4__CACHEMANAGER_H_
#define EX4__CACHEMANAGER_H_

#include <string>
using namespace std;
template <class S>

class CacheManager{
 protected:
  mutable pthread_mutex_t mutex;

 public:
  virtual void insert(string key, S obj)=0;
  virtual S get(string key)=0;
  virtual bool existInCache (string key)=0;

};

#endif //EX4__CACHEMANAGER_H_
