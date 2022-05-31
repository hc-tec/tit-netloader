//
// Created by titto on 2022/5/31.
//

#ifndef TIT_NETLOADER_CLIENT_SOCKET_POOL_H
#define TIT_NETLOADER_CLIENT_SOCKET_POOL_H

#include "core/base/url/scheme_host_port.h"

#include <map>
#include <memory>

#include "base/noncopyable.h"

namespace tit {
namespace net {

class ClientSocketHandle;
class StreamSocket;

class ClientSocketPool {
 public:
  ClientSocketPool() = default;
  virtual ~ClientSocketPool() = default;

  class GroupId {
   public:
    explicit GroupId(const SchemeHostPort& scheme_host_port);

    GroupId(const GroupId&) = default;
    GroupId& operator=(const GroupId&) = default;

    bool operator==(const GroupId& other);

    bool operator<(const GroupId& other) const;

    void set_scheme_host_port(SchemeHostPort scheme_host_port) {
      scheme_host_port_ = scheme_host_port;
    }

    std::string ToString() const {
      return scheme_host_port_.ToString();
    }

   private:
    SchemeHostPort scheme_host_port_;
  };

  virtual int RequestSocket(
      const GroupId& group_id,
      ClientSocketHandle* handle) = 0;

  virtual int ReleaseSocket(const GroupId& group_id,
                            std::unique_ptr<StreamSocket> socket) = 0;

  virtual void CloseIdleSockets(const GroupId& group_id) = 0;

  virtual int IdleSocketCount() const = 0;

  virtual size_t IdleSocketCountInGroup(const GroupId& group_id) const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(ClientSocketPool);

};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_CLIENT_SOCKET_POOL_H
