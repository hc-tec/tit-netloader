//
// Created by titto on 2022/6/1.
//

#include "ssl_client_socket_pool.h"

#include "core/socket/tcp/ssl_client_socket.h"

namespace tit {
namespace net {

std::unique_ptr<StreamSocket> SSLClientSocketPool::CreateSocket() {
  return std::make_unique<SSLClientSocket>();
}
SSLClientSocketPool::SSLClientSocketPool(int max_sockets,
                                         int max_sockets_per_group)
    : TransportClientSocketPool(max_sockets, max_sockets_per_group) {}

}  // namespace net
}  // namespace tit