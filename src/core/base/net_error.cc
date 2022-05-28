//
// Created by titto on 2022/5/28.
//

#include "net_error.h"

namespace tit {
namespace net {

std::string ErrorToString(int error) {
  return "net::" + ErrorToShortString(error);
}

std::string ErrorToShortString(int error) {
  if (error == OK)
    return "OK";

  const char* error_string;
  switch (error) {
#define NET_ERROR(label, value) \
  case ERR_ ## label: \
    error_string = # label; \
    break;
#include "core/base/net_error_list.h"
#undef NET_ERROR
    default:
      error_string = "<unknown>";
  }
  return std::string("ERR_") + error_string;
}

}  // namespace net
}  // namespace tit

