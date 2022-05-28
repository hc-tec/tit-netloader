//
// Created by titto on 2022/5/28.
//

#include "http_network_transaction.h"

#include "core/base/net_error.h"

namespace tit {
namespace net {

HttpNetworkTransaction::HttpNetworkTransaction(HttpNetworkSession *session)
    : session_(session) {}

HttpNetworkTransaction::~HttpNetworkTransaction() {}

int HttpNetworkTransaction::Start(HttpRequestInfo *request_info) {
  request_info_ = request_info;

  return OK;
}

int HttpNetworkTransaction::Restart() { return 0; }

const HttpResponseInfo *HttpNetworkTransaction::GetResponseInfo() const {
  return &response_info_;
}

}  // namespace net
}  // namespace tit