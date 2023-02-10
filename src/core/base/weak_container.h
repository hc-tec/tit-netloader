//
// Created by titto on 2023/2/9.
//

#ifndef TIT_NETLOADER_WEAK_CONTAINER_H
#define TIT_NETLOADER_WEAK_CONTAINER_H

#include <cstdio>
#include <memory>
#include <map>
#include <vector>
#include <any>

#include "co/co/mutex.h"

namespace tit {

inline const char* labelClassName(char* name, void* el) {
  snprintf(name, 8, "%x", el);
}

template <typename T>
class WeakContainerUnsafe {
 public:
  void Push(std::weak_ptr<T> el) {
    char id[8];
    labelClassName(id, el.lock().get());
    if (elements_.find(id) == elements_.end()) {
      elements_.insert({id, el});
    }
  }

  void Push(T* el) {
    char id[8];
    labelClassName(id, el);
    if (elements_.find(id) == elements_.end()) {
      elements_.insert({id, el});
    }
  }

  void Remove(std::weak_ptr<T> el) {
    char id[8];
    labelClassName(id, el.lock().get());
    auto it = elements_.find(id);
    if (it == elements_.end()) return;
    elements_.erase(it);
  }

  void Remove(T* el) {
    char id[8];
    labelClassName(id, el);
    auto it = elements_.find(id);
    if (it == elements_.end()) return;
    elements_.erase(it);
  }

  void ClearUnlessElements() {
    for (auto& el : unless_elements_) {
      elements_.erase(el);
    }
    unless_elements_.clear();
  }

  bool StillAlive(std::any el) {
    if (el.type() == typeid(std::weak_ptr<T>)) {
      auto w_el = std::any_cast<std::weak_ptr<T>>(el);
      char id[8];
      labelClassName(id, w_el.lock().get());
      if (w_el.expired()) {
        unless_elements_.push_back(id);
        return false;
      }
    }
    return true;
  }

  T* GetPtr(std::any el) {
    if (el.type() == typeid(std::weak_ptr<T>)) {
      return std::any_cast<std::weak_ptr<T>>(el).lock().get();
    }
    return std::any_cast<T*>(el);
  }

  std::map<const char*, std::any> GetElements() { return elements_; }
 private:
  std::map<const char*, std::any> elements_;

  std::vector<const char*> unless_elements_;
};

template <typename T>
class WeakContainerSafe {
 public:
  void Push(std::weak_ptr<T> el) {
    co::MutexGuard g(mutex_);
    unsafe_container_.Push(el);
  }

  void Remove(std::weak_ptr<T> el) {
    co::MutexGuard g(mutex_);
    unsafe_container_.Remove(el);
  }

  void ClearUnlessElements() {
    unsafe_container_.ClearUnlessElements();
  }

  bool StillAlive(std::weak_ptr<T> el) {
    return unsafe_container_.StillAlive(el);
  }

  std::map<const char*, std::weak_ptr<T>> GetElements() {
    return unsafe_container_.GetElements();
  }

  co::Mutex& mutex() { return mutex_; }
 private:
  co::Mutex mutex_;
  WeakContainerUnsafe<T> unsafe_container_;
};

}

#endif  // TIT_NETLOADER_WEAK_CONTAINER_H
