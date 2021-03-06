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
  url_loader_interceptors_.push_back(interceptor);
}

void NetworkContext::RemoveURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  int size = url_loader_interceptors_.size();
  for (int i = 0; i < size; ++i) {
    if (typeid(url_loader_interceptors_[i]) == typeid(interceptor)) {
      url_loader_interceptors_.erase(
          url_loader_interceptors_.begin() + i);
      break;
    }
  }
}

bool NetworkContext::URLLoaderIntercept(NetworkService* service,
                                        RequestParams* params) {
  for (auto& interceptor : url_loader_interceptors_) {
    if (!interceptor->Interceptor(service, params)) return false;
  }
  return true;
}

bool NetworkContext::SetProtocolHandler(
    const std::string& scheme,
    std::unique_ptr<URLRequestJobFactory::ProtocolHandler> protocol_handler) {
  return url_request_job_factory_->SetProtocolHandler(
      scheme, std::move(protocol_handler));
}

void NetworkContext::AddHttpRequestObserver(
    std::weak_ptr<HttpRequestObserver> observer) {
  url_request_observers_.push_back(observer);
}

void NetworkContext::RemoveHttpRequestObserver(
    std::weak_ptr<HttpRequestObserver> observer) {
  int size = url_request_observers_.size();
  for (int i = 0; i < size; ++i) {
    if (typeid(url_request_observers_[i]) == typeid(observer)) {
      url_request_observers_.erase(
          url_request_observers_.begin() + i);
      break;
    }
  }
}

}  // namespace net
}  // namespace tit
