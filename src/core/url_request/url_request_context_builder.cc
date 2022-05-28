//
// Created by titto on 2022/5/28.
//

#include "url_request_context_builder.h"

#include "core/http/http_transaction_factory.h"
#include "core/network/network_context.h"
#include "core/url_request/url_request_context.h"
#include "core/url_request/url_request_job_factory.h"

namespace tit {
namespace net {

URLRequestContextBuilder::URLRequestContextBuilder(
    NetworkContext *network_context)
    : network_context_(network_context) {}

URLRequestContextBuilder::~URLRequestContextBuilder() {}

std::unique_ptr<URLRequestContext> URLRequestContextBuilder::Build() {
  auto context = std::make_unique<URLRequestContext>();
  context->set_host_resolver(
      network_context_->host_resolver());
  context->set_resource_scheduler(
      network_context_->resource_scheduler());

  if (url_request_job_factory_ == nullptr)
    url_request_job_factory_ = std::make_unique<URLRequestJobFactory>();
  context->set_job_factory(std::move(url_request_job_factory_));

  if (http_transaction_factory_ == nullptr)
    http_transaction_factory_ = std::make_unique<HttpTransactionFactory>();
  context->set_transaction_factory(std::move(http_transaction_factory_));

  return context;
}

}  // namespace net
}  // namespace tit