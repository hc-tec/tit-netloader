//
// Created by titto on 2022/6/1.
//

#ifndef TIT_NETLOADER_SSL_CLIENT_SOCKET_POOL_H
#define TIT_NETLOADER_SSL_CLIENT_SOCKET_POOL_H

#include "core/socket/tcp/transport_client_socket_pool.h"

namespace tit {
namespace net {

class SSLClientSocketPool : public TransportClientSocketPool {
 public:

  SSLClientSocketPool(int max_sockets,
                            int max_sockets_per_group);

  std::unique_ptr<StreamSocket> CreateSocket() override;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_SSL_CLIENT_SOCKET_POOL_H
