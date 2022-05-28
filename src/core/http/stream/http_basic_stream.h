//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_BASIC_STREAM_H
#define TIT_NETLOADER_HTTP_BASIC_STREAM_H

#include <memory>
#include <string>

#include "core/http/stream/http_stream.h"

namespace tit {
namespace net {

class HttpRequestInfo;
class HttpResponseInfo;
class ClientSocketHandle;

class HttpBasicStream : public HttpStream {
 public:
  HttpBasicStream(std::unique_ptr<ClientSocketHandle> connection,
                  bool using_proxy);

  HttpBasicStream(const HttpBasicStream&) = delete;
  HttpBasicStream& operator=(const HttpBasicStream&) = delete;

  ~HttpBasicStream() override;

  void RegisterRequest(HttpRequestInfo* request_info) override;
  int InitializeStream() override;
  int SendRequest(HttpResponseInfo* response_info) override;
  int ReadResponseHeaders() override;
  int ReadResponseBody() override;
  void Close() override;

 private:
  bool using_proxy_;
  std::unique_ptr<ClientSocketHandle> connection_;
  std::string read_buf_;
  HttpRequestInfo* request_info_;
  HttpResponseInfo* response_info_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_BASIC_STREAM_H
