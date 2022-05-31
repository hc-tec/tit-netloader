//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_CLIENT_SOCKET_HANDLE_H
#define TIT_NETLOADER_CLIENT_SOCKET_HANDLE_H

#include <memory>

#include "core/socket/client_socket_pool.h"

namespace tit {
namespace net {

class StreamSocket;

class ClientSocketHandle {
 public:

  explicit ClientSocketHandle(const ClientSocketPool::GroupId& group_id);

  ClientSocketHandle(const ClientSocketHandle&) = delete;
  ClientSocketHandle& operator=(const ClientSocketHandle&) = delete;

  ~ClientSocketHandle();

  void CloseSocket();

  ClientSocketPool::GroupId group_id() { return group_id_; }

  void set_socket(std::unique_ptr<StreamSocket> socket);
  StreamSocket* socket() { return socket_.get(); }

  std::unique_ptr<StreamSocket> PassSocket();

 private:
  ClientSocketPool::GroupId group_id_;
  std::unique_ptr<StreamSocket> socket_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_CLIENT_SOCKET_HANDLE_H
