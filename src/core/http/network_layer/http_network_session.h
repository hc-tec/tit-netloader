//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_NETWORK_SESSION_H
#define TIT_NETLOADER_HTTP_NETWORK_SESSION_H

#include <memory>

namespace tit {
namespace net {

struct RequestParams;
class ClientSocketPool;
class ClientSocketPoolManager;
class HostResolver;
class HttpStreamFactory;
class NetworkContext;
class URLRequestContext;
class URLRequestContextBuilder;

class HttpNetworkSession {
 public:
  HttpNetworkSession();
  ~HttpNetworkSession();

  const RequestParams* request_params() { return request_params_; }

  NetworkContext* network_context() { return network_context_; }

  HostResolver* host_resolver() { return host_resolver_; }

  HttpStreamFactory* http_stream_factory() {
    return http_stream_factory_.get();
  }

  ClientSocketPool* GetClientSocketPool(std::string type);

 private:
  friend URLRequestContext;
  friend URLRequestContextBuilder;
  const RequestParams* request_params_;
  NetworkContext* network_context_;

  HostResolver* host_resolver_;

  std::unique_ptr<HttpStreamFactory> http_stream_factory_;
  std::unique_ptr<ClientSocketPool> normal_socket_pool_;
  std::unique_ptr<ClientSocketPool> ssl_socket_pool_;
  std::unique_ptr<ClientSocketPool> websocket_socket_pool_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_NETWORK_SESSION_H
