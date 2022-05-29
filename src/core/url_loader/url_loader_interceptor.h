//
// Created by titto on 2022/5/29.
//

#ifndef TIT_NETLOADER_URL_LOADER_INTERCEPTOR_H
#define TIT_NETLOADER_URL_LOADER_INTERCEPTOR_H

namespace tit {
namespace net {

class NetworkService;
struct RequestParams;

class URLLoaderInterceptor {
 public:
  virtual ~URLLoaderInterceptor() = default;

  virtual bool Interceptor(NetworkService* service,
                           RequestParams* params) = 0;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_URL_LOADER_INTERCEPTOR_H
