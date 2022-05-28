//
// Created by titto on 2022/5/28.
//

#include "http_network_transaction.h"

#include "core/base/net_error.h"
#include "core/http/stream/http_stream.h"
#include "core/http/stream/http_stream_factory.h"
#include "core/http/network_layer/http_network_session.h"
#include "core/socket/tcp/transport_client_socket.h"
#include "core/socket/client_socket_handle.h"

namespace tit {
namespace net {

HttpNetworkTransaction::HttpNetworkTransaction(HttpNetworkSession *session)
    : session_(session) {}

HttpNetworkTransaction::~HttpNetworkTransaction() {}

int HttpNetworkTransaction::Start(HttpRequestInfo *request_info) {
  request_info_ = request_info;
  HttpStreamFactory* stream_factory = session_->http_stream_factory();

  std::unique_ptr<TransportClientSocket> socket = std::make_unique<TransportClientSocket>();
  std::unique_ptr<ClientSocketHandle> handle;
  handle->SetSocket(std::move(socket));
  stream_ = stream_factory->RequestStream(std::move(handle), request_info);
  stream_->SendRequest(&response_info_);
  return OK;
}

int HttpNetworkTransaction::Restart() { return 0; }

const HttpResponseInfo *HttpNetworkTransaction::GetResponseInfo() const {
  return &response_info_;
}

}  // namespace net
}  // namespace tit