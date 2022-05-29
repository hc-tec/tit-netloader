//
// Created by titto on 2022/5/28.
//

#include "http_basic_stream.h"

#include "core/base/net_error.h"
#include "core/http/request/http_request_info.h"
#include "core/http/response/http_response_info.h"
#include "core/socket/tcp/stream_socket.h"
#include "core/socket/client_socket_handle.h"
#include "log/logging.h"

namespace tit {
namespace net {

HttpBasicStream::HttpBasicStream(std::unique_ptr<ClientSocketHandle> connection,
                                 bool using_proxy)
    : using_proxy_(using_proxy),
      connection_(std::move(connection)) {

}

HttpBasicStream::~HttpBasicStream() {}

void HttpBasicStream::RegisterRequest(HttpRequestInfo *request_info) {
  request_info_ = request_info;
}

int HttpBasicStream::InitializeStream() { return 0; }

int HttpBasicStream::SendRequest(HttpResponseInfo* response_info) {
  response_info_ = response_info;
  std::string request_line = request_info_->GenerateRequestLine();

  std::string request = request_line +
                        request_info_->headers.ToString() +
                        request_info_->body->ToString();
  LOG(INFO) << "Send Request data: \n" << request;
  connection_->socket()->Connect(request_info_->address);
  connection_->socket()->Write(request.data(), request.size());
  return OK;
}

int HttpBasicStream::ReadResponseHeaders() {
  char buf[2048];
  connection_->socket()->Read(buf, 2048);
  LOG(INFO) << "Read Response data: \n" << buf;
  return OK;
}

int HttpBasicStream::ReadResponseBody() { return 0; }

void HttpBasicStream::Close() {
  StreamSocket* socket = connection_->socket();
  socket->Disconnect();
}



}  // namespace net
}  // namespace tit