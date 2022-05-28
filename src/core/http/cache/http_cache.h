//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_CACHE_H
#define TIT_NETLOADER_HTTP_CACHE_H

#include <memory>

#include "core/http/http_transaction_factory.h"

namespace tit {
namespace net {

class HttpCacheTransaction;

class HttpCache : public HttpTransactionFactory {
 public:

  class Transaction;

  HttpCache(std::unique_ptr<HttpTransactionFactory> network_layer);

  std::unique_ptr<HttpTransaction> CreateTransaction() override;

  HttpNetworkSession* GetSession() override;

 private:
  friend HttpCacheTransaction;

  std::unique_ptr<HttpTransactionFactory> network_layer_;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_HTTP_CACHE_H
