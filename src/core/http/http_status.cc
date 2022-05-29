//
// Created by titto on 2022/5/29.
//

#include "http_status.h"

namespace tit {
namespace net {

const HttpStatus HttpStatus::CODE_100(100, "Continue");
const HttpStatus HttpStatus::CODE_101(101, "Switching");
const HttpStatus HttpStatus::CODE_102(102, "Processing");

const HttpStatus HttpStatus::CODE_200(200, "OK");
const HttpStatus HttpStatus::CODE_201(201, "Created");
const HttpStatus HttpStatus::CODE_202(202, "Accepted");
const HttpStatus HttpStatus::CODE_203(203, "Non-Authoritative Information");
const HttpStatus HttpStatus::CODE_204(204, "No Content");
const HttpStatus HttpStatus::CODE_205(205, "Reset Content");
const HttpStatus HttpStatus::CODE_206(206, "Partial Content");
const HttpStatus HttpStatus::CODE_207(207, "Multi-HttpStatus");
const HttpStatus HttpStatus::CODE_226(226, "IM Used");

const HttpStatus HttpStatus::CODE_300(300, "Multiple Choices");
const HttpStatus HttpStatus::CODE_301(301, "Moved Permanently");
const HttpStatus HttpStatus::CODE_302(302, "Moved Temporarily");
const HttpStatus HttpStatus::CODE_303(303, "See Other");
const HttpStatus HttpStatus::CODE_304(304, "Not Modified");
const HttpStatus HttpStatus::CODE_305(305, "Use Proxy");
const HttpStatus HttpStatus::CODE_306(306, "Reserved");
const HttpStatus HttpStatus::CODE_307(307, "Temporary Redirect");

const HttpStatus HttpStatus::CODE_400(400, "Bad Request");
const HttpStatus HttpStatus::CODE_401(401, "Unauthorized");
const HttpStatus HttpStatus::CODE_402(402, "Payment Required");
const HttpStatus HttpStatus::CODE_403(403, "Forbidden");
const HttpStatus HttpStatus::CODE_404(404, "Not Found");
const HttpStatus HttpStatus::CODE_405(405, "Method Not Allowed");
const HttpStatus HttpStatus::CODE_406(406, "Not Acceptable");
const HttpStatus HttpStatus::CODE_407(407, "Proxy Authentication Required");
const HttpStatus HttpStatus::CODE_408(408, "Request Timeout");
const HttpStatus HttpStatus::CODE_409(409, "Conflict");
const HttpStatus HttpStatus::CODE_410(410, "Gone");
const HttpStatus HttpStatus::CODE_411(411, "Length Required");
const HttpStatus HttpStatus::CODE_412(412, "Precondition Failed");
const HttpStatus HttpStatus::CODE_413(413, "Request Entity Too Large");
const HttpStatus HttpStatus::CODE_414(414, "Request-URI Too Large");
const HttpStatus HttpStatus::CODE_415(415, "Unsupported Media Type");
const HttpStatus HttpStatus::CODE_416(416, "Requested Range Not Satisfiable");
const HttpStatus HttpStatus::CODE_417(417, "Expectation Failed");
const HttpStatus HttpStatus::CODE_418(418, "I'm a Teapot");
const HttpStatus HttpStatus::CODE_422(422, "Unprocessable Entity");
const HttpStatus HttpStatus::CODE_423(423, "Locked");
const HttpStatus HttpStatus::CODE_424(424, "Failed Dependency");
const HttpStatus HttpStatus::CODE_425(425, "Unordered Collection");
const HttpStatus HttpStatus::CODE_426(426, "Upgrade Required");
const HttpStatus HttpStatus::CODE_428(428, "Precondition Required");
const HttpStatus HttpStatus::CODE_429(429, "Too Many Requests");
const HttpStatus HttpStatus::CODE_431(431, "Request Header Fields Too Large");
const HttpStatus HttpStatus::CODE_434(434, "Requested host unavailable");
const HttpStatus HttpStatus::CODE_444(444, "Close connection withot sending headers");
const HttpStatus HttpStatus::CODE_449(449, "Retry With");
const HttpStatus HttpStatus::CODE_451(451, "Unavailable For Legal Reasons");

const HttpStatus HttpStatus::CODE_500(500, "Internal Server Error");
const HttpStatus HttpStatus::CODE_501(501, "Not Implemented");
const HttpStatus HttpStatus::CODE_502(502, "Bad Gateway");
const HttpStatus HttpStatus::CODE_503(503, "Service Unavailable");
const HttpStatus HttpStatus::CODE_504(504, "Gateway Timeout");
const HttpStatus HttpStatus::CODE_505(505, "HTTP Version Not Supported");
const HttpStatus HttpStatus::CODE_506(506, "Variant Also Negotiates");
const HttpStatus HttpStatus::CODE_507(507, "Insufficient Storage");
const HttpStatus HttpStatus::CODE_508(508, "Loop Detected");
const HttpStatus HttpStatus::CODE_509(509, "Bandwidth Limit Exceeded");
const HttpStatus HttpStatus::CODE_510(510, "Not Extended");
const HttpStatus HttpStatus::CODE_511(511, "Network Authentication Required");

HttpStatus::HttpStatus(HttpStatus* pStatus) {
  code = pStatus->code;
  description = pStatus->description;
}

log::LogStream& operator<<(log::LogStream& stream, HttpStatus status) {
  stream << status.code << " " << status.description;
}

}  // namespace net
}  // namespace tit