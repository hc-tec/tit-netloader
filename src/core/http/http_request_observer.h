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
                              const std::string& dns_ip) = 0;

  virtual void OnHostResolveError(HttpNetworkSession* session,
                              HttpRequestInfo* request_info) = 0;

  virtual void OnConnected(HttpNetworkSession* session,
                           HttpRequestInfo* request_info) = 0;
  virtual void OnBeforeRequest(HttpNetworkSession* session,
                               HttpRequestInfo* request_info,
                               std::string& request_msg) = 0;
  virtual void OnResponseHeaderReceived(HttpNetworkSession* session,
                                        HttpResponseInfo* response_info,
                                        const std::string& raw_response) = 0;
  virtual void OnResponseBodyReceived(HttpNetworkSession* session,
                                      HttpResponseInfo* response_info,
                                      const std::string& raw_response) = 0;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_HTTP_REQUEST_OBSERVER_H
