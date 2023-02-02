//
// Created by titto on 2022/5/28.
//

#include "network_service.h"

#include "core/http/http_transaction_factory.h"
#include "core/network/network_context.h"
#include "core/network/request_manager.h"
#include "core/network/request_params.h"
#include "core/network/host_resolver.h"
#include "core/network/resource_scheduler.h"
#include "core/url_loader/url_loader_factory.h"
#include "core/url_request/url_request_context_builder.h"

namespace tit {
namespace net {

NetworkService::NetworkService()
    : network_context_(std::make_unique<NetworkContext>()),
      request_manager_(std::make_unique<RequestManager>()),
      url_loader_factory_(std::make_unique<URLLoaderFactory>()) {

}

std::unique_ptr<URLLoader> NetworkService::CreateURLLoader(
    RequestParams& request_params) {

  if(!network_context_->URLLoaderIntercept(this, &request_params)) {
    LOG(INFO) << "Intercept by URLLoaderInterceptor";
    return nullptr;
  }

  uint64 request_id = request_manager_->GenerateRequestId();
  std::unique_ptr<URLLoader> url_loader =
      url_loader_factory_->CreateURLLoader(
          request_id,
          request_params,
          network_context_.get(),
          this);

  request_manager_->PutRequest(url_loader.get());
  return url_loader;
}

NetworkService::~NetworkService() {

}

void NetworkService::AddURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  network_context_->AddURLLoaderInterceptor(interceptor);
}

void NetworkService::RemoveURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  network_context_->RemoveURLLoaderInterceptor(interceptor);
}

bool NetworkService::SetProtocolHandler(
    const std::string& scheme,
    std::unique_ptr<URLRequestJobFactory::ProtocolHandler> protocol_handler) {
  return network_context_->SetProtocolHandler(
      scheme, std::move(protocol_handler));
}

void NetworkService::AddHttpRequestObserver(
    std::weak_ptr<HttpRequestObserver> observer) {
  network_context_->AddHttpRequestObserver(observer);
}

void NetworkService::RemoveHttpRequestObserver(
    std::weak_ptr<HttpRequestObserver> observer) {
  network_context_->RemoveHttpRequestObserver(observer);
}



}  // namespace net
}  // namespace tit