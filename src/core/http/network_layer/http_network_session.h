//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_NETWORK_SESSION_H
#define TIT_NETLOADER_HTTP_NETWORK_SESSION_H

#include <memory>

namespace tit {
namespace net {

class ClientSocketPoolManager;
class HostResolver;
class HttpStreamFactory;
class URLRequestContextBuilder;

class HttpNetworkSession {
 public:
  HttpNetworkSession();
  ~HttpNetworkSession();

  HostResolver* host_resolver() { return host_resolver_; }

  HttpStreamFactory* http_stream_factory() {
    return http_stream_factory_.get();
  }

 private:
  friend URLRequestContextBuilder;

  HostResolver* host_resolver_;

  std::unique_ptr<HttpStreamFactory> http_stream_factory_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_NETWORK_SESSION_H
