//
// Created by titto on 2022/5/31.
//

#ifndef TIT_NETLOADER_TRANSPORT_CLIENT_SOCKET_POOL_H
#define TIT_NETLOADER_TRANSPORT_CLIENT_SOCKET_POOL_H

#include <memory>
#include <vector>
#include <list>

#include "core/socket/client_socket_handle.h"
#include "core/socket/tcp/stream_socket.h"
#include "log/logging.h"

namespace tit {
namespace net {

inline int kDefaultMaxSockets = 256;
inline int kDefaultMaxSocketsPerGroup = 256;

class TransportClientSocketPool : public ClientSocketPool {
 public:
  TransportClientSocketPool(int max_sockets,
                            int max_sockets_per_group);
  ~TransportClientSocketPool();

  // ClientSocketPool
  int RequestSocket(const GroupId& group_id,
                    ClientSocketHandle* handle) override;
  int ReleaseSocket(const GroupId& group_id,
                    std::unique_ptr<StreamSocket> socket) override;
  void CloseIdleSockets(const GroupId& group_id) override;
  int IdleSocketCount() const override;
  size_t IdleSocketCountInGroup(const GroupId& group_id) const override;

 public:
  class Group {
   public:
    Group(const GroupId& group_id,
          TransportClientSocketPool* clientSocketPool);

    ~Group();

    bool IsEmpty() {
      return active_socket_count_ == 0 &&
             idle_sockets_.empty();
    }

    bool CanCreateNewSocket(int max_sockets_per_group) {
      return active_socket_count_ < max_sockets_per_group;
    }

    bool HasIdleSocket() {
        return !idle_sockets_.empty();
    }

    std::unique_ptr<StreamSocket> GetIdleSocket() {
      assert(HasIdleSocket());
      std::unique_ptr<StreamSocket> socket =
          std::move(idle_sockets_.back());
      idle_sockets_.pop_back();
      LOG(TRACE) << "Get idle socket: " << &socket << " from socket pool";
      LOG(TRACE) << "Current idle socket num: " << idle_sockets_.size();
      return socket;
    }

    void AddIdleSocket(std::unique_ptr<StreamSocket> socket) {
      LOG(TRACE) << "Add idle socket: " << &socket << " into socket pool";
      idle_sockets_.push_back(std::move(socket));
      LOG(TRACE) << "Current idle socket num: " << idle_sockets_.size();
    }

    void IncrementActiveSocketCount() { active_socket_count_++; }
    void DecrementActiveSocketCount() { active_socket_count_--; }

    const std::list<std::unique_ptr<StreamSocket>>&
    idle_sockets() const { return idle_sockets_; }

    int active_socket_count() const {
      return active_socket_count_;
    }

    std::list<std::unique_ptr<StreamSocket>>*
    mutable_idle_sockets() { return &idle_sockets_; }

   private:
    GroupId group_id_;
    TransportClientSocketPool* client_socket_pool_;

    int active_socket_count_;
    std::list<std::unique_ptr<StreamSocket>> idle_sockets_;
  };

 public:
  Group* GetOrCreateGroup(const GroupId& group_id);

 private:

  std::map<GroupId, std::unique_ptr<Group>> group_map_;

  // The total number of idle sockets in the system.
  int idle_socket_count_;

  // Number of connected sockets we handed out across all groups.
  int active_socket_count_;
  // The maximum total number of sockets. See ReachedMaxSocketsLimit.
  const int max_sockets_;

  // The maximum number of sockets kept per group.
  const int max_sockets_per_group_;

};

}  // namespace net
}  // namespace tit
#endif  // TIT_NETLOADER_TRANSPORT_CLIENT_SOCKET_POOL_H
