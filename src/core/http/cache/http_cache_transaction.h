//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_CACHE_TRANSACTION_H
#define TIT_NETLOADER_HTTP_CACHE_TRANSACTION_H

#include <memory>

#include "core/http/http_transaction.h"

namespace tit {
namespace net {

class HttpCache;

class HttpCacheTransaction : public HttpTransaction {
 public:

  HttpCacheTransaction(URLRequestContext* url_request_context,  HttpCache* cache);

  int Start(HttpRequestInfo* request_info) override;
  int Restart() override;
  const HttpResponseInfo *GetResponseInfo() const override;
  int End() override;

 private:
  int DoPrepareCache();
  int DoSendRequest();
  int DoReadResponse();

  HttpCache* cache_;
  std::unique_ptr<HttpTransaction> network_trans_;

  HttpRequestInfo* request_info_;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_HTTP_CACHE_TRANSACTION_H
