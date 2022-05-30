//
// Created by titto on 2022/5/28.
//

#include "host_resolver.h"

#include <co/co/sock.h>

#include "core/base/url/url_scheme.h"

namespace tit {
namespace net {

HostResolver::HostResolver() {
}

SimpleHostResolver::SimpleHostResolver() : HostResolver() {}

void SimpleHostResolver::Start(const URL& url) {
  url_ = url;
  struct addrinfo* info = 0;
  int r = getaddrinfo(url_.host().data(),
                      reinterpret_cast<const char*>(url_.port()),
                      NULL, &info);
  if (r != 0) return;
  if (info->ai_family == AF_INET) {
    addr_ = std::make_shared<IPv4Address>(*info);
  } else if (info->ai_family == AF_INET6) {
    addr_ = std::make_shared<IPv6Address>(*info);
  }
}

Address::Ptr SimpleHostResolver::GetAddressResult() {
  uint32 port = URLScheme::Get()->GetPort(
      url_.scheme().data());
  addr_->set_port(port);
  return addr_;
}

std::unique_ptr<HostResolver> SimpleHostResolver::Create() {
  return std::make_unique<SimpleHostResolver>();
}

}  // namespace net
}  // namespace tit