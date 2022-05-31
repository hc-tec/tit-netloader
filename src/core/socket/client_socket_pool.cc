//
// Created by titto on 2022/5/31.
//

#include "client_socket_pool.h"

namespace tit {
namespace net {

bool ClientSocketPool::GroupId::operator==(
    const ClientSocketPool::GroupId& other) {
  return std::tie(scheme_host_port_) ==
         std::tie(other.scheme_host_port_);
}

ClientSocketPool::GroupId::GroupId(const SchemeHostPort& scheme_host_port)
    : scheme_host_port_(scheme_host_port) {}

bool ClientSocketPool::GroupId::operator<(
    const ClientSocketPool::GroupId& other) const {
  return std::tie(scheme_host_port_) <
         std::tie(other.scheme_host_port_);
}

}  // namespace net
}  // namespace tit