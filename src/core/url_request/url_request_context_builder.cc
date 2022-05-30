//
// Created by titto on 2022/5/28.
//

#include "url_request_context_builder.h"

#include "core/http/network_layer/http_network_session.h"
#include "core/http/http_transaction_factory.h"
#include "core/http/network_layer/http_network_layer.h"
#include "core/http/cache/http_cache.h"
#include "core/network/host_resolver.h"
#include "core/network/network_context.h"
#include "core/network/resource_scheduler.h"
#include "core/url_request/url_request_context.h"

namespace tit {
namespace net {

URLRequestContextBuilder::URLRequestContextBuilder(
    NetworkContext *network_context)
    : network_context_(network_context),
      network_session_(std::make_unique<HttpNetworkSession>()),
      url_request_job_factory_(network_context_->job_factory()) {
  network_session_->host_resolver_ = network_context_->host_resolver();
  network_session_->network_context_ = network_context_;
  std::unique_ptr<HttpTransactionFactory> network_layer =
      std::make_unique<HttpNetworkLayer>(network_session_.get());
  http_transaction_factory_ = std::make_unique<HttpCache>(
      std::move(network_layer));
}

URLRequestContextBuilder::~URLRequestContextBuilder() {}

std::unique_ptr<URLRequestContext> URLRequestContextBuilder::Build() {
  auto context = std::make_unique<URLRequestContext>();
  context->set_host_resolver(
      network_context_->host_resolver());
  context->set_resource_scheduler(
      network_context_->resource_scheduler());

  context->set_job_factory(url_request_job_factory_);

  SetHttpNetworkSessionComponents(network_session_.get(), context.get());

  context->set_transaction_factory(std::move(http_transaction_factory_));

  return context;
}

void URLRequestContextBuilder::SetHttpNetworkSessionComponents(
    HttpNetworkSession *session,
    URLRequestContext *request_context) {

}

}  // namespace net
}  // namespace tit