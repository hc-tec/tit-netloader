//
// Created by titto on 2022/6/1.
//

#include "ssl_client_socket.h"

#include "core/socket/tcp/ssl_socket.h"

namespace tit {
namespace net {


SSLClientSocket::SSLClientSocket() : TransportClientSocket() {
  socket_.reset();
  socket_ = std::make_unique<SSLSocket>();
}

}  // namespace net
}  // namespace tit