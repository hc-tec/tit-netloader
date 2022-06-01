//
// Created by titto on 2022/6/1.
//

#ifndef TIT_NETLOADER_SSL_CONN_H
#define TIT_NETLOADER_SSL_CONN_H

#include "core/socket/tcp/conn.h"

#include <co/so/ssl.h>

#include "core/socket/tcp/ssl_context.h"

namespace tit {
namespace net {

class SSLConn : public TcpConn {
 public:

  explicit SSLConn(SSLContext* ssl_ctx, int sock)
      : TcpConn(sock),
        ssl_ctx_(ssl_ctx) {}

  ~SSLConn() override {};

  int Recv(void* buf, int n, int ms) override {
    return ssl::recv(ssl_ctx_->ssl_ctx(), buf, n);
  }

  int Recvn(void* buf, int n, int ms) override {
    return ssl::recvn(ssl_ctx_->ssl_ctx(), buf, n);
  }

  int Send(const void* buf, int n, int ms) override {
    return ssl::send(ssl_ctx_->ssl_ctx(), buf, n);
  }

 private:
  SSLContext* ssl_ctx_;

};

class SSLConnFactory {
 public:
  using Ptr = SSLConn::Ptr;
  SSLConn::Ptr Create(SSLContext* ssl_ctx, int fd) {
    return std::make_shared<SSLConn>(ssl_ctx, fd);
  }
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_SSL_CONN_H
