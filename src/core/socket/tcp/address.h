//
// Created by titto on 2022/4/21.
//

#ifndef TIT_COROUTINE_ADDRESS_H
#define TIT_COROUTINE_ADDRESS_H

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>  // basic socket api, struct linger
#include <netinet/in.h>  // for struct sockaddr_in
#include <netinet/tcp.h> // for TCP_NODELAY...
#include <arpa/inet.h>   // for inet_ntop...
#include <netdb.h>       // getaddrinfo, gethostby...

#include <memory>

#include "co/def.h"
#include "co/byte_order.h"
#include "co/co/sock.h"
#include "log/logging.h"

namespace tit {

namespace net {

enum Family {
  kIpv4 = AF_INET,
  kIpv6 = AF_INET6
};

class Address {
 public:
  using Ptr = std::shared_ptr<Address>;

//  static Ptr Create(const char* ip, uint16 port);

  virtual sockaddr* addr() = 0;
  virtual socklen_t addrlen() = 0;

  virtual uint16 port() const = 0;
  virtual void set_port(uint16 port) = 0;

  virtual Family family() = 0;

  virtual fastring ToString() = 0;
};

class IPv4Address : public Address {
 public:
  using Ptr = std::shared_ptr<IPv4Address>;

  static Ptr Create(const char* ip, uint16 port) {
    return std::make_shared<IPv4Address>(ip, port);
  }

  IPv4Address() {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
  }

  IPv4Address(const char* ip, uint16 port) {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = hton16(port);
    int res = inet_pton(AF_INET, ip, &addr_.sin_addr);
    if (res <=0 ) {
      LOG(ERROR) << "ip transform error";
    }
  }

  IPv4Address(const sockaddr_in& addr)
      : addr_(addr) {}

  uint16 port() const override {
    return ntoh16(addr_.sin_port);
  }
  void set_port(uint16 port) override {
    addr_.sin_port = hton16(port);
  }

  sockaddr* addr() override {
    return (sockaddr*)(&addr_);
  }

  socklen_t addrlen() override { return sizeof(addr_); }

  Family family() override { return kIpv4; }

  fastring ToString() override {
    return co::to_string(&addr_);
  }

 private:
  sockaddr_in addr_;
};


class IPv6Address : public Address {
 public:
  using Ptr = std::shared_ptr<IPv6Address>;

  static Ptr Create(const char* ip, uint16 port) {
    return std::make_shared<IPv6Address>(ip, port);
  }

  IPv6Address() {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin6_family = AF_INET6;
  }

  IPv6Address(const char* ip, uint16 port) {
    memset(&addr_, 0, sizeof(addr_));
    addr_.sin6_family = AF_INET6;
    addr_.sin6_port = hton16(port);
    int res = inet_pton(AF_INET6, ip, &addr_.sin6_addr);
    if (res <=0 ) {
      LOG(ERROR) << "ip transform error";
    }
  }

  IPv6Address(const sockaddr_in6& addr)
      : addr_(addr) {}

  uint16 port() const override {
    return ntoh16(addr_.sin6_port);
  }
  void set_port(uint16 port) override {
    addr_.sin6_port = hton16(port);
  }

  sockaddr* addr() override {
    return reinterpret_cast<sockaddr*>(&addr_);
  }

  socklen_t addrlen() override { return sizeof(addr_); }

  Family family() override { return kIpv6; }

  fastring ToString() override {
    return co::to_string(&addr_);
  }

 private:
  sockaddr_in6 addr_;
};


}  // namespace net

}  // namespace tit



#endif  // TIT_COROUTINE_ADDRESS_H
