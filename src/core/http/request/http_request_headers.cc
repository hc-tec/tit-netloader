//
// Created by titto on 2022/5/28.
//

#include "http_request_headers.h"

#include "core/version.h"

namespace tit {
namespace net {


const char* const HttpRequestHeaders::Value::CONNECTION_CLOSE = "close";
const char* const HttpRequestHeaders::Value::CONNECTION_KEEP_ALIVE =
    "keep-alive";
const char* const HttpRequestHeaders::Value::CONNECTION_UPGRADE = "Upgrade";

const char* const HttpRequestHeaders::Value::SERVER =
    "tit-net-loader" TIT_NET_LOADER_VERSION;
const char* const HttpRequestHeaders::Value::USER_AGENT =
    "tit-net-loader/" TIT_NET_LOADER_VERSION;

const char* const HttpRequestHeaders::Value::TRANSFER_ENCODING_CHUNKED =
    "chunked";

const char* const HttpRequestHeaders::Value::CONTENT_TYPE_APPLICATION_JSON =
    "application/json";

const char* const HttpRequestHeaders::Value::EXPECT_100_CONTINUE =
    "100-continue";

const char* const HttpRequestHeaders::ACCEPT = "Accept";
const char* const HttpRequestHeaders::AUTHORIZATION = "Authorization";
const char* const HttpRequestHeaders::WWW_AUTHENTICATE = "WWW-Authenticate";
const char* const HttpRequestHeaders::CONNECTION = "Connection";
const char* const HttpRequestHeaders::TRANSFER_ENCODING = "Transfer-Encoding";
const char* const HttpRequestHeaders::CONTENT_ENCODING = "Content-Encoding";
const char* const HttpRequestHeaders::CONTENT_LENGTH = "Content-Length";
const char* const HttpRequestHeaders::CONTENT_TYPE = "Content-Type";
const char* const HttpRequestHeaders::CONTENT_RANGE = "Content-Range";
const char* const HttpRequestHeaders::RANGE = "Range";
const char* const HttpRequestHeaders::HOST = "Host";
const char* const HttpRequestHeaders::USER_AGENT = "User-Agent";
const char* const HttpRequestHeaders::SERVER = "Server";
const char* const HttpRequestHeaders::UPGRADE = "Upgrade";


const char* const HttpRequestHeaders::CORS_ORIGIN =
    "Access-Control-Allow-Origin";
const char* const HttpRequestHeaders::CORS_METHODS =
    "Access-Control-Allow-Methods";
const char* const HttpRequestHeaders::CORS_HEADERS =
    "Access-Control-Allow-HttpRequestHeaderss";
const char* const HttpRequestHeaders::CORS_MAX_AGE =
    "Access-Control-Max-Age";

const char* const HttpRequestHeaders::ACCEPT_ENCODING = "Accept-Encoding";

const char* const HttpRequestHeaders::EXPECT = "Expect";

void HttpRequestHeaders::PutHeaders(const std::string& name,
                                    const std::string& value) {
  headers_.insert({ name, value });
}

std::string HttpRequestHeaders::GetHeader(const std::string& name) {
  return headers_[name];
}

std::string HttpRequestHeaders::ToString() {
  std::string output;
  for (auto& [key, value] : headers_) {
    output.append(key.c_str()).append(value.c_str()).append("\r\n");
  }
  output.append("\r\n");
  return output;
}

}  // namespace net
}  // namespace tit