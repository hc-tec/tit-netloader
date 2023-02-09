//
// Created by titto on 2023/2/9.
//

#ifndef TIT_NETLOADER_WEAK_CONTAINER_H
#define TIT_NETLOADER_WEAK_CONTAINER_H

#include <memory>
#include <map>
#include <vector>

#include "co/co/mutex.h"

namespace tit {

template <typename T>
class WeakContainerUnsafe {
 public:
  void Push(std::weak_ptr<T> el) {
    const char* id = typeid(el).name();
    if (elements_.find(id) == elements_.end()) {
      elements_.insert({id, el});
    }
  }

  void Remove(std::weak_ptr<T> el) {
    const char* id = typeid(el).name();
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

  bool StillAlive(std::weak_ptr<T> el) {
    if (el.expired()) {
      unless_elements_.push_back(typeid(el).name());
      return false;
    }
    return true;
  }

  std::map<const char*, std::weak_ptr<T>> GetElements() { return elements_; }
 private:
  std::map<const char*, std::weak_ptr<T>> elements_;

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
