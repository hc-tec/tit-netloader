//
// Created by titto on 2022/5/28.
//

#include "url_request_context.h"


#include "core/network/host_resolver.h"
#include "core/network/network_context.h"
#include "core/network/resource_scheduler.h"
#include "core/http/http_request_observer.h"
#include "core/http/http_transaction_factory.h"
#include "core/http/network_layer/http_network_session.h"
#include "core/url_request/url_request_job_factory.h"
#include "core/url_request/url_request_context_builder.h"

namespace tit {
namespace net {

URLRequestContext::URLRequestContext(URLRequestContextBuilder *builder)
    : url_request_context_builder_(builder) {}

URLRequestContext::~URLRequestContext() {}

std::unique_ptr<URLRequest> URLRequestContext::CreateURLRequest(
    const URL &url,
    RequestPriority priority,
    const RequestParams &request_params,
    URLRequest::Delegate *delegate) {
  auto url_request = std::make_unique<URLRequest>(url,
                                      priority,
                                      delegate,
                                      this);
  request_params_ = &request_params;
  url_request_context_builder_->network_session()->
      request_params_ = request_params_;
  url_request_ = url_request.get();
  return url_request;
}

void URLRequestContext::AddHttpRequestObserver(
    std::weak_ptr<HttpRequestObserver> observer) {
  url_request_observers_.Push(observer);
}

void URLRequestContext::RemoveHttpRequestObserver(
    std::weak_ptr<HttpRequestObserver> observer) {
  url_request_observers_.Remove(observer);
}

NetworkContext *URLRequestContext::network_context() {
  return url_request_context_builder_->network_context();
}

}  // namespace net
}  // namespace tit