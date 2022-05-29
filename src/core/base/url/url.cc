//
// Created by titto on 2022/5/28.
//

#include "url.h"

#include <utility>

#include "core/base/url/url_parser.h"

namespace tit {
namespace net {


URL::URL()
    : URL("http://127.0.0.1:8000/") {}

URL::URL(std::string url)
    : origin_url_(std::move(url)),
      path_("/") {
  TParseUrl parser(origin_url_.data());
  scheme_ = std::move(parser.v_param.protocol);
  host_ = std::move(parser.v_param.host);
  port_ = std::move(parser.v_param.port);
  path_.append(std::move(parser.v_param.uri));
}

//URL& URL::operator=(const URL& other) = default;

}  // namespace net
}  // namespace tit