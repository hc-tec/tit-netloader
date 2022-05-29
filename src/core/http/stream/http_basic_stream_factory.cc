//
// Created by titto on 2022/5/28.
//

#include "http_basic_stream_factory.h"

#include "core/http/stream/http_basic_stream.h"
#include "core/socket/client_socket_handle.h"

namespace tit {
namespace net {

HttpBasicStreamFactory::HttpBasicStreamFactory(HttpNetworkSession *session)
    : HttpStreamFactory(session) {

}

HttpBasicStreamFactory::~HttpBasicStreamFactory() {}

std::unique_ptr<HttpStream> HttpBasicStreamFactory::RequestStream(
    std::unique_ptr<ClientSocketHandle> connection,
    HttpRequestInfo *request_info,
    HttpStream::Delegate* delegate) {
  std::unique_ptr<HttpBasicStream> stream = std::make_unique<HttpBasicStream>(
      std::move(connection), false, delegate
      );
  stream->InitializeStream();
  stream->RegisterRequest(request_info);
  return stream;
}



}  // namespace net
}  // namespace tit