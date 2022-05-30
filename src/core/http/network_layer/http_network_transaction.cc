//
// Created by titto on 2022/5/28.
//

#include "http_network_transaction.h"

#include "core/base/net_error.h"
#include "core/http/http_request_observer.h"
#include "core/http/http_transaction_factory.h"
#include "core/http/network_layer/http_network_session.h"
#include "core/http/stream/http_stream_factory.h"
#include "core/network/host_resolver.h"
#include "core/network/network_context.h"
#include "core/network/resource_scheduler.h"
#include "core/socket/client_socket_handle.h"
#include "core/socket/tcp/transport_client_socket.h"
#include "core/url_request/url_request_context_builder.h"

namespace tit {
namespace net {

HttpNetworkTransaction::HttpNetworkTransaction(HttpNetworkSession *session)
    : session_(session) {}

HttpNetworkTransaction::~HttpNetworkTransaction() {}

int HttpNetworkTransaction::Start(HttpRequestInfo *request_info) {
  request_info_ = request_info;
  HttpStreamFactory* stream_factory = session_->http_stream_factory();

  std::unique_ptr<TransportClientSocket> socket =
      std::make_unique<TransportClientSocket>();

  std::unique_ptr<ClientSocketHandle> handle =
      std::make_unique<ClientSocketHandle>();

  handle->SetSocket(std::move(socket));
  stream_ = stream_factory->RequestStream(std::move(handle),
                                          request_info,
                                          this);
  int rv = stream_->SendRequest(&response_info_);
  if (rv != OK) return rv;
  rv = stream_->ReadResponseHeaders();
  if (rv != OK) return rv;
  rv = stream_->ReadResponseBody();
  if (rv != OK) return rv;
  LOG(INFO) << "Receive Response: " << response_info_;
  return OK;
}

int HttpNetworkTransaction::Restart() { return 0; }

const HttpResponseInfo *HttpNetworkTransaction::GetResponseInfo() const {
  return &response_info_;
}

void HttpNetworkTransaction::OnConnected(HttpRequestInfo* request_info) {
  LOG(INFO) << "OnConnected";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnConnected(session_, request_info);
    }
  }
}

void HttpNetworkTransaction::OnBeforeRequest(HttpRequestInfo *request_info,
                                             std::string &request_msg) {
  LOG(INFO) << "OnBeforeRequest";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnBeforeRequest(session_, request_info, request_msg);
    }
  }
}

void HttpNetworkTransaction::OnResponseHeaderReceived(
    HttpResponseInfo *response_info, std::string raw_response) {
  LOG(INFO) << "OnResponseHeaderReceived";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnResponseHeaderReceived(session_,
                                               response_info,
                                               raw_response);
    }
  }
}

void HttpNetworkTransaction::OnResponseBodyReceived(
    HttpResponseInfo *response_info, std::string raw_response) {
  LOG(INFO) << "OnResponseBodyReceived";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnResponseBodyReceived(session_,
                                             response_info,
                                             raw_response);
    }
  }
}

}  // namespace net
}  // namespace tit