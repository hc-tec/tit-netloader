//
// Created by titto on 2022/5/28.
//

#include "http_request_info.h"

namespace tit {
namespace net {

HttpRequestInfo::HttpRequestInfo()
    : url(nullptr),
      method(nullptr),
      headers() {

}

HttpRequestInfo::HttpRequestInfo(const HttpRequestInfo& other) {
  url = other.url;
  method = other.method;
  headers = other.headers;
}

HttpRequestInfo::~HttpRequestInfo() {}
}  // namespace net
}  // namespace tit