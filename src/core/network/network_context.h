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
class HttpRequestObserver;
class NetworkService;
class ResourceScheduler;
class RequestParams;
class URLLoaderInterceptor;
class URLRequestJobFactory;
class URLRequestContextBuilder;

class NetworkContext {
 public:
  NetworkContext();
  ~NetworkContext();

  void set_host_resolver(std::unique_ptr<HostResolver> host_resolver) {
    host_resolver_ = std::move(host_resolver);
  }
  HostResolver* host_resolver() { return host_resolver_.get(); }

  void set_resource_scheduler(std::unique_ptr<ResourceScheduler> resource_scheduler) {
    resource_scheduler_ = std::move(resource_scheduler);
  }
  ResourceScheduler* resource_scheduler() { return resource_scheduler_.get(); }

  void set_job_factory(std::unique_ptr<URLRequestJobFactory> job_factory) {
    url_request_job_factory_ = std::move(job_factory);
  }
  URLRequestJobFactory* job_factory() { return url_request_job_factory_.get(); }

  void set_url_request_context_builder(
      std::unique_ptr<URLRequestContextBuilder> builder) {
    url_request_context_builder_ = std::move(builder);
  }
  URLRequestContextBuilder* url_request_context_builder() {
    return url_request_context_builder_.get();
  }

  void AddURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  void RemoveURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  bool URLLoaderIntercept(NetworkService* service,
                          RequestParams* params);

  bool SetProtocolHandler(const std::string& scheme,
                          std::unique_ptr<URLRequestJobFactory::ProtocolHandler>
                              protocol_handler);

  void AddHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

  void RemoveHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

 private:
  friend HttpNetworkTransaction;

  std::unique_ptr<HostResolver> host_resolver_;
  std::unique_ptr<ResourceScheduler> resource_scheduler_;
  std::unique_ptr<URLRequestJobFactory> url_request_job_factory_;
  std::unique_ptr<URLRequestContextBuilder> url_request_context_builder_;

  std::vector<std::shared_ptr<URLLoaderInterceptor>> url_loader_interceptors_;
  std::vector<std::weak_ptr<HttpRequestObserver>> url_request_observers_;
};


}  // namespace net
}  // namespace tit


#endif //TIT_NETLOADER_NETWORK_CONTEXT_H
