//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_CLIENT_SOCKET_HANDLE_H
#define TIT_NETLOADER_CLIENT_SOCKET_HANDLE_H

#include <memory>

namespace tit {
namespace net {

class StreamSocket;

class ClientSocketHandle {
 public:

  ClientSocketHandle();

  ClientSocketHandle(const ClientSocketHandle&) = delete;
  ClientSocketHandle& operator=(const ClientSocketHandle&) = delete;

  ~ClientSocketHandle();

  void CloseSocket();

  void SetSocket(std::unique_ptr<StreamSocket> socket);

  StreamSocket* socket() { return socket_.get(); }

  std::unique_ptr<StreamSocket> PassSocket();

 private:
  std::unique_ptr<StreamSocket> socket_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_CLIENT_SOCKET_HANDLE_H
