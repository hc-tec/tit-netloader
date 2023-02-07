//
// Created by titto on 2022/5/30.
//

#ifndef TIT_NETLOADER_HTTP_REQUEST_OBSERVER_H
#define TIT_NETLOADER_HTTP_REQUEST_OBSERVER_H

#include <string>

namespace tit {
namespace net {

struct HttpRequestInfo;
struct HttpResponseInfo;
class HttpNetworkSession;

class HttpRequestObserver {
 public:
  virtual ~HttpRequestObserver() = default;

  virtual void OnHostResolved(HttpNetworkSession* session,
                           HttpRequestInfo* request_info,
                              bool need_host_resolve,
                              const std::string& dns_ip) {};

  virtual void OnHostResolveError(HttpNetworkSession* session,
                              HttpRequestInfo* request_info) {};

  virtual void OnConnected(HttpNetworkSession* session,
                           HttpRequestInfo* request_info) {};
  virtual void OnBeforeRequest(HttpNetworkSession* session,
                               HttpRequestInfo* request_info,
                               std::string& request_msg) {};
  virtual void OnResponseHeaderReceived(HttpNetworkSession* session,
                                        HttpRequestInfo* request_info,
                                        HttpResponseInfo* response_info,
                                        const std::string& raw_response) {};
  virtual void OnResponseBodyReceived(HttpNetworkSession* session,
                                      HttpRequestInfo* request_info,
                                      HttpResponseInfo* response_info,
                                      const std::string& raw_response) {};
  virtual void OnResponseAllReceived(HttpNetworkSession* session,
                                      HttpRequestInfo* request_info,
                                      HttpResponseInfo* response_info) {};
  virtual void OnConnectClosed(HttpNetworkSession* session,
                               HttpRequestInfo* request_info,
                               HttpResponseInfo* response_info) {};
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_HTTP_REQUEST_OBSERVER_H
