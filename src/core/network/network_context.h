//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NETWORK_CONTEXT_H
#define TIT_NETLOADER_NETWORK_CONTEXT_H

#include <memory>
#include <vector>

#include "core/url_request/url_request_job_factory.h"

namespace tit {
namespace net {

class HostResolver;
class HttpNetworkTransaction;
class NetworkService;
class ResourceScheduler;
class RequestParams;
class URLLoaderInterceptor;
class URLRequestJobFactory;
class URLRequestObserver;

class NetworkContext {
 public:
  NetworkContext();
  ~NetworkContext();

  HostResolver* host_resolver() { return host_resolver_.get(); }
  ResourceScheduler* resource_scheduler() { return resource_scheduler_.get(); }
  URLRequestJobFactory* job_factory() { return url_request_job_factory_.get(); }

  void AddURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  void RemoveURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  bool URLLoaderIntercept(NetworkService* service,
                          RequestParams* params);

  bool SetProtocolHandler(const std::string& scheme,
                          std::unique_ptr<URLRequestJobFactory::ProtocolHandler>
                              protocol_handler);

  void AddURLRequestObserver(
      std::weak_ptr<URLRequestObserver> observer);

  void RemoveURLRequestObserver(
      std::weak_ptr<URLRequestObserver> observer);

//  const std::vector<std::weak_ptr<URLRequestObserver>>&
//  url_request_observers() {
//    return url_request_observers_;
//  }

 private:
  friend HttpNetworkTransaction;

  std::unique_ptr<HostResolver> host_resolver_;
  std::unique_ptr<ResourceScheduler> resource_scheduler_;
  std::unique_ptr<URLRequestJobFactory> url_request_job_factory_;

  std::vector<std::shared_ptr<URLLoaderInterceptor>> url_loader_interceptors_;
  std::vector<std::weak_ptr<URLRequestObserver>> url_request_observers_;
};


}  // namespace net
}  // namespace tit


#endif //TIT_NETLOADER_NETWORK_CONTEXT_H
