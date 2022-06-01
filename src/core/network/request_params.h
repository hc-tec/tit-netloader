//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_REQUEST_PARAMS_H
#define TIT_NETLOADER_REQUEST_PARAMS_H

#include "core/base/request_priority.h"
#include "core/base/url/url_scheme.h"
#include "core/http/request/http_request_info.h"

namespace tit {
namespace net {

struct RequestParams {
  bool enable_spdy;
  bool enable_http2;
  bool enable_quic;
  std::string scheme;
  ProtocolType protocol_type { ProtocolType::HTTP1_0 };
  RequestPriority priority;
  HttpRequestInfo request_info;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_REQUEST_PARAMS_H
