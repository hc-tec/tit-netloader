//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_TRANSPORT_CLIENT_SOCKET_H
#define TIT_NETLOADER_TRANSPORT_CLIENT_SOCKET_H

#include "core/socket/tcp/address.h"
#include "core/socket/tcp/stream_socket.h"
#include "core/socket/tcp/tcp_socket.h"

namespace tit {
namespace net {

class TransportClientSocket : public StreamSocket {
 public:

  TransportClientSocket();
  ~TransportClientSocket() override;

  int Connect(const Address::Ptr& address) override;
  void Disconnect() override;
  bool IsConnected() const override;

  int Read(char* buf, int buf_len) override;

  int ReadFix(char* buf, int buf_len) override;

  int Write(char* buf, int buf_len) override;

  const Address::Ptr& GetPeerAddress() const override;
  const Address::Ptr& GetLocalAddress() const override;

 protected:
  TcpSocket::Ptr socket_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_TRANSPORT_CLIENT_SOCKET_H
