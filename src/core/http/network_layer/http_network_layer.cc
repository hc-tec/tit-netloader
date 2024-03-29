//
// Created by titto on 2022/5/28.
//

#include "http_network_layer.h"

#include "core/http/network_layer/http_network_transaction.h"

namespace tit {
namespace net {

HttpNetworkLayer::HttpNetworkLayer(HttpNetworkSession* session)
    : session_(session) {}

std::unique_ptr<HttpTransaction> HttpNetworkLayer::CreateTransaction(
    URLRequestContext* url_request_context) {
  return std::make_unique<HttpNetworkTransaction>(url_request_context, session_);
}

HttpNetworkSession* HttpNetworkLayer::GetSession() { return session_; }

HttpNetworkLayer::~HttpNetworkLayer() {}

}  // namespace net
}  // namespace tit