//
// Created by titto on 2022/5/28.
//

#include "http_basic_stream.h"

#include "core/base/net_error.h"
#include "core/http/request/http_request_info.h"
#include "core/http/response/http_response_info.h"
#include "core/http/response//http_response_parser.h"
#include "core/network/request_params.h"
#include "core/socket/tcp/stream_socket.h"
#include "core/socket/client_socket_handle.h"
#include "log/logging.h"

namespace tit {
namespace net {

HttpBasicStream::HttpBasicStream(ClientSocketHandle* connection,
                                 bool using_proxy,
                                 HttpStream::Delegate* delegate)
    : delegate_(delegate),
      using_proxy_(using_proxy),
      connection_(connection),
      response_parser_(std::make_unique<HttpResponseParser>()) {

}

HttpBasicStream::~HttpBasicStream() {}

void HttpBasicStream::RegisterRequest(HttpRequestInfo *request_info,
                                      const RequestParams* request_params) {
  request_params_ = request_params;
  request_info_ = request_info;
}

int HttpBasicStream::InitializeStream() {

}

int HttpBasicStream::SendRequest(HttpResponseInfo* response_info) {

  response_parser_->set_response(response_info);
  response_info_ = response_info;
  response_info_->url = request_info_->url;
  response_info_->address = request_info_->address;
  response_info_->body = std::make_shared<HttpResponseBufferBody>();

  std::string request_line = request_info_->GenerateRequestLine(
      request_params_->protocol_type);

  std::string request = request_line +
                        request_info_->headers.ToString() +
      (request_info_->body ? request_info_->body->ToString() : "");

  if (!connection_->socket()->IsConnected()) {
    bool connected = connection_->socket()->Connect(request_info_->address);
    if (!connected) {
      return ERR_CONNECTION_FAILED;
    }
  }
  LOG(INFO) << "Send Request" << request_info_;
  LOG(TRACE) << "\n" << request;
  delegate_->OnConnected(request_info_);
  delegate_->OnBeforeRequest(request_info_, request);
  connection_->socket()->Write(request.data(), request.size());
  return OK;
}

int HttpBasicStream::ReadResponseHeaders() {
  char buf[2048];
  int buf_size = connection_->socket()->Read(buf, 2048);
  LOG(INFO) << "Read Response data: \n" << buf;
  response_info_->buffer.Buffer(buf, buf_size);
  response_parser_->ParseHeaders();
  delegate_->OnResponseHeaderReceived(request_info_, response_info_,
                                      std::string(buf, buf_size));
  return OK;
}

int HttpBasicStream::ReadResponseBody() {
  int remain = response_parser_->RemainSize();
  if (remain <= 0) {
    delegate_->OnResponseBodyReceived(request_info_, response_info_, "");
    return OK;
  }

  char buf[remain];
  int buf_size = connection_->socket()->Read(buf, remain);
  if (buf_size == 0) {
    delegate_->OnConnectClosed(request_info_, response_info_);
    return ERR_CONNECTION_CLOSED;
  }
  LOG(INFO) << "Read Response data: \n" << buf;
  response_info_->buffer.Buffer(buf, buf_size);
  response_parser_->ParseBody();
  delegate_->OnResponseBodyReceived(request_info_,
                                    response_info_,
                                    std::string(buf, buf_size));
  return OK;
}

void HttpBasicStream::Close() {
  StreamSocket* socket = connection_->socket();
  socket->Disconnect();
}

}  // namespace net
}  // namespace tit