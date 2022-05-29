//
// Created by titto on 2022/5/29.
//

#ifndef TIT_NETLOADER_HTTP_STATUS_H
#define TIT_NETLOADER_HTTP_STATUS_H

#include <map>

#include <co/def.h>

#include "log/log_stream.h"

namespace tit {
namespace net {



/**
 * Http Status.
 */
class HttpStatus {
 public:
  HttpStatus(HttpStatus* pStatus);
  static inline std::map<int32, HttpStatus> HttpStatusMap;
  /**
   * Continue.
   */
  static const HttpStatus CODE_100;// Continue

  /**
   * Switching Protocols.
   */
  static const HttpStatus CODE_101;// Switching

  /**
   * Processing.
   */
  static const HttpStatus CODE_102;// Processing

  /**
   * OK.
   */
  static const HttpStatus CODE_200;// OK

  /**
   * Created.
   */
  static const HttpStatus CODE_201;// Created

  /**
   * Accepted.
   */
  static const HttpStatus CODE_202;// Accepted

  /**
   * Non-Authoritative Information.
   */
  static const HttpStatus CODE_203;// Non-Authoritative Information

  /**
   * No Content.
   */
  static const HttpStatus CODE_204;// No Content

  /**
   * Reset Content.
   */
  static const HttpStatus CODE_205;// Reset Content

  /**
   * Partial Content.
   */
  static const HttpStatus CODE_206;// Partial Content

  /**
   * Multi-HttpStatus.
   */
  static const HttpStatus CODE_207;// Multi-HttpStatus

  /**
   * IM Used.
   */
  static const HttpStatus CODE_226;// IM Used

  /**
   * Multiple Choices.
   */
  static const HttpStatus CODE_300;// Multiple Choices

  /**
   * Moved Permanently.
   */
  static const HttpStatus CODE_301;// Moved Permanently

  /**
   * Moved Temporarily.
   */
  static const HttpStatus CODE_302;// Moved Temporarily

  /**
   * See Other.
   */
  static const HttpStatus CODE_303;// See Other

  /**
   * Not Modified.
   */
  static const HttpStatus CODE_304;// Not Modified

  /**
   * Use Proxy.
   */
  static const HttpStatus CODE_305;// Use Proxy

  /**
   * Reserved.
   */
  static const HttpStatus CODE_306;// Reserved

  /**
   * Temporary Redirect.
   */
  static const HttpStatus CODE_307;// Temporary Redirect

  /**
   * Bad Request.
   */
  static const HttpStatus CODE_400;// Bad Request

  /**
   * Unauthorized.
   */
  static const HttpStatus CODE_401;// Unauthorized

  /**
   * Payment Required.
   */
  static const HttpStatus CODE_402;// Payment Required

  /**
   * Forbidden.
   */
  static const HttpStatus CODE_403;// Forbidden

  /**
   * Not Found.
   */
  static const HttpStatus CODE_404;// Not Found

  /**
   * Method Not Allowed.
   */
  static const HttpStatus CODE_405;// Method Not Allowed

  /**
   * Not Acceptable.
   */
  static const HttpStatus CODE_406;// Not Acceptable

  /**
   * Proxy Authentication Required.
   */
  static const HttpStatus CODE_407;// Proxy Authentication Required

  /**
   * Request Timeout.
   */
  static const HttpStatus CODE_408;// Request Timeout

  /**
   * Conflict.
   */
  static const HttpStatus CODE_409;// Conflict

  /**
   * Gone
   */
  static const HttpStatus CODE_410;// Gone

  /**
   * Length Required.
   */
  static const HttpStatus CODE_411;// Length Required

  /**
   * Precondition Failed.
   */
  static const HttpStatus CODE_412;// Precondition Failed

  /**
   * Request Entity Too Large.
   */
  static const HttpStatus CODE_413;// Request Entity Too Large

  /**
   * Request-URI Too Large.
   */
  static const HttpStatus CODE_414;// Request-URI Too Large

  /**
   * Unsupported Media Type.
   */
  static const HttpStatus CODE_415;// Unsupported Media Type

  /**
   * Requested Range Not Satisfiable.
   */
  static const HttpStatus CODE_416;// Requested Range Not Satisfiable

  /**
   * Expectation Failed.
   */
  static const HttpStatus CODE_417;// Expectation Failed

  /**
   * I'm a Teapot (rfc7168 2.3.3)
   */
  static const HttpStatus CODE_418;// I'm a teapot

  /**
   * Unprocessable Entity.
   */
  static const HttpStatus CODE_422;// Unprocessable Entity

  /**
   * Locked.
   */
  static const HttpStatus CODE_423;// Locked

  /**
   * Failed Dependency.
   */
  static const HttpStatus CODE_424;// Failed Dependency

  /**
   * Unordered Collection.
   */
  static const HttpStatus CODE_425;// Unordered Collection

  /**
   * Upgrade Required.
   */
  static const HttpStatus CODE_426;// Upgrade Required

  /**
   * Precondition Required.
   */
  static const HttpStatus CODE_428;// Precondition Required

  /**
   * Too Many Requests.
   */
  static const HttpStatus CODE_429;// Too Many Requests

  /**
   * Request Header Fields Too Large.
   */
  static const HttpStatus CODE_431;// Request Header Fields Too Large

  /**
   * Requested host unavailable.
   */
  static const HttpStatus CODE_434;// Requested host unavailable

  /**
   * Close connection withot sending headers.
   */
  static const HttpStatus CODE_444;// Close connection withot sending headers

  /**
   * Retry With.
   */
  static const HttpStatus CODE_449;// Retry With

  /**
   * Unavailable For Legal Reasons.
   */
  static const HttpStatus CODE_451;// Unavailable For Legal Reasons

  /**
   * Internal Server Error.
   */
  static const HttpStatus CODE_500;// Internal Server Error

  /**
   * Not Implemented.
   */
  static const HttpStatus CODE_501;// Not Implemented

  /**
   * Bad Gateway.
   */
  static const HttpStatus CODE_502;// Bad Gateway

  /**
   * Service Unavailable.
   */
  static const HttpStatus CODE_503;// Service Unavailable

  /**
   * Gateway Timeout.
   */
  static const HttpStatus CODE_504;// Gateway Timeout

  /**
   * HTTP Version Not Supported.
   */
  static const HttpStatus CODE_505;// HTTP Version Not Supported

  /**
   * Variant Also Negotiates.
   */
  static const HttpStatus CODE_506;// Variant Also Negotiates

  /**
   * Insufficient Storage.
   */
  static const HttpStatus CODE_507;// Insufficient Storage

  /**
   * Loop Detected.
   */
  static const HttpStatus CODE_508;// Loop Detected

  /**
   * Bandwidth Limit Exceeded.
   */
  static const HttpStatus CODE_509;// Bandwidth Limit Exceeded

  /**
   * Not Extended.
   */
  static const HttpStatus CODE_510;// Not Extended

  /**
   * Network Authentication Required.
   */
  static const HttpStatus CODE_511;// Network Authentication Required

  /**
   * Constructor.
   */
  HttpStatus()
      : code(0)
      , description(nullptr)
  {}

  /**
   * Constructor.
   * @param pCode - HttpStatus code.
   * @param pDesc - description.
   */
  HttpStatus(int32 pCode, const char* pDesc)
      : code(pCode)
      , description(pDesc) {
    HttpStatusMap.emplace(pCode, this);
  }

  /**
   * HttpStatus code.
   */
  int32 code;

  /**
   * Description.
   */
  const char* description;

  bool operator==(const HttpStatus& other) const {
    return this->code == other.code;
  }

  bool operator!=(const HttpStatus& other) const {
    return this->code != other.code;
  }

};

log::LogStream& operator<<(log::LogStream& stream, HttpStatus status);

}  // namespace net
}  // namespace tit
#endif  // TIT_NETLOADER_HTTP_STATUS_H
