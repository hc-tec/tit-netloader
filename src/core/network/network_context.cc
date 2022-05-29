//
// Created by titto on 2022/5/28.
//

#include "network_context.h"

#include "core/network/host_resolver.h"
#include "core/network/resource_scheduler.h"
#include "core/url_loader/url_loader_interceptor.h"


namespace tit {
namespace net {

NetworkContext::NetworkContext() {}
NetworkContext::~NetworkContext() {}

void NetworkContext::AddURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  url_loader_interceptors.push_back(interceptor);
}

void NetworkContext::RemoveURLLoaderInterceptor(
    std::shared_ptr<URLLoaderInterceptor> interceptor) {
  int size = url_loader_interceptors.size();
//  int index = -1;
  for (int i = 0; i < size; ++i) {
    if (typeid(url_loader_interceptors[i]) == typeid(interceptor)) {
//      index = i;
      url_loader_interceptors.erase(
          url_loader_interceptors.begin() + i);
      break;
    }
  }
}

bool NetworkContext::URLLoaderIntercept(NetworkService* service,
                                        RequestParams* params) {
  for (auto& interceptor : url_loader_interceptors) {
    if (!interceptor->Interceptor(service, params)) return false;
  }
  return true;
}

}  // namespace net
}  // namespace tit
