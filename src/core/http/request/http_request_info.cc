//
// Created by titto on 2022/5/28.
//

#include "http_request_info.h"

namespace tit {
namespace net {

std::string MethodToString(Method method) {
  std::string output;
  switch (method) {
    case GET: output = "GET"; break;
    case POST: output = "POST"; break;
    case PUT: output = "PUT"; break;
    case PATCH: output = "PATCH"; break;
    case DELETE: output = "DELETE"; break;
    case OPTION: output = "OPTION"; break;
    case HEAD: output = "HEAD"; break;
    default:
      output = "UNKNOWN_METHOD";
      break;
  }
  return output;
}

HttpRequestInfo::HttpRequestInfo()
    : url("/"),
      method("GET"),
      headers() {

}

HttpRequestInfo::HttpRequestInfo(const HttpRequestInfo& other) {
  url = other.url;
  method = other.method;
  headers = other.headers;
}

HttpRequestInfo::~HttpRequestInfo() {}

std::string HttpRequestInfo::GenerateRequestLine() {
  static const char kSuffix[] = " HTTP/1.1\r\n";
  const size_t kSuffixLen = std::size(kSuffix) - 1;
  std::string path = url.path();
  std::string request_line;
  const size_t expected_size =
      method.size() + 1 + path.size() + kSuffixLen;
  request_line.reserve(expected_size);
  request_line.append(method);
  request_line.append(1, ' ');
  request_line.append(path);
  request_line.append(kSuffix, kSuffixLen);
  return request_line;
}

}  // namespace net
}  // namespace tit