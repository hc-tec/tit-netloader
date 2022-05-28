//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_CONTEXT_BUILDER_H
#define TIT_NETLOADER_URL_REQUEST_CONTEXT_BUILDER_H

#include <memory>

namespace tit {
namespace net {

class NetworkContext;
class HostResolver;
class HttpNetworkSession;
class HttpTransactionFactory;
class ResourceScheduler;
class URLRequest;
class URLRequestContext;
class URLRequestJobFactory;

class URLRequestContextBuilder {
 public:

  explicit URLRequestContextBuilder(NetworkContext* network_context);

  ~URLRequestContextBuilder();

  std::unique_ptr<URLRequestContext> Build();

  void set_job_factory(std::unique_ptr<URLRequestJobFactory> job_factory) {
    url_request_job_factory_ = std::move(job_factory);
  }

  void set_transaction_factory(
      std::unique_ptr<HttpTransactionFactory> transaction_factory) {
    http_transaction_factory_ = std::move(transaction_factory);
  }

 private:

  void SetHttpNetworkSessionComponents(HttpNetworkSession* session,
                                       URLRequestContext* request_context);

  NetworkContext* network_context_;

  HostResolver* host_resolver_;
  ResourceScheduler* resource_scheduler_;

  std::unique_ptr<URLRequestJobFactory> url_request_job_factory_;
  std::unique_ptr<HttpTransactionFactory> http_transaction_factory_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_CONTEXT_BUILDER_H
