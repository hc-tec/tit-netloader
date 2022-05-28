//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NET_ERROR_H
#define TIT_NETLOADER_NET_ERROR_H

#include <string>

namespace tit {
namespace net {

// Error values are negative.
enum Error {
  // No error. Change NetError.template after changing value.
  OK = 0,

#define NET_ERROR(label, value) ERR_ ## label = value,
#include "core/base/net_error_list.h"
#undef NET_ERROR

  // The value of the first certificate error code.
  ERR_CERT_BEGIN = ERR_CERT_COMMON_NAME_INVALID,
};

// Returns a textual representation of the error code for logging purposes.
std::string ErrorToString(int error);

// Same as above, but leaves off the leading "net::".
std::string ErrorToShortString(int error);

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_NET_ERROR_H
