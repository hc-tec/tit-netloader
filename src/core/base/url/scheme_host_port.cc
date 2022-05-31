//
// Created by titto on 2022/5/31.
//

#include "scheme_host_port.h"

namespace tit {
namespace net {

SchemeHostPort::SchemeHostPort(const std::string& scheme,
                               const std::string& host,
                               uint32 port)
    : scheme_(scheme),
      host_(host),
      port_(port) {}

SchemeHostPort::SchemeHostPort(URL& url)
    : SchemeHostPort(url.scheme(), url.host(), url.port()) {}

}  // namespace net
}  // namespace tit