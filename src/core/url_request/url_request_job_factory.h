//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_JOB_FACTORY_H
#define TIT_NETLOADER_URL_REQUEST_JOB_FACTORY_H

#include <map>
#include <memory>
#include <string>

namespace tit {
namespace net {

class URLRequest;
class URLRequestJob;

class URLRequestJobFactory {
 public:
  class ProtocolHandler {
   public:
    virtual ~ProtocolHandler();

    virtual std::unique_ptr<URLRequestJob> CreateJob(
        URLRequest* request) const = 0;
  };

  URLRequestJobFactory();

  URLRequestJobFactory(const URLRequestJobFactory&) = delete;
  URLRequestJobFactory& operator=(const URLRequestJobFactory&) = delete;

  virtual ~URLRequestJobFactory();

  bool SetProtocolHandler(const std::string& scheme,
                          std::unique_ptr<ProtocolHandler> protocol_handler);

  virtual std::unique_ptr<URLRequestJob> CreateJob(URLRequest* request) const;

 private:
  using ProtocolHandlerMap =
    std::map<std::string, std::unique_ptr<ProtocolHandler>>;
  ProtocolHandlerMap handler_map_;
};

class HttpProtocolHandler : public URLRequestJobFactory::ProtocolHandler {
 public:
  std::unique_ptr<URLRequestJob> CreateJob(URLRequest* request) const override;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_JOB_FACTORY_H
