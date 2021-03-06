//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_REQUEST_INFO_H
#define TIT_NETLOADER_HTTP_REQUEST_INFO_H

#include <memory>
#include <string>

#include "core/base/url/url.h"
#include "core/base/url/url_scheme.h"
#include "core/socket/tcp/address.h"
#include "http_request_body.h"
#include "http_request_headers.h"
#include "log/log_stream.h"

namespace tit {
namespace net {

enum Method {
  GET,
  POST,
  PUT,
  PATCH,
  DELETE,
  OPTION,
  HEAD
};

std::string MethodToString(Method method);

struct HttpRequestInfo {
  HttpRequestInfo();
  HttpRequestInfo(const HttpRequestInfo& other);
  ~HttpRequestInfo();

  std::string GenerateRequestLine(ProtocolType protocol_type);

  void SetAddressByUrl();

  URL url;

  Address::Ptr address;

  Method method;

  HttpRequestHeaders headers;

  std::shared_ptr<HttpRequestBody> body;

};

log::LogStream& operator<<(log::LogStream& stream, HttpRequestInfo* request);

log::LogStream& operator<<(log::LogStream& stream, HttpRequestInfo request);

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_REQUEST_INFO_H
