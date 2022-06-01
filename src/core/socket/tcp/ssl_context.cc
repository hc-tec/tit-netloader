//
// Created by titto on 2022/6/1.
//

#include "ssl_context.h"

#include <co/so/ssl.h>

namespace tit {
namespace net {


SSLContext::SSLContext() {
  client_ctx_ = ssl::new_client_ctx();
  if (client_ctx_ == nullptr) {
    LOG(ERROR) << "ssl connect new client contex failed: " << ssl::strerror();
    return;
  }
  ssl_ctx_ = ssl::new_ssl(client_ctx_);
  if (ssl_ctx_ == nullptr) {
    LOG(ERROR) << "ssl connect new SSL failed: " << ssl::strerror();
  }
}

SSLContext::~SSLContext() {
  ssl::free_ctx(client_ctx_);
  ssl::free_ssl(ssl_ctx_);
}

}  // namespace net
}  // namespace tit