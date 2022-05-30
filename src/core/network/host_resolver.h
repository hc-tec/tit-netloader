//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HOST_RESOLVER_H
#define TIT_NETLOADER_HOST_RESOLVER_H

#include "core/base/url/url.h"
#include "core/socket/tcp/address.h"

namespace tit {
namespace net {

class HostResolver {
 public:
  explicit HostResolver();
  ~HostResolver() = default;

  virtual std::unique_ptr<HostResolver> Create() = 0;

  virtual void Start(const URL& url) = 0;

  virtual Address::Ptr GetAddressResult() = 0;

 protected:
  URL url_;
};

class SimpleHostResolver : public HostResolver {
 public:
  explicit SimpleHostResolver();

  std::unique_ptr<HostResolver> Create() override;

  void Start(const URL& url) override;
  Address::Ptr GetAddressResult() override;

 private:
  Address::Ptr addr_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HOST_RESOLVER_H
