//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_NETWORK_TRANSACTION_H
#define TIT_NETLOADER_HTTP_NETWORK_TRANSACTION_H

#include <memory>

#include "core/http/http_transaction.h"
#include "core/http/response/http_response_info.h"
#include "core/http/stream/http_stream.h"

namespace tit {
namespace net {

class HttpNetworkSession;

class HttpNetworkTransaction :
    public HttpTransaction,
    public HttpStream::Delegate {
 public:
  explicit HttpNetworkTransaction(HttpNetworkSession* session);
  ~HttpNetworkTransaction() override;

  int Start(HttpRequestInfo *request_info) override;
  int Restart() override;
  const HttpResponseInfo *GetResponseInfo() const override;

  // HttpStream::Delegate
  void OnConnected(HttpRequestInfo* request_info) override;
  void OnBeforeRequest(HttpRequestInfo *request_info,
                       std::string &request_msg) override;
  void OnResponseHeaderReceived(HttpResponseInfo *response_info,
                                const std::string& raw_response) override;
  void OnResponseBodyReceived(HttpResponseInfo *response_info,
                              const std::string& raw_response) override;

  void OnHostResolved(HttpRequestInfo* request_info,
                      bool need_host_resolve,
                      const std::string& dns_ip);
  void OnHostResolvedError(HttpRequestInfo* request_info);
 private:
  bool NeedHostResolve();
  int DoHostResolve();

  HttpNetworkSession* session_;
  HttpRequestInfo* request_info_;

  HttpResponseInfo response_info_;

  std::unique_ptr<HttpStream> stream_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_NETWORK_TRANSACTION_H
