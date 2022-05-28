//
// Created by titto on 2022/5/28.
//

#include "http_stream_factory.h"

namespace tit {
namespace net {

HttpStreamFactory::HttpStreamFactory(HttpNetworkSession *session)
    : session_(session) {}

HttpStreamFactory::~HttpStreamFactory() {}

}  // namespace net
}  // namespace tit