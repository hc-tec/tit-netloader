//
// Created by titto on 2022/5/28.
//

#include "http_network_transaction.h"

#include "core/base/net_error.h"
#include "core/http/http_request_observer.h"
#include "core/http/http_transaction_factory.h"
#include "core/http/network_layer/http_network_session.h"
#include "core/http/request/http_request_info.h"
#include "core/http/stream/http_stream_factory.h"
#include "core/network/host_resolver.h"
#include "core/network/network_context.h"
#include "core/network/resource_scheduler.h"
#include "core/socket/client_socket_handle.h"
#include "core/socket/tcp/transport_client_socket.h"
#include "core/socket/client_socket_pool.h"
#include "core/url_request/url_request_context_builder.h"

namespace tit {
namespace net {

HttpNetworkTransaction::HttpNetworkTransaction(HttpNetworkSession *session)
    : session_(session) {}

HttpNetworkTransaction::~HttpNetworkTransaction() {}

int HttpNetworkTransaction::Start(HttpRequestInfo *request_info) {
  request_info_ = request_info;
  int rv = DoHostResolve();
  if (rv != OK) return rv;
  HttpStreamFactory* stream_factory = session_->http_stream_factory();

  ClientSocketPool::GroupId group_id(request_info_->url);

  client_socket_handle_ = std::make_unique<ClientSocketHandle>(group_id);

  stream_ = stream_factory->RequestStream(client_socket_handle_.get(),
                                          request_info,
                                          this);
  rv = stream_->SendRequest(&response_info_);
  if (rv != OK) return rv;
  rv = stream_->ReadResponseHeaders();
  if (rv != OK) return rv;
  rv = stream_->ReadResponseBody();
  if (rv != OK) return rv;
  LOG(INFO) << "Receive Response: " << response_info_;
  return OK;
}

int HttpNetworkTransaction::Restart() { return 0; }

int HttpNetworkTransaction::End() {
  HttpStreamFactory* stream_factory = session_->http_stream_factory();
  stream_factory->RecycleStream(
      client_socket_handle_.get(),
      request_info_);
}

const HttpResponseInfo *HttpNetworkTransaction::GetResponseInfo() const {
  return &response_info_;
}

bool HttpNetworkTransaction::NeedHostResolve() {
  if (request_info_->url.is_ip()) {
    if (request_info_->address.get() == nullptr) {
      request_info_->SetAddressByUrl();
    }
    return false;
  }
  return true;
}

int HttpNetworkTransaction::DoHostResolve() {
  if (!NeedHostResolve()) {
    OnHostResolved(request_info_, false,
                   request_info_->address->ToString());
    return OK;
  }
  auto host_resolver = session_->host_resolver()->Create();
  int rv = host_resolver->Start(request_info_->url);
  if (rv != 0) {
    OnHostResolvedError(request_info_);
    return rv;
  }
  request_info_->address = host_resolver->GetAddressResult();
  OnHostResolved(request_info_, true,
                 request_info_->address->ToString());
  return OK;
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
    HttpRequestInfo *request_info,
    HttpResponseInfo *response_info,
    const std::string& raw_response) {
  LOG(INFO) << "OnResponseHeaderReceived";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnResponseHeaderReceived(session_,
                                               request_info,
                                               response_info,
                                               raw_response);
    }
  }
}

void HttpNetworkTransaction::OnResponseBodyReceived(
    HttpRequestInfo *request_info,
    HttpResponseInfo *response_info,
    const std::string& raw_response) {
  LOG(INFO) << "OnResponseBodyReceived";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnResponseBodyReceived(session_,
                                             request_info,
                                             response_info,
                                             raw_response);
    }
  }
}

void HttpNetworkTransaction::OnHostResolved(HttpRequestInfo* request_info,
                                            bool need_host_resolve,
                                            const std::string& dns_ip) {
  LOG(INFO) << "OnHostResolved";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnHostResolved(session_,
                                     request_info,
                                     need_host_resolve,
                                     dns_ip);
    }
  }
}

void HttpNetworkTransaction::OnHostResolvedError(
    HttpRequestInfo* request_info) {
  LOG(INFO) << "OnHostResolved";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnHostResolveError(session_, request_info);
    }
  }
}

void HttpNetworkTransaction::OnConnectClosed(HttpRequestInfo* request_info,
                                             HttpResponseInfo* response_info) {

  LOG(INFO) << "OnConnectClosed";
  auto& observers = session_->network_context()->url_request_observers_;
  for (auto& observer : observers) {
    auto observer_share = observer.lock();
    if (observer_share.use_count()) {
      observer_share->OnConnectClosed(session_, request_info, response_info);
    }
  }

}

}  // namespace net
}  // namespace tit