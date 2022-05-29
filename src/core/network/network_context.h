//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NETWORK_CONTEXT_H
#define TIT_NETLOADER_NETWORK_CONTEXT_H

#include <memory>
#include <vector>

namespace tit {
namespace net {

class HostResolver;
class NetworkService;
class ResourceScheduler;
class RequestParams;
class URLLoaderInterceptor;

class NetworkContext {
 public:
  NetworkContext();
  ~NetworkContext();

  HostResolver* host_resolver() { return host_resolver_.get(); }
  ResourceScheduler* resource_scheduler() { return resource_scheduler_.get(); }

  void AddURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  void RemoveURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  bool URLLoaderIntercept(NetworkService* service,
                          RequestParams* params);

 private:
  std::unique_ptr<HostResolver> host_resolver_;
  std::unique_ptr<ResourceScheduler> resource_scheduler_;

  std::vector<std::shared_ptr<URLLoaderInterceptor>> url_loader_interceptors;
};


}  // namespace net
}  // namespace tit


#endif //TIT_NETLOADER_NETWORK_CONTEXT_H
