//
// Created by titto on 2022/5/28.
//

#include "http_cache_transaction.h"

#include "core/base/net_error.h"
#include "core/http/cache/http_cache.h"

namespace tit {
namespace net {

HttpCacheTransaction::HttpCacheTransaction(HttpCache *cache)
    : cache_(cache) {}

int HttpCacheTransaction::Start(HttpRequestInfo *request_info) {
  request_info_ = request_info;
  int rv = OK;
  do {
    rv = DoPrepareCache();
    if (rv != OK) break;
    rv = DoSendRequest();
    if (rv != OK) break;
    rv = DoReadResponse();
    if (rv != OK) break;
  } while (false);
  network_trans_->End();
  return rv;
}

int HttpCacheTransaction::Restart() { return 0; }

const HttpResponseInfo *HttpCacheTransaction::GetResponseInfo() const {
  return nullptr;
}

int HttpCacheTransaction::DoPrepareCache() { return OK; }

int HttpCacheTransaction::DoSendRequest() {
  network_trans_ = cache_->network_layer_->CreateTransaction();
  if (network_trans_.get() == nullptr) return ERR_OUT_OF_MEMORY;
  int rv = network_trans_->Start(request_info_);
  return rv;
}

int HttpCacheTransaction::DoReadResponse() {
  network_trans_->GetResponseInfo();
  return OK;
}
int HttpCacheTransaction::End() { return network_trans_->End(); }

}  // namespace net
}  // namespace tit