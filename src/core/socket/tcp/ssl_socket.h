//
// Created by titto on 2022/6/1.
//

#ifndef TIT_NETLOADER_SSL_SOCKET_H
#define TIT_NETLOADER_SSL_SOCKET_H

#include <co/so/ssl.h>

#include "core/socket/tcp/conn.h"
#include "core/socket/tcp/ssl_conn.h"
#include "core/socket/tcp/ssl_context.h"
#include "core/socket/tcp/tcp_socket.h"


namespace tit {
namespace net {

template <typename SSLConnFactory>
class SSLSocketTemplate : public TcpSocketTemplate<TcpConnFactory> {

  void Init(int fd) override {
    if (unlikely(fd == kInvalidFd)) {
      LOG(ERROR) << "socket create error";
    } else {
      fd_ = fd;
      co::set_reuseaddr(fd_);
      conn_ = ssl_conn_factory_.Create(&ssl_context_, fd_);
      connected_ = true;
      InitLocalAddr();
      InitRemoteAddr();
    }
  }

  bool Bind(const Address::Ptr& addr) override {
    if (!is_valid()) {
      CreateSocket();
    }
//    CHECK(is_valid());
    if (co::bind(fd(), addr->addr(), addr->addrlen())) {
      LOG(ERROR) << "bind error";
      return false;
    }
    return true;
  }


  Ptr Accept() override;

  bool Connect(const Address::Ptr& address, uint64_t timeout_ms = -1) override;

//  void set_ssl_context(SSLContext* ssl_context) { ssl_context_ = ssl_context; }

 private:
  SSLContext ssl_context_;

  SSLConnFactory ssl_conn_factory_;
};


template <typename ConnFactory>
typename SSLSocketTemplate<ConnFactory>::Ptr SSLSocketTemplate<ConnFactory>::Accept() {
//  CHECK(is_valid());
  SSLSocketTemplate::Ptr sock = SSLSocketTemplate::Create(family(), type(), protocol());
  int client_sock = co::accept(fd(), nullptr, nullptr);
  if (client_sock < 0) {
    LOG(ERROR) << "accept error";
  }
  sock->Init(client_sock);
  return sock;
}

template <typename ConnFactory>
bool SSLSocketTemplate<ConnFactory>::Connect(const Address::Ptr& address,
                                             uint64_t ms) {
  if (!is_valid()) {
    CreateSocket();
  }

//  CHECK(is_valid());
  if(co::connect(fd_, address->addr(), address->addrlen(), ms)) {
    LOG(ERROR) << "Connect error";
    return false;
  }

  ssl::set_fd(ssl_context_.ssl_ctx(), fd_);
  if(ssl::connect(ssl_context_.ssl_ctx()) != 1) {
    LOG(ERROR) << "ssl connect failed: "
               << ssl::strerror(ssl_context_.ssl_ctx());
    return false;
  }

  InitLocalAddr();
  InitRemoteAddr();
  return true;
}

using SSLSocket = SSLSocketTemplate<SSLConnFactory>;

}  // namespace net

}  // namespace tit


#endif  // TIT_NETLOADER_SSL_SOCKET_H
