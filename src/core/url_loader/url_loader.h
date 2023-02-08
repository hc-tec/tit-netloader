//
// Created by titto on 2022/5/27.
//

#ifndef TIT_NETLOADER_URL_LOADER_H
#define TIT_NETLOADER_URL_LOADER_H

#include <memory>

#include <co/def.h>

#include "core/url_request/url_request.h"

namespace tit {
namespace net {
struct RequestParams;

class HttpRequestObserver;
class NetworkContext;
class ResourceScheduler;
class URLRequestContext;
class URLRequestContextBuilder;

class URLLoader : public URLRequest::Delegate {
 public:

  class Delegate {

  };

  URLLoader(uint64 request_id,
            const RequestParams& request_params,
            NetworkContext* network_context,
            Delegate* delegate);

  ~URLLoader();

  void ScheduleStart();

  void Start();

  void set_url_request_context_builder(URLRequestContextBuilder* builder) {
    url_request_context_builder_ = builder;
  }

  void AddHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

  void RemoveHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

 private:

  uint64 request_id_;
  Delegate* delegate_;

  NetworkContext* network_context_;
  ResourceScheduler* resource_scheduler_;
  URLRequestContextBuilder* url_request_context_builder_;

  std::unique_ptr<URLRequestContext> url_request_context_;
  std::unique_ptr<URLRequest> url_request_;

};

}  // namespace net
}  // namespace tit



#endif //TIT_NETLOADER_URL_LOADER_H
