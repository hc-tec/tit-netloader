//
// Created by titto on 2022/5/28.
//

#include "http_response_info.h"

namespace tit {
namespace net {

log::LogStream& operator<<(log::LogStream& stream, HttpResponseInfo response) {
  stream << "\n------Response------\n"
         << response.url << "\n"
         << response.status
         << "\n------HEADERS------\n" << response.headers;
  stream << "------BODY------\n" << response.body;
  stream << "\n";
}

}  // namespace net
}  // namespace tit