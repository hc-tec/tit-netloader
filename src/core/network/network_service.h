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
class URLRequestObserver;

class NetworkService : public URLLoader::Delegate {
 public:

  NetworkService();
  ~NetworkService();

   std::unique_ptr<URLLoader> CreateURLLoader(
      RequestParams& request_params);

  void AddURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  void RemoveURLLoaderInterceptor(
      std::shared_ptr<URLLoaderInterceptor> interceptor);

  bool SetProtocolHandler(const std::string& scheme,
                          std::unique_ptr<URLRequestJobFactory::ProtocolHandler>
                          protocol_handler);

  void AddURLRequestObserver(
      std::weak_ptr<URLRequestObserver> observer);

  void RemoveURLRequestObserver(
      std::weak_ptr<URLRequestObserver> observer);

 private:
  friend URLLoaderInterceptor;

  std::unique_ptr<NetworkContext> network_context_;
  std::unique_ptr<RequestManager> request_manager_;
  std::unique_ptr<URLLoaderFactory> url_loader_factory_;
};

NetworkService* GetNetworkService();

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_NETWORK_SERVICE_H
