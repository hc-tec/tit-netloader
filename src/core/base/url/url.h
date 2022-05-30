//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_H
#define TIT_NETLOADER_URL_H

#include <string>

#include <co/def.h>
#include "log/log_stream.h"

namespace tit {
namespace net {

class URL {
 public:

  URL();

  URL(std::string url);

  const std::string& origin_url() { return origin_url_; }

  const std::string& scheme() { return scheme_; }

  const std::string& host() { return host_; }

  uint32 port() const { return port_; }

  const std::string& path() { return path_; }

  bool is_ip() const { return is_ip_; }

 private:
  std::string origin_url_;
  std::string scheme_;
  std::string host_;
  uint32 port_;
  std::string path_;

  bool is_ip_;
};

log::LogStream& operator<<(log::LogStream& stream, URL url);

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_URL_H
