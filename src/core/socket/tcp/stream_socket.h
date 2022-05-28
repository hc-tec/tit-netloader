//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_STREAM_SOCKET_H
#define TIT_NETLOADER_STREAM_SOCKET_H

#include "core/socket/socket.h"
#include "core/socket/tcp/address.h"

namespace tit {
namespace net {

class StreamSocket : public Socket {
 public:
  StreamSocket() : Socket() {}
  virtual ~StreamSocket() override {}

  virtual int Connect(const Address::Ptr& address) = 0;

  virtual void Disconnect() = 0;

  virtual bool IsConnected() const = 0;

  virtual const Address::Ptr& GetPeerAddress() const = 0;

  // Copies the local address to |address| and returns a network error code.
  // ERR_SOCKET_NOT_CONNECTED will be returned if the socket is not bound.
  virtual const Address::Ptr& GetLocalAddress() const = 0;

  virtual int Read(char* buf, int buf_len) override = 0;

  virtual int ReadFix(char* buf, int buf_len) override = 0;

  virtual int Write(char* buf, int buf_len) override = 0;

};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_STREAM_SOCKET_H
