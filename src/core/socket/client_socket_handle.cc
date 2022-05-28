//
// Created by titto on 2022/5/28.
//

#include "client_socket_handle.h"

#include "core/socket/tcp/stream_socket.h"

namespace tit {
namespace net {

ClientSocketHandle::ClientSocketHandle() {}

ClientSocketHandle::~ClientSocketHandle() {}

void ClientSocketHandle::CloseSocket() {
  socket_->Disconnect();
}

void ClientSocketHandle::SetSocket(std::unique_ptr<StreamSocket> socket) {
  socket_ = std::move(socket);
}

std::unique_ptr<StreamSocket> ClientSocketHandle::PassSocket() {
  return std::move(socket_);
}

}  // namespace net
}  // namespace tit