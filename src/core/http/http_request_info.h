//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_REQUEST_INFO_H
#define TIT_NETLOADER_HTTP_REQUEST_INFO_H

#include <memory>
#include <string>

#include "core/base/url/url.h"
#include "core/http/http_request_headers.h"
#include "core/http/http_request_body.h"

namespace tit {
namespace net {

struct HttpRequestInfo {
  HttpRequestInfo();
  HttpRequestInfo(const HttpRequestInfo& other);
  ~HttpRequestInfo();

  URL url;

  std::string method;

  HttpRequestHeaders headers;

  std::shared_ptr<HttpRequestBody> body;

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_REQUEST_INFO_H
