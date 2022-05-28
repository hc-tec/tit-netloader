//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_TRANSACTION_FACTORY_H
#define TIT_NETLOADER_HTTP_TRANSACTION_FACTORY_H

#include <memory>

namespace tit {
namespace net {

class HttpTransaction;
class HttpNetworkSession;

class HttpTransactionFactory {
 public:
  virtual ~HttpTransactionFactory(){}

  virtual std::unique_ptr<HttpTransaction> CreateTransaction() = 0;

  virtual HttpNetworkSession* GetSession() = 0;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_TRANSACTION_FACTORY_H
