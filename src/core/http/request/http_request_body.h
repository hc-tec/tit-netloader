//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_REQUEST_BODY_H
#define TIT_NETLOADER_HTTP_REQUEST_BODY_H

#include <map>
#include <memory>
#include <string>

#include "http_request_headers.h"
#include "log/log_stream.h"

namespace tit {
namespace net {

class HttpRequestBody {
 public:

  virtual void DeclareHeaders(HttpRequestHeaders& headers) = 0;

  virtual std::string ToString() = 0;
};

class HttpRequestBufferBody : public HttpRequestBody {
 public:
  HttpRequestBufferBody(const std::string& content_type,
                        const std::string& buffer);

  void DeclareHeaders(HttpRequestHeaders& headers) override;

  std::string ToString() override {
    return buffer_;
  }

  const std::string& content_type() { return content_type_; };
  const std::string& buffer() { return buffer_; }

 private:
  std::string content_type_;
  std::string buffer_;
};

log::LogStream& operator<<(log::LogStream& stream,
                           std::shared_ptr<HttpRequestBody> body);

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_REQUEST_BODY_H
