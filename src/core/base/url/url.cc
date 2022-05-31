//
// Created by titto on 2022/5/28.
//

#include "url.h"

#include <utility>
#include <http_parser.h>

//#include "core/base/url/url_parser.h"
#include "log/logging.h"

namespace tit {
namespace net {


URL::URL()
    : URL("http://127.0.0.1:8000/") {}

URL::URL(std::string url)
    : origin_url_(std::move(url)),
      path_("/"),
      is_ip_(false) {
  http_parser_url u;
  http_parser_url_init(&u);
  int rv = http_parser_parse_url(origin_url_.data(), origin_url_.size(), 0, &u);
  if (rv != 0) {
    LOG(ERROR) << "URL parser error, url: " << origin_url_;
    return;
  }
  auto& data = u.field_data;
  scheme_ = origin_url_.substr(data[UF_SCHEMA].off, data[UF_SCHEMA].len);
  host_ = origin_url_.substr(data[UF_HOST].off, data[UF_HOST].len);
  port_ = atoi(origin_url_.substr(data[UF_PORT].off, data[UF_PORT].len).data());
  path_ = origin_url_.substr(data[UF_PATH].off, data[UF_PATH].len);
  if (host_.size() > 1 && host_.at(0) < 65) is_ip_ = true;
//  path_ = url.substr(data[UF_QUERY].off, data[UF_QUERY].len)

//  TParseUrl parser(origin_url_.data());
//  scheme_ = std::move(parser.v_param.protocol);
//  host_ = std::move(parser.v_param.host);
//  port_ = std::move(parser.v_param.port);
//  path_.append(std::move(parser.v_param.uri));
}

URL::URL(const URL& url) = default;

//URL& URL::operator=(const URL& other) = default;

log::LogStream& operator<<(log::LogStream& stream, URL url) {
  stream << url.origin_url();
}

}  // namespace net
}  // namespace tit