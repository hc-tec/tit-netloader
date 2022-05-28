//
// Created by titto on 2022/4/21.
//

#ifndef TIT_COROUTINE_SOCKET_H
#define TIT_COROUTINE_SOCKET_H

#include "co/co/sock.h"
#include "address.h"
#include "conn.h"

namespace tit {
namespace net {

static constexpr int kInvalidFd = -1;

enum Type {
  kTcp = SOCK_STREAM,
  kUdp = SOCK_DGRAM
};

template <typename ConnFactory>
class TcpSocketTemplate {
 public:
  using Ptr = std::shared_ptr<TcpSocketTemplate>;

  using ConnType = typename ConnFactory::type;

  TcpSocketTemplate() : TcpSocketTemplate(kIpv4, kTcp, 0) {}

  TcpSocketTemplate(Family family, Type type, int protocol)
      : fd_(kInvalidFd),
        family_(family),
        type_(type),
        protocol_(protocol),
        connected_(false) {}

  static Ptr Create() {
    return std::make_shared<TcpSocketTemplate>();
  }

  static Ptr Create(Family family, Type type, int protocol) {
    return std::make_shared<TcpSocketTemplate>(family, type, protocol);
  }

//  static Ptr Create(Socket<ConnFactory>* sock) {
//    return std::make_shared<Socket>(sock);
//  }

  void Init(int fd) {
    if (unlikely(fd == kInvalidFd)) {
      LOG(ERROR) << "socket create error";
    } else {
      fd_ = fd;
      co::set_reuseaddr(fd_);
      conn_ = conn_factory_.Create(fd_);
      connected_ = true;
      InitLocalAddr();
      InitRemoteAddr();
    }
  }

  void CreateSocket() {
    fd_ = socket(family_, type_, protocol_);
    Init(fd_);
  }

  virtual int Recv(void* buf, int n, int ms) {
//    CHECK(connected_);
    return conn_->Recv(buf, n, ms);
  }

  virtual int Recvn(void* buf, int n, int ms) {
//    CHECK(connected_);
    return conn_->Recvn(buf, n, ms);
  }

  virtual int Send(const void* buf, int n, int ms) {
//    CHECK(connected_);
    return conn_->Send(buf, n, ms);
  }

  virtual bool Close(int ms = -1) {
    if (!connected_) return true;
    connected_ = false;
    return conn_->Close(ms) == 0;
  }

  virtual int Reset(int ms) {
//    CHECK(connected_);
    return conn_->Reset(ms);
  }

  int fd() const { return fd_; }
  Family family() { return family_; }
  Type type() { return type_; }
  int protocol() const { return protocol_; }
  bool connected() const { return connected_; }

  bool is_valid() const { return fd_ != kInvalidFd; }

  void InitLocalAddr();
  void InitRemoteAddr();

  const Address::Ptr& local_addr() const { return local_addr_; }
  const Address::Ptr& remote_addr() const { return remote_addr_; }

  bool Bind(const Address::Ptr& addr) {
    if (!is_valid()) {
      CreateSocket();
    }
    CHECK(is_valid());
    if (co::bind(fd(), addr->addr(), addr->addrlen())) {
      LOG(ERROR) << "bind error";
      return false;
    }
    return true;
  }

  bool Listen(int backlog = kMaxConn) {
    CHECK(is_valid());
    if (co::listen(fd(), backlog)) {
      LOG(ERROR) << "listen error";
      return false;
    }
    return true;
  }

  Ptr Accept();

  bool Connect(const Address::Ptr& address, uint64_t timeout_ms = -1);

  ConnType get_conn() { return conn_; }

 private:

  static const int kMaxConn = 4096;

  int fd_;
  Family family_;
  Type type_;
  int protocol_;

  ConnFactory conn_factory_;
  ConnType conn_;

  Address::Ptr local_addr_;
  Address::Ptr remote_addr_;

 protected:
  bool connected_;
};

template <typename ConnFactory>
void TcpSocketTemplate<ConnFactory>::InitLocalAddr() {
  if (local_addr_) return;
  switch (family_) {
    case AF_INET:
      local_addr_.reset(new IPv4Address());
      break;
    case AF_INET6:
      local_addr_.reset(new IPv6Address());
      break;
  }
  socklen_t addrlen = local_addr_->addrlen();
  if (getsockname(fd_, local_addr_->addr(), &addrlen)) {
    LOG(ERROR) << "unknown address";
  }
}

template <typename ConnFactory>
void TcpSocketTemplate<ConnFactory>::InitRemoteAddr() {
  if (remote_addr_) return;
  switch (family_) {
    case AF_INET:
      remote_addr_.reset(new IPv4Address());
      break;
    case AF_INET6:
      remote_addr_.reset(new IPv6Address());
      break;
  }
  socklen_t addrlen = remote_addr_->addrlen();
  if (getsockname(fd_, remote_addr_->addr(), &addrlen)) {
    LOG(ERROR) << "unknown address";
  }
}

template <typename ConnFactory>
typename TcpSocketTemplate<ConnFactory>::Ptr TcpSocketTemplate<ConnFactory>::Accept() {
  CHECK(is_valid());
  TcpSocketTemplate::Ptr sock = TcpSocketTemplate::Create(family(), type(), protocol());
  int client_sock = co::accept(fd(), nullptr, nullptr);
  if (client_sock < 0) {
    LOG(ERROR) << "accept error";
  }
  sock->Init(client_sock);
  return sock;
}

template <typename ConnFactory>
bool TcpSocketTemplate<ConnFactory>::Connect(const Address::Ptr& address,
                              uint64_t ms) {
  if (!is_valid()) {
    CreateSocket();
  }
//  CHECK(is_valid());
  if(co::connect(fd(), address->addr(), address->addrlen(), ms)) {
    LOG(ERROR) << "connect error";
    return false;
  }

  InitLocalAddr();
  InitRemoteAddr();
  return true;
}

using TcpSocket = TcpSocketTemplate<TcpConnFactory>;

}  // namespace net

}  // namespace tit


#endif  // TIT_COROUTINE_SOCKET_H
