//
// Created by titto on 2022/5/29.
//

#ifndef TIT_NETLOADER_HTTP_RESPONSE_BODY_H
#define TIT_NETLOADER_HTTP_RESPONSE_BODY_H

#include <string>

#include <co/def.h>
#include <memory>

#include "core/base/io_buffer.h"
#include "log/log_stream.h"

namespace tit {
namespace net {

class HttpResponseBody {
 public:

  virtual ~HttpResponseBody() {};

  virtual size_t Read(std::string_view* buf, size_t buf_size) = 0;

  virtual size_t Buffer(char* buf, size_t buf_size) = 0;

  virtual size_t GetSize() = 0;

  // for testing
  virtual std::string ToString() = 0;
};

class HttpResponseBufferBody :
    public HttpResponseBody,
    public IOBuffer {
 public:

  HttpResponseBufferBody();
  ~HttpResponseBufferBody() override;
  size_t Read(std::string_view*, size_t buf_size) override;
  size_t Buffer(char*, size_t buf_size) override;
  size_t GetSize() override;
  std::string ToString() override;
};

log::LogStream& operator<<(log::LogStream& stream,
                           std::shared_ptr<HttpResponseBody> body);

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_RESPONSE_BODY_H
