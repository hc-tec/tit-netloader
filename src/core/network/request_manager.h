//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_REQUEST_MANAGER_H
#define TIT_NETLOADER_REQUEST_MANAGER_H

#include <map>
#include <memory>
#include <mutex>

#include <co/def.h>

namespace tit {
namespace net {

class URLLoader;

class RequestManager {
 public:

  RequestManager();

  uint64 GenerateRequestId();

  uint64 PutRequest(URLLoader* url_loader);

  URLLoader* GetRequest(uint64 request_id);

  void RemoveRequest(uint64 request_id);

 private:
  uint64 consume_request_id;

  std::mutex request_map_lock_;
  std::map<uint64, URLLoader*> request_map_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_REQUEST_MANAGER_H
