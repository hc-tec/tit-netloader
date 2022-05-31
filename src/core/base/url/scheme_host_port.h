//
// Created by titto on 2022/5/31.
//

#ifndef TIT_NETLOADER_SCHEME_HOST_PORT_H
#define TIT_NETLOADER_SCHEME_HOST_PORT_H

#include <string>
#include <tuple>

#include <co/def.h>

#include "core/base/url/url.h"

namespace tit {
namespace net {

class SchemeHostPort {
 public:
  SchemeHostPort(URL& url);

  SchemeHostPort(const std::string& scheme,
                 const std::string& host,
                 uint32 port);

  const std::string& scheme() { return scheme_; }

  const std::string& host() { return host_; }

  uint32 port() const { return port_; }

  std::string ToString() const {
    return std::string().append(scheme_)
        .append("://")
        .append(host_)
        .append(std::to_string(port_));
  }

  bool operator==(const SchemeHostPort& other) {
    return std::tie(scheme_, host_, port_) ==
           std::tie(other.scheme_, other.host_, other.port_);
  }
 private:
  std::string scheme_;
  std::string host_;
  uint32 port_;
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_SCHEME_HOST_PORT_H
