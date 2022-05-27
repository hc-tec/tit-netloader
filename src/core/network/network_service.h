//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NETWORK_SERVICE_H
#define TIT_NETLOADER_NETWORK_SERVICE_H

#include <memory>

#include "core/url_loader/url_loader.h"

namespace tit {
namespace net {

class NetworkContext;

class NetworkService : public URLLoader::Delegate {
 public:


 private:
  std::unique_ptr<NetworkContext> network_context_;
};

NetworkService* GetNetworkService() {
  static NetworkService service;
  return &service;
}

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_NETWORK_SERVICE_H
