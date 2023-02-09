//
// Created by titto on 2022/5/28.
//

#include "network_context.h"

#include "core/http/http_transaction_factory.h"
#include "core/network/host_resolver.h"
#include "core/network/resource_scheduler.h"
#include "core/url_loader/url_loader_interceptor.h"
#include "core/url_request/url_request_job_factory.h"
#include "core/url_request/url_request_context_builder.h"

namespace tit {
namespace net {

NetworkContext::NetworkContext()
    : host_resolver_(std::make_unique<SimpleHostResolver>()),
      url_request_job_factory_(std::make_unique<URLRequestJobFactory>()),
      url_request_context_builder_(
          std::make_unique<URLRequestContextBuilder>(this)) {

}

NetworkContext::~NetworkContext() {}

void NetworkContext::AddURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  url_loader_interceptors_.Push(interceptor);
}

void NetworkContext::RemoveURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  url_loader_interceptors_.Remove(interceptor);
}

bool NetworkContext::URLLoaderIntercept(NetworkService* service,
                                        RequestParams* params) {
  auto interceptors = url_loader_interceptors_.GetElements();
  for (auto& [_, interceptor] : interceptors) {
    if (url_loader_interceptors_.StillAlive(interceptor)) {
      auto interceptor_share = interceptor.lock();
      if (!interceptor_share->Interceptor(service, params)) return false;
    }
  }
  return true;
}

bool NetworkContext::SetProtocolHandler(
    const std::string& scheme,
    std::unique_ptr<URLRequestJobFactory::ProtocolHandler> protocol_handler) {
  return url_request_job_factory_->SetProtocolHandler(
      scheme, std::move(protocol_handler));
}

void NetworkContext::AddURLRequestObserver(
    std::weak_ptr<URLRequestObserver> observer) {
  url_request_observers_.Push(observer);
}

void NetworkContext::RemoveURLRequestObserver(
    std::weak_ptr<URLRequestObserver> observer) {
  url_request_observers_.Remove(observer);
}

}  // namespace net
}  // namespace tit
