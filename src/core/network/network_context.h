//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NETWORK_CONTEXT_H
#define TIT_NETLOADER_NETWORK_CONTEXT_H

#include <memory>

namespace tit {
namespace net {

class HostResolver;

class NetworkContext {
 public:

 private:
  std::unique_ptr<HostResolver> host_resolver_;

};


}  // namespace net
}  // namespace tit


#endif //TIT_NETLOADER_NETWORK_CONTEXT_H
