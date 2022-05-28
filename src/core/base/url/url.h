//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_H
#define TIT_NETLOADER_URL_H

#include <string>

namespace tit {
namespace net {

class URL {
 public:
  URL();

  URL(std::string url);

  const std::string& scheme() { return scheme_; }

  const std::string& path() { return "/"; }

 private:
  std::string scheme_;
  std::string origin_url_;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_URL_H
