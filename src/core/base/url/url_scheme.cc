//
// Created by titto on 2022/5/30.
//

#include "url_scheme.h"

#include "log/logging.h"

namespace tit {
namespace net {

std::string ProtocolToString(ProtocolType type) {
  switch (type) {
    case ProtocolType::HTTP1_0: return "HTTP/1.0";
    case ProtocolType::HTTP1_1: return "HTTP/1.1";
    case ProtocolType::HTTP2: return "HTTP/2.0";
    default:
      return "HTTP/1.0";
  }
}

void URLScheme::RegisterSchemeWithPort(const char *scheme, uint32 port) {
  scheme_port_map_[scheme] = port;
}

uint32 URLScheme::GetPort(const char *scheme) {
  auto it = scheme_port_map_.find(scheme);
  if (it == scheme_port_map_.end()) {
    LOG(ERROR) << "Scheme: " << scheme
               << " not register port in URLScheme";
  }
  return it->second;
}

URLScheme* URLScheme::Get() {
  static URLScheme url_scheme;
  return &url_scheme;
}

URLScheme::URLScheme() {
  RegisterSchemeWithPort(kHttpScheme, 80);
  RegisterSchemeWithPort(kHttpsScheme, 443);
}

}  // namespace net
}  // namespace tit