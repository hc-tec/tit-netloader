//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_REQUEST_PARAMS_H
#define TIT_NETLOADER_REQUEST_PARAMS_H

#include "core/base/request_priority.h"
#include "core/http/request/http_request_info.h"

namespace tit {
namespace net {

enum ProtocolType {
  HTTP,
  HTTP2,
  WEBSOCKER,
  QUIC,
  OTHER
};

struct RequestParams {
  bool enable_spdy;
  bool enable_http2;
  bool enable_quic;
  std::string scheme;
  ProtocolType protocol_type;
  RequestPriority priority;
  HttpRequestInfo request_info;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_REQUEST_PARAMS_H
