//
// Created by titto on 2022/5/28.
//

#include "http_cache.h"

#include "core/http/http_transaction.h"
#include "core/http/cache/http_cache_transaction.h"

namespace tit {
namespace net {

HttpCache::HttpCache(std::unique_ptr<HttpTransactionFactory> network_layer)
    : network_layer_(std::move(network_layer)) {}

std::unique_ptr<HttpTransaction> HttpCache::CreateTransaction() {
  return std::make_unique<HttpCacheTransaction>(this);
}

HttpNetworkSession* HttpCache::GetSession() { return nullptr; }

HttpCache::~HttpCache() {}

}  // namespace net
}  // namespace tit