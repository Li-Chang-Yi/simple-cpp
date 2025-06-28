/*************************************************************************
 *   @file : mutexlock.cpp
 *   @date : 2018-05-21
 *   @author : jiayunwei 
 ************************************************************************/
#include "mutex.h"

class  MutexLock {
 public:
  explicit MutexLock(Mutex *mu)
      : mu_(mu)  {
    this->mu_->Lock();
  }
  ~MutexLock() { this->mu_->Unlock(); }

 private:
  Mutex *const mu_;
  // No copying allowed
  MutexLock(const MutexLock&);
  void operator=(const MutexLock&);
};
