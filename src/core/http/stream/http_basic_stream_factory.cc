//
// Created by titto on 2022/5/28.
//

#include "http_basic_stream_factory.h"

#include "core/http/stream/http_basic_stream.h"
#include "core/http/request/http_request_info.h"
#include "core/http/network_layer/http_network_session.h"
#include "core/socket/client_socket_handle.h"
#include "core/socket/client_socket_pool.h"
#include "core/socket/tcp/stream_socket.h"


namespace tit {
namespace net {

HttpBasicStreamFactory::HttpBasicStreamFactory(HttpNetworkSession *session)
    : HttpStreamFactory(session) {

}

HttpBasicStreamFactory::~HttpBasicStreamFactory() {}

std::unique_ptr<HttpStream> HttpBasicStreamFactory::RequestStream(
    ClientSocketHandle* connection,
    HttpRequestInfo *request_info,
    HttpStream::Delegate* delegate) {
  std::unique_ptr<HttpBasicStream> stream = std::make_unique<HttpBasicStream>(
      std::move(connection), false, delegate
      );
  ClientSocketPool* pool = session_->GetClientSocketPool(
      request_info->url.scheme());
  int rv = pool->RequestSocket(connection->group_id(), connection);
  stream->InitializeStream();
  stream->RegisterRequest(request_info);
  return stream;
}

void HttpBasicStreamFactory::RecycleStream(
    ClientSocketHandle* connection,
    HttpRequestInfo *request_info) {
  ClientSocketPool* pool = session_->GetClientSocketPool(
      request_info->url.scheme());
  // if reusable
  int rv = pool->ReleaseSocket(connection->group_id(), connection->PassSocket());
}

}  // namespace net
}  // namespace tit