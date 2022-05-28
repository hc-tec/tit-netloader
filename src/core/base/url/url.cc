//
// Created by titto on 2022/5/28.
//

#include "url.h"

#include <utility>

namespace tit {
namespace net {


URL::URL()
    : origin_url_("/") {}

URL::URL(std::string url)
    : origin_url_(std::move(url)) {

}



//URL& URL::operator=(const URL& other) = default;

}  // namespace net
}  // namespace tit