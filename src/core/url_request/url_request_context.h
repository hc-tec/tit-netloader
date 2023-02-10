//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_CONTEXT_H
#define TIT_NETLOADER_URL_REQUEST_CONTEXT_H

#include <memory>

#include "core/base/weak_container.h"
#include "core/url_request/url_request.h"

namespace tit {
namespace net {

struct RequestParams;
class HostResolver;
class HttpNetworkTransaction;
class HttpRequestObserver;
class HttpTransactionFactory;
class NetworkContext;
class ResourceScheduler;
class URLRequestJobFactory;
class URLRequestContextBuilder;

class URLRequestContext {
 public:
  explicit URLRequestContext(URLRequestContextBuilder* builder);

  ~URLRequestContext();

  std::unique_ptr<URLRequest> CreateURLRequest(const URL& url,
                                               RequestPriority priority,
                                               const RequestParams &request_params,
                                               URLRequest::Delegate* delegate);

  void set_request_params(const RequestParams* request_params) {
    request_params_ = request_params;
  }
  const RequestParams* request_params() { return request_params_; }

  void set_host_resolver(HostResolver* host_resolver) {
    host_resolver_ = host_resolver;
  }

  void set_resource_scheduler(ResourceScheduler* resource_scheduler) {
    resource_scheduler_ = resource_scheduler;
  }

  void set_url_request(URLRequest* url_request) {
    url_request_ = url_request;
  }

  URLRequestJobFactory* job_factory() { return url_request_job_factory_; }
  void set_job_factory(URLRequestJobFactory* job_factory) {
    url_request_job_factory_ = job_factory;
  }

  HttpTransactionFactory* transaction_factory() {
    return http_transaction_factory_;
  }
  void set_transaction_factory(
      HttpTransactionFactory* transaction_factory) {
    http_transaction_factory_ = transaction_factory;
  }

  NetworkContext* network_context();

  void AddHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

  void AddHttpRequestObserver(
      HttpRequestObserver* observer);

  void RemoveHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

  void RemoveHttpRequestObserver(
      HttpRequestObserver* observer);

 private:
  friend HttpNetworkTransaction;

  const RequestParams* request_params_;
  HostResolver* host_resolver_;
  ResourceScheduler* resource_scheduler_;
  URLRequestJobFactory* url_request_job_factory_;
  URLRequestContextBuilder* url_request_context_builder_;

  URLRequest* url_request_;

  HttpTransactionFactory* http_transaction_factory_;

  WeakContainerUnsafe<HttpRequestObserver> url_request_observers_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_CONTEXT_H
