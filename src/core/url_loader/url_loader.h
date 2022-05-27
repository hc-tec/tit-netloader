//
// Created by titto on 2022/5/27.
//

#ifndef TIT_NETLOADER_URL_LOADER_H
#define TIT_NETLOADER_URL_LOADER_H

#include <memory>

namespace tit {
namespace net {

class URLRequest;

class URLLoader {
 public:

  class Delegate {

  };

 private:
  std::unique_ptr<URLRequest> url_request_;

};

}  // namespace net
}  // namespace tit



#endif //TIT_NETLOADER_URL_LOADER_H
