//
// Created by titto on 2022/5/28.
//

#include "url_request_context.h"

#include "core/network/network_context.h"
#include "core/url_request/url_request_job_factory.h"
#include "core/http/http_transaction_factory.h"

namespace tit {
namespace net {

URLRequestContext::URLRequestContext() {}

URLRequestContext::~URLRequestContext() {}

std::unique_ptr<URLRequest> URLRequestContext::CreateURLRequest(
    const URL &url,
    RequestPriority priority,
    URLRequest::Delegate *delegate) {
  auto url_request = std::make_unique<URLRequest>(url,
                                      priority,
                                      delegate,
                                      this);

  url_request_ = url_request.get();
  return url_request;
}

}  // namespace net
}  // namespace tit