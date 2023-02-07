//
// Created by titto on 2022/5/29.
//

#ifndef TIT_NETLOADER_IOBUFFER_H
#define TIT_NETLOADER_IOBUFFER_H

#include <string>

#include <co/def.h>

namespace tit {
namespace net {

class IOBuffer {
 public:

  IOBuffer();

  virtual ~IOBuffer();

  virtual void Reset();

  virtual void SetPosition(int pos);

  virtual void Forward(int offset);

  virtual size_t ReadRemainAll(std::string_view* buf);

  virtual size_t Read(std::string_view* buf, size_t buf_size);
  virtual size_t Buffer(char* buf, size_t buf_size);
  virtual size_t GetPosition();
  virtual size_t GetSize();

 protected:
  size_t pos_;
  std::string buffer_;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_IOBUFFER_H
