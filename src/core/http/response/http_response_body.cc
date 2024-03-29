//
// Created by titto on 2022/5/29.
//

#include "http_response_body.h"

#include <cstring>

namespace tit {
namespace net {

HttpResponseBufferBody::HttpResponseBufferBody()
    : IOBuffer() {}

HttpResponseBufferBody::~HttpResponseBufferBody() {}

size_t HttpResponseBufferBody::GetSize() {
  return this->IOBuffer::GetSize();
}

size_t HttpResponseBufferBody::Buffer(char* buf, size_t buf_size) {
  return this->IOBuffer::Buffer(buf, buf_size);
}

size_t HttpResponseBufferBody::Read(std::string_view* buf, size_t buf_size) {
  return this->IOBuffer::Read(buf, buf_size);
}

std::string HttpResponseBufferBody::ToString() {
  return buffer_.empty() ? "" : buffer_;
}
void HttpResponseBufferBody::SetPosition(int pos) {
  this->IOBuffer::SetPosition(pos);
}

log::LogStream& operator<<(log::LogStream& stream,
                           std::shared_ptr<HttpResponseBody> body) {
  stream << body->ToString();
}

}  // namespace net
}  // namespace tit