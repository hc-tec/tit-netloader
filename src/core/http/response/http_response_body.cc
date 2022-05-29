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

}  // namespace net
}  // namespace tit