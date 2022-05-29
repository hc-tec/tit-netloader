//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_RESPONSE_INFO_H
#define TIT_NETLOADER_HTTP_RESPONSE_INFO_H

#include "core/base/io_buffer.h"
#include "core/base/url/url.h"
#include "core/http/response/http_response_headers.h"
#include "core/http/response/http_response_body.h"
#include "core/socket/tcp/address.h"
#include "core/http/http_status.h"
#include "log/log_stream.h"

namespace tit {
namespace net {

struct HttpResponseInfo {

  HttpStatus status;

  URL url;

  Address::Ptr address;

  IOBuffer buffer;

  HttpResponseHeaders headers;

  std::shared_ptr<HttpResponseBody> body;

};

log::LogStream& operator<<(log::LogStream& stream, HttpResponseInfo response);

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_RESPONSE_INFO_H
