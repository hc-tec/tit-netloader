//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_NETWORK_TRANSACTION_H
#define TIT_NETLOADER_HTTP_NETWORK_TRANSACTION_H

#include "core/http/http_transaction.h"
#include "core/http/http_response_info.h"

namespace tit {
namespace net {

class HttpNetworkSession;

class HttpNetworkTransaction : public HttpTransaction {
 public:
  explicit HttpNetworkTransaction(HttpNetworkSession* session);
  ~HttpNetworkTransaction() override;

  int Start(HttpRequestInfo *request_info) override;
  int Restart() override;
  const HttpResponseInfo *GetResponseInfo() const override;

 private:
  HttpNetworkSession* session_;
  HttpRequestInfo* request_info_;

  HttpResponseInfo response_info_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_NETWORK_TRANSACTION_H
