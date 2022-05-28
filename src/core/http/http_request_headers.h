//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_REQUEST_HEADERS_H
#define TIT_NETLOADER_HTTP_REQUEST_HEADERS_H

#include <map>
#include <string>

namespace tit {
namespace net {

class HttpRequestHeaders {
 public:

  void PutHeaders(const std::string& name, const std::string& value);

  std::string GetHeader(const std::string& name);

  /**
   * Possible values for headers.
   */
  class Value {
   public:
    static const char* const CONNECTION_CLOSE;
    static const char* const CONNECTION_KEEP_ALIVE;
    static const char* const CONNECTION_UPGRADE;

    static const char* const SERVER;
    static const char* const USER_AGENT;

    static const char* const TRANSFER_ENCODING_CHUNKED;
    static const char* const CONTENT_TYPE_APPLICATION_JSON;

    static const char* const EXPECT_100_CONTINUE;
  };
 public:
  static const char* const ACCEPT;              // "Accept"
  static const char* const AUTHORIZATION;       // "Authorization"
  static const char* const WWW_AUTHENTICATE;    // "WWW-Authenticate"
  static const char* const CONNECTION;          // "Connection"
  static const char* const TRANSFER_ENCODING;   // "Transfer-Encoding"
  static const char* const CONTENT_ENCODING;    // "Content-Encoding"
  static const char* const CONTENT_LENGTH;      // "Content-Length"
  static const char* const CONTENT_TYPE;        // "Content-Type"
  static const char* const CONTENT_RANGE;       // "Content-Range"
  static const char* const RANGE;               // "Range"
  static const char* const HOST;                // "Host"
  static const char* const USER_AGENT;          // "User-Agent"
  static const char* const SERVER;              // "Server"
  static const char* const UPGRADE;             // "Upgrade"
  static const char* const CORS_ORIGIN;         // Access-Control-Allow-Origin
  static const char* const CORS_METHODS;        // Access-Control-Allow-Methods
  static const char* const CORS_HEADERS;        // Access-Control-Allow-Headers
  static const char* const CORS_MAX_AGE;        // Access-Control-Max-Age
  static const char* const ACCEPT_ENCODING;     // Accept-Encoding
  static const char* const EXPECT;              // Expect

 private:
  std::map<std::string, std::string> headers_;

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_REQUEST_HEADERS_H
