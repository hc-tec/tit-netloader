//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_LOADER_FACTORY_H
#define TIT_NETLOADER_URL_LOADER_FACTORY_H

#include <memory>

#include <co/def.h>

#include "core/url_loader/url_loader.h"

namespace tit {
namespace net {

struct RequestParams;

class NetworkContext;

class URLLoaderFactory {
 public:
  std::unique_ptr<URLLoader> CreateURLLoader(
      uint64 request_id,
      const RequestParams& request_params,
      NetworkContext* network_context,
      URLLoader::Delegate* delegate);

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_LOADER_FACTORY_H
