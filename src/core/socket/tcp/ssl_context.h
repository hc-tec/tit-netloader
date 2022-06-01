//
// Created by titto on 2022/6/1.
//

#ifndef TIT_NETLOADER_SSL_CONTEXT_H
#define TIT_NETLOADER_SSL_CONTEXT_H

#include "log/logging.h"

namespace tit {
namespace net {

class SSLContext {
 public:

  SSLContext();
  ~SSLContext();

  void* ssl_ctx() { return ssl_ctx_; }

 private:
  void* client_ctx_;
  void* ssl_ctx_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_SSL_CONTEXT_H
