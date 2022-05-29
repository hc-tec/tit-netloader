//
// Created by titto on 2022/5/29.
//

#include "io_buffer.h"

#include <cmath>
#include <cstring>

#include "log/logging.h"

namespace tit {
namespace net {

IOBuffer::IOBuffer()
    : pos_(0),
      buffer_() {}

size_t IOBuffer::GetSize() {
  return buffer_.size();
}

size_t IOBuffer::Buffer(char *buf, size_t buf_size) {
  buffer_.append(buf, buf_size);
  return buf_size;
}

void IOBuffer::Reset() {
  pos_ = 0;
}

void IOBuffer::SetPosition(int pos) {
  pos_ = pos;
}

size_t IOBuffer::Read(std::string_view *buf, size_t buf_size) {
  if (pos_ > GetSize()) {
    LOG(TRACE) << "buffer out of size";
    return -1;
  }
  int remain = GetSize() - pos_;
  remain = fmin(remain, buf_size);
  *buf = std::string_view(buffer_.data()+pos_, remain);
//  memcpy(buf, buffer_.data()+pos_, remain);
  Forward(remain);
  return remain;
}

size_t IOBuffer::ReadRemainAll(std::string_view *buf) {
  return Read(buf, GetSize() - pos_);
}

void IOBuffer::Forward(int offset) {
  pos_ += offset;
}

IOBuffer::~IOBuffer() {}

}  // namespace net
}  // namespace tit