//
// Created by titto on 2022/6/1.
//

#ifndef TIT_NETLOADER_SSL_CLIENT_SOCKET_H
#define TIT_NETLOADER_SSL_CLIENT_SOCKET_H

#include "core/socket/tcp/transport_client_socket.h"

namespace tit {
namespace net {

class SSLClientSocket : public TransportClientSocket {
 public:
  SSLClientSocket();
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_SSL_CLIENT_SOCKET_H
