//
// Created by titto on 2022/5/28.
//

#include "http_cache.h"

namespace tit {
namespace net {

HttpCache::HttpCache(std::unique_ptr<HttpTransactionFactory> network_layer)
    : network_layer_(std::move(network_layer)) {}

std::unique_ptr<HttpTransaction> HttpCache::CreateTransaction() {
  return std::unique_ptr<HttpTransaction>();
}

HttpNetworkSession* HttpCache::GetSession() { return nullptr; }


}  // namespace net
}  // namespace tit