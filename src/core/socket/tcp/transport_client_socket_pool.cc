//
// Created by titto on 2022/5/31.
//

#include "transport_client_socket_pool.h"

#include "core/base/net_error.h"
#include "core/socket/tcp/transport_client_socket.h"
#include "log/logging.h"

namespace tit {
namespace net {

TransportClientSocketPool::TransportClientSocketPool(
    int max_sockets, int max_sockets_per_group)
    : idle_socket_count_(0),
      active_socket_count_(0),
      max_sockets_(max_sockets),
      max_sockets_per_group_(max_sockets_per_group) {}

TransportClientSocketPool::~TransportClientSocketPool() {
    for (auto& [group_id, group] : group_map_) {
      CloseIdleSockets(group_id);
    }
}

TransportClientSocketPool::Group::Group(
    const ClientSocketPool::GroupId &group_id,
    TransportClientSocketPool *clientSocketPool)
    : group_id_(group_id),
      client_socket_pool_(clientSocketPool),
      active_socket_count_(0) {}

TransportClientSocketPool::Group::~Group() = default;

int TransportClientSocketPool::RequestSocket(
    const ClientSocketPool::GroupId &group_id,
    ClientSocketHandle *handle) {
  Group* group = GetOrCreateGroup(group_id);
  if (group->HasIdleSocket()) {
    std::unique_ptr<StreamSocket> idle_socket = group->GetIdleSocket();
    handle->set_socket(std::move(idle_socket));
    group->IncrementActiveSocketCount();
  } else {
    if (group->CanCreateNewSocket(max_sockets_per_group_)) {
      std::unique_ptr<StreamSocket> socket = CreateSocket();
      LOG(TRACE) << "Create socket: " << &socket;
      handle->set_socket(std::move(socket));
      group->IncrementActiveSocketCount();
    } else {
      return ERR_PRECONNECT_MAX_SOCKET_LIMIT;
    }
  }
  return OK;
}

int TransportClientSocketPool::ReleaseSocket(
    const ClientSocketPool::GroupId &group_id,
    std::unique_ptr<StreamSocket> socket) {
  Group* group = GetOrCreateGroup(group_id);
  if (socket->IsConnected()) {
    group->AddIdleSocket(std::move(socket));
    group->DecrementActiveSocketCount();
  } else {
    socket.reset();
    group->DecrementActiveSocketCount();
  }
  return 0;
}

void TransportClientSocketPool::CloseIdleSockets(
    const ClientSocketPool::GroupId &group_id) {}

int TransportClientSocketPool::IdleSocketCount() const { return idle_socket_count_; }

size_t TransportClientSocketPool::IdleSocketCountInGroup(
    const ClientSocketPool::GroupId &group_id) const {
  auto it = group_map_.find(group_id);
  if (it == group_map_.end()) {
    return -1;
  }
  return it->second->idle_sockets().size();
}

TransportClientSocketPool::Group *TransportClientSocketPool::GetOrCreateGroup(
    const ClientSocketPool::GroupId &group_id) {
  auto it = group_map_.find(group_id);
  if (it == group_map_.end()) {
    bool ok;
    std::unique_ptr<Group> group = std::make_unique<Group>(
        group_id, this);
    std::tie(it, ok) = group_map_.insert({ group_id, std::move(group) });
    if (!ok) {
      LOG(ERROR) << "GroupMap insert error, group_id: " << group_id.ToString();
      return nullptr;
    }
  }
  return it->second.get();
}

std::unique_ptr<StreamSocket> TransportClientSocketPool::CreateSocket() {
  return std::make_unique<TransportClientSocket>();
}

}  // namespace net
}  // namespace tit