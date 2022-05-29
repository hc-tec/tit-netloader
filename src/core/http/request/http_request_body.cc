//
// Created by titto on 2022/5/28.
//

#include "http_request_body.h"

namespace tit {
namespace net {

HttpRequestBufferBody::HttpRequestBufferBody(const std::string& content_type,
                                             const std::string& buffer)
    : content_type_(content_type),
      buffer_(!buffer.empty() ? buffer : "") {

}

void HttpRequestBufferBody::DeclareHeaders(HttpRequestHeaders& headers) {
  if (!content_type_.empty()) {
    headers.PutHeaders(HttpRequestHeaders::CONTENT_TYPE, content_type_);
  }
}

log::LogStream& operator<<(log::LogStream& stream,
                           std::shared_ptr<HttpRequestBody> body) {
    stream << body->ToString();
}

}  // namespace net
}  // namespace tit