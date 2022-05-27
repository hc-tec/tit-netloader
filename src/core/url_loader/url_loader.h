//
// Created by titto on 2022/5/27.
//

#ifndef TIT_NETLOADER_URL_LOADER_H
#define TIT_NETLOADER_URL_LOADER_H

#include <memory>

#include <co/def.h>

namespace tit {
namespace net {

class URLRequest;
class RequestParams;
class NetworkContext;
class ResourceScheduler;

class URLLoader {
 public:

  class Delegate {

  };

  URLLoader(uint64 request_id,
            const RequestParams& request_params,
            NetworkContext* network_context,
            Delegate* delegate);

  ~URLLoader();

 private:

  uint64 request_id_;
  Delegate* delegate_;

  NetworkContext* network_context_;
  ResourceScheduler* resource_scheduler_;
  std::unique_ptr<URLRequest> url_request_;

};

}  // namespace net
}  // namespace tit



#endif //TIT_NETLOADER_URL_LOADER_H
