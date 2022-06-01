//
// Created by titto on 2022/5/28.
//

#include "http_request_info.h"

#include "core/socket/tcp/address.h"
#include "core/http/request/http_request_body.h"

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
      method(GET),
      headers() {

}

HttpRequestInfo::HttpRequestInfo(const HttpRequestInfo& other) {
  url = other.url;
  method = other.method;
  headers = other.headers;
  address = other.address;
  body = other.body;
}

HttpRequestInfo::~HttpRequestInfo() {}

std::string HttpRequestInfo::GenerateRequestLine(ProtocolType protocol_type) {
  std::string suffix(" ");
  suffix.append(ProtocolToString(protocol_type))
      .append("\r\n");
  const size_t kSuffixLen = suffix.size() - 1;
  std::string path = url.path();
  std::string request_line;
  std::string method_str = MethodToString(method);
  const size_t expected_size =
      method_str.size() + 1 + path.size() + kSuffixLen;
  request_line.reserve(expected_size);
  request_line.append(method_str);
  request_line.append(1, ' ');
  request_line.append(path);
  request_line.append(suffix);
  return request_line;
}

void HttpRequestInfo::SetAddressByUrl() {
  address = IPv4Address::Create(url.host().data(), url.port());
}

log::LogStream& operator<<(log::LogStream& stream, HttpRequestInfo* request) {
    return stream << *request;
}

log::LogStream& operator<<(log::LogStream& stream, HttpRequestInfo request) {
  stream << "\n------Request------\n"
         << MethodToString(request.method) << " "
         << request.url
         << "\n------HEADERS------\n" << request.headers;
  stream << "------BODY------\n";
  if (request.body) stream << request.body;
  stream << "\n";
}

}  // namespace net
}  // namespace tit