//
// Created by titto on 2022/5/29.
//

#include "http_headers.h"

#include "core/version.h"

namespace tit {
namespace net {

const char* const HttpHeaders::Value::CONNECTION_CLOSE = "close";
const char* const HttpHeaders::Value::CONNECTION_KEEP_ALIVE =
    "keep-alive";
const char* const HttpHeaders::Value::CONNECTION_UPGRADE = "Upgrade";

const char* const HttpHeaders::Value::SERVER =
    "tit-net-loader" TIT_NET_LOADER_VERSION;
const char* const HttpHeaders::Value::USER_AGENT =
    "tit-net-loader/" TIT_NET_LOADER_VERSION;

const char* const HttpHeaders::Value::TRANSFER_ENCODING_CHUNKED =
    "chunked";

const char* const HttpHeaders::Value::CONTENT_TYPE_APPLICATION_JSON =
    "application/json";

const char* const HttpHeaders::Value::EXPECT_100_CONTINUE =
    "100-continue";

const char* const HttpHeaders::ACCEPT = "Accept";
const char* const HttpHeaders::AUTHORIZATION = "Authorization";
const char* const HttpHeaders::WWW_AUTHENTICATE = "WWW-Authenticate";
const char* const HttpHeaders::CONNECTION = "Connection";
const char* const HttpHeaders::TRANSFER_ENCODING = "Transfer-Encoding";
const char* const HttpHeaders::CONTENT_ENCODING = "Content-Encoding";
const char* const HttpHeaders::CONTENT_LENGTH = "Content-Length";
const char* const HttpHeaders::CONTENT_TYPE = "Content-Type";
const char* const HttpHeaders::CONTENT_RANGE = "Content-Range";
const char* const HttpHeaders::RANGE = "Range";
const char* const HttpHeaders::HOST = "Host";
const char* const HttpHeaders::USER_AGENT = "User-Agent";
const char* const HttpHeaders::SERVER = "Server";
const char* const HttpHeaders::UPGRADE = "Upgrade";


const char* const HttpHeaders::CORS_ORIGIN =
    "Access-Control-Allow-Origin";
const char* const HttpHeaders::CORS_METHODS =
    "Access-Control-Allow-Methods";
const char* const HttpHeaders::CORS_HEADERS =
    "Access-Control-Allow-HttpHeaderss";
const char* const HttpHeaders::CORS_MAX_AGE =
    "Access-Control-Max-Age";

const char* const HttpHeaders::ACCEPT_ENCODING = "Accept-Encoding";

const char* const HttpHeaders::EXPECT = "Expect";

void HttpHeaders::PutHeaders(const std::string& name,
                                    const std::string& value) {
  headers_.insert({ name, value });
}

std::string HttpHeaders::GetHeader(const std::string& name) {
  auto it = headers_.find(name);
  if (it == headers_.end()) {
    return "";
  }
  return it->second;
}

std::string HttpHeaders::ToString() {
  std::string output;
  for (auto& [key, value] : headers_) {
    output
        .append(key.c_str())
        .append(": ")
        .append(value.c_str())
        .append("\r\n");
  }
  output.append("\r\n");
  return output;
}

log::LogStream& operator<<(log::LogStream& stream, HttpHeaders headers) {
  stream << headers.ToString();
}


}  // namespace net
}  // namespace tit