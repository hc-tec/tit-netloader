//
// Created by titto on 2022/5/28.
//

#include "transport_client_socket.h"

#include "core/socket/tcp/tcp_socket.h"

namespace tit {
namespace net {

TransportClientSocket::TransportClientSocket()
    : StreamSocket(),
      socket_(TcpSocket::Create()) {}

TransportClientSocket::~TransportClientSocket() {}

int TransportClientSocket::Connect(const Address::Ptr& address) {
  return socket_->Connect(address, -1);
}

void TransportClientSocket::Disconnect() {
  socket_->Close();
}

bool TransportClientSocket::IsConnected() const {
  return socket_->connected();
}

int TransportClientSocket::Read(char* buf, int buf_len) {
  return socket_->Recv(buf, buf_len, -1);
}

int TransportClientSocket::Write(char* buf, int buf_len) {
  return socket_->Send(buf, buf_len, -1);
}

const Address::Ptr& TransportClientSocket::GetPeerAddress() const {
  return socket_->remote_addr();
}

const Address::Ptr& TransportClientSocket::GetLocalAddress() const {
  return socket_->local_addr();
}

int TransportClientSocket::ReadFix(char* buf, int buf_len) {
  return socket_->Recvn(buf, buf_len, -1);
}

}  // namespace net
}  // namespace tit