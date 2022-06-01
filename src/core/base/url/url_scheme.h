//
// Created by titto on 2022/5/30.
//

#ifndef TIT_NETLOADER_URL_SCHEME_H
#define TIT_NETLOADER_URL_SCHEME_H

#include <map>
#include <string>

#include "core/base/url/url_constants.h"

namespace tit {
namespace net {

enum ProtocolType {
  HTTP1_0,
  HTTP1_1,
  HTTP2,
  WEBSOCKER,
  QUIC,
  OTHER
};

std::string ProtocolToString(ProtocolType type);

class URLScheme {
 public:

  URLScheme();

  void RegisterSchemeWithPort(const char* scheme, uint32 port);

  uint32 GetPort(const char* scheme);

  static URLScheme* Get();

 private:
  std::map<std::string, uint32> scheme_port_map_;

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_SCHEME_H
