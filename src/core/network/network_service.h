//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_NETWORK_SERVICE_H
#define TIT_NETLOADER_NETWORK_SERVICE_H

#include <memory>

#include "core/url_loader/url_loader.h"
#include "core/url_request/url_request_job_factory.h"

namespace tit {
namespace net {

struct RequestParams;

class NetworkContext;
class RequestManager;
class URLLoaderFactory;
class URLLoaderInterceptor;
class HttpRequestObserver;

class NetworkService : public URLLoader::Delegate {
 public:

  NetworkService();
  ~NetworkService();

  NetworkContext* network_context() { return network_context_.get(); }

   std::unique_ptr<URLLoader> CreateURLLoader(
      RequestParams& request_params);

  void AddURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  void RemoveURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  bool SetProtocolHandler(const std::string& scheme,
                          std::unique_ptr<URLRequestJobFactory::ProtocolHandler>
                          protocol_handler);

  void AddHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

  void RemoveHttpRequestObserver(
      std::weak_ptr<HttpRequestObserver> observer);

 private:
  friend URLLoaderInterceptor;

  std::unique_ptr<NetworkContext> network_context_;
  std::unique_ptr<RequestManager> request_manager_;
  std::unique_ptr<URLLoaderFactory> url_loader_factory_;
};

inline NetworkService* GetNetworkService() {
  static NetworkService service;
  return &service;
}

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_NETWORK_SERVICE_H
