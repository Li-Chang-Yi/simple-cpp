/*************************************************************************
 *   @file : mutex.h
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include <pthread.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

class Mutex {
 public:
  Mutex();
  ~Mutex();

  void Lock();
  void Unlock(); 

 private:
  pthread_mutex_t mu_;

  // No copying
  Mutex(const Mutex&);
  void operator=(const Mutex&);
};
