//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_CONTEXT_H
#define TIT_NETLOADER_URL_REQUEST_CONTEXT_H

#include <memory>

#include "core/url_request/url_request.h"

namespace tit {
namespace net {

class HostResolver;
class HttpTransactionFactory;
class ResourceScheduler;
class URLRequestJobFactory;

class URLRequestContext {
 public:
  URLRequestContext();

  ~URLRequestContext();

  std::unique_ptr<URLRequest> CreateURLRequest(const URL& url,
                                               RequestPriority priority,
                                               URLRequest::Delegate* delegate);

  void set_host_resolver(HostResolver* host_resolver) {
    host_resolver_ = host_resolver;
  }

  void set_resource_scheduler(ResourceScheduler* resource_scheduler) {
    resource_scheduler_ = resource_scheduler;
  }

  void set_url_request(URLRequest* url_request) {
    url_request_ = url_request;
  }

  void set_job_factory(std::unique_ptr<URLRequestJobFactory> job_factory) {
    url_request_job_factory_ = std::move(job_factory);
  }

  void set_transaction_factory(
      std::unique_ptr<HttpTransactionFactory> transaction_factory) {
    http_transaction_factory_ = std::move(transaction_factory);
  }

 private:

  HostResolver* host_resolver_;
  ResourceScheduler* resource_scheduler_;

  URLRequest* url_request_;

  std::unique_ptr<URLRequestJobFactory> url_request_job_factory_;
  std::unique_ptr<HttpTransactionFactory> http_transaction_factory_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_CONTEXT_H
