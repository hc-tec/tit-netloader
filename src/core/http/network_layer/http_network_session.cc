//
// Created by titto on 2022/5/28.
//

#include "http_network_session.h"

#include "core/base/url/url_constants.h"
#include "core/http/stream/http_basic_stream_factory.h"
#include "core/socket/tcp/transport_client_socket_pool.h"

namespace tit {
namespace net {

HttpNetworkSession::HttpNetworkSession()
    : http_stream_factory_(
          std::make_unique<HttpBasicStreamFactory>(this)),
      normal_socket_pool_(
          std::make_unique<TransportClientSocketPool>(
              kDefaultMaxSockets,
              kDefaultMaxSocketsPerGroup)) {

}


HttpNetworkSession::~HttpNetworkSession() {}

ClientSocketPool* HttpNetworkSession::GetClientSocketPool(std::string type) {
  if (type == kWsScheme) {
    return websocket_socket_pool_.get();
  }
  return normal_socket_pool_.get();
}

}  // namespace net
}  // namespace tit