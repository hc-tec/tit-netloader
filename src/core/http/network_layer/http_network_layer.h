//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_NETWORK_LAYER_H
#define TIT_NETLOADER_HTTP_NETWORK_LAYER_H

#include "core/http/http_transaction_factory.h"

namespace tit {
namespace net {

class HttpNetworkLayer : public HttpTransactionFactory {
 public:

  explicit HttpNetworkLayer(HttpNetworkSession* session);

  ~HttpNetworkLayer() override;

  std::unique_ptr<HttpTransaction> CreateTransaction(
      URLRequestContext* url_request_context) override;

  HttpNetworkSession* GetSession() override;

 private:
  HttpNetworkSession* session_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_NETWORK_LAYER_H
