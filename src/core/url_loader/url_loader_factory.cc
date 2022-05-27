//
// Created by titto on 2022/5/28.
//

#include "url_loader_factory.h"

namespace tit {
namespace net {

std::unique_ptr<URLLoader> URLLoaderFactory::CreateURLLoader(
    uint64 request_id,
    const RequestParams &request_params,
    NetworkContext *network_context,
    URLLoader::Delegate *delegate) {
  return std::make_unique<URLLoader>(
      request_id,
      request_params,
      network_context,
      delegate
      );
}
}  // namespace net
}  // namespace tit