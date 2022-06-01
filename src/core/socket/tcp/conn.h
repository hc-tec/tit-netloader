//
// Created by titto on 2022/4/21.
//

#ifndef TIT_COROUTINE_CONN_H
#define TIT_COROUTINE_CONN_H

#include "address.h"

#include "co/co/sock.h"

namespace tit {

namespace net {

class ConnectionInterface {
 public:
  using Ptr = std::shared_ptr<ConnectionInterface>;

  ConnectionInterface() = default;
  virtual ~ConnectionInterface() = default;

  virtual int Recv(void* buf, int n, int ms) = 0;
  virtual int Recvn(void* buf, int n, int ms) = 0;
  virtual int Send(const void* buf, int n, int ms) = 0;

  virtual int Close(int ms) = 0;
  virtual int Reset(int ms) = 0;

  virtual int socket() = 0;
};

class ConnFactory {
 public:
  using type = ConnectionInterface::Ptr;
  virtual ConnectionInterface::Ptr Create(int fd) {}
};

class TcpConn : public ConnectionInterface {
 public:
  explicit TcpConn(int sock) : sock_(sock) {}
  virtual ~TcpConn() override { this->Close(0); }

  virtual int Recv(void* buf, int n, int ms) override {
    return co::recv(sock_, buf, n, ms);
  }

  virtual int Recvn(void* buf, int n, int ms) override {
    return co::recvn(sock_, buf, n, ms);
  }

  virtual int Send(const void* buf, int n, int ms) override {
    return co::send(sock_, buf, n, ms);
  }

  virtual int Close(int ms) override {
    int r = sock_ != -1 ? co::close(sock_, ms) : 0;
    sock_ = -1;
    return r;
  }

  virtual int Reset(int ms) override {
    int r = sock_ != -1 ? co::reset_tcp_socket(sock_, ms) : 0;
    sock_ = -1;
    return r;
  }

  virtual int socket() override {
    return sock_;
  }

 protected:
  int sock_;
};

class TcpConnFactory : public ConnFactory {
 public:
  using Ptr = TcpConn::Ptr;
  TcpConn::Ptr Create(int fd) override {
    return std::make_shared<TcpConn>(fd);
  }
};

}  // namespace net

}  // namespace tit

#endif  // TIT_COROUTINE_CONN_H
