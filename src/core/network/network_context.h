//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NETWORK_CONTEXT_H
#define TIT_NETLOADER_NETWORK_CONTEXT_H

#include <memory>


namespace tit {
namespace net {

class HostResolver;
class ResourceScheduler;

class NetworkContext {
 public:
  NetworkContext();
  ~NetworkContext();

  HostResolver* host_resolver() { return host_resolver_.get(); }
  ResourceScheduler* resource_scheduler() { return resource_scheduler_.get(); }

 private:
  std::unique_ptr<HostResolver> host_resolver_;
  std::unique_ptr<ResourceScheduler> resource_scheduler_;
};


}  // namespace net
}  // namespace tit


#endif //TIT_NETLOADER_NETWORK_CONTEXT_H
