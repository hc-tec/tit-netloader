//
// Created by titto on 2022/5/28.
//

#include "http_network_session.h"

#include "core/http/stream/http_basic_stream_factory.h"

namespace tit {
namespace net {

HttpNetworkSession::HttpNetworkSession()
    : http_stream_factory_(
          std::make_unique<HttpBasicStreamFactory>(this)) {

}


HttpNetworkSession::~HttpNetworkSession() {}
}  // namespace net
}  // namespace tit