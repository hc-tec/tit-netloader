//
// Created by titto on 2022/5/28.
//

#include "request_manager.h"

#include <co/atomic.h>

#include "log/logging.h"

namespace tit {
namespace net {

RequestManager::RequestManager() : consume_request_id(0) {}

uint64 RequestManager::GenerateRequestId() {
  atomic_inc(&consume_request_id);
  return consume_request_id;
}

uint64 RequestManager::PutRequest(URLLoader *url_loader) {
  std::lock_guard<std::mutex> g(request_map_lock_);
  if (auto [pos, ok] = request_map_.insert({atomic_load(&consume_request_id), url_loader});
      !ok) {
    LOG(ERROR) << "Request id: " << consume_request_id <<  " insert error";
    return -1;
  }
  return consume_request_id;
}

URLLoader* RequestManager::GetRequest(uint64 request_id) {
  std::lock_guard<std::mutex> g(request_map_lock_);
  auto it = request_map_.find(request_id);
  if (it == request_map_.end()) return nullptr;
  return it->second;
}

void RequestManager::RemoveRequest(uint64 request_id) {
  std::lock_guard<std::mutex> g(request_map_lock_);
  auto it = request_map_.find(request_id);
  if (it == request_map_.end()) return;
  request_map_.erase(request_id);
}

}  // namespace net
}  // namespace tit