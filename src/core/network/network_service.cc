//
// Created by titto on 2022/5/28.
//

#include "network_service.h"

#include "core/network/request_manager.h"
#include "core/network/network_context.h"
#include "core/url_loader/url_loader_factory.h"
#include "core/url_request/url_request.h"

namespace tit {
namespace net {

NetworkService::NetworkService()
    : network_context_(std::make_unique<NetworkContext>()),
      request_manager_(std::make_unique<RequestManager>()),
      url_loader_factory_(std::make_unique<URLLoaderFactory>()) {

}

std::unique_ptr<URLLoader> NetworkService::CreateURLLoader(
    const RequestParams& request_params) {

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

NetworkService* GetNetworkService() {
  static NetworkService service;
  return &service;
}

}  // namespace net
}  // namespace tit