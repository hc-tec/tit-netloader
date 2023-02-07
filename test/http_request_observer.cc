//
// Created by titto on 2022/5/30.
//

#include <co/co.h>

#include <iostream>

#include "core/http/http_request_observer.h"
#include "core/http/request/http_request_body.h"
#include "core/network/network_service.h"
#include "core/network/request_params.h"

using namespace tit;

class HttpRequestObserverTest : public net::HttpRequestObserver {
 public:
  void OnConnected(net::HttpNetworkSession *session,
                   net::HttpRequestInfo *request_info) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnConnected";
  }
  void OnBeforeRequest(net::HttpNetworkSession *session,
                       net::HttpRequestInfo *request_info,
                       std::string &request_msg) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnBeforeRequest";
  }
  void OnResponseHeaderReceived(net::HttpNetworkSession *session,
                                net::HttpRequestInfo *request_info,
                                net::HttpResponseInfo *response_info,
                                const std::string& raw_response) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnResponseHeaderReceived";
  }
  void OnResponseBodyReceived(net::HttpNetworkSession *session,
                              net::HttpRequestInfo *request_info,
                              net::HttpResponseInfo *response_info,
                              const std::string& raw_response) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnResponseBodyReceived";
  }
  void OnHostResolved(net::HttpNetworkSession *session,
                      net::HttpRequestInfo *request_info,
                      bool need_host_resolve,
                      const std::string& dns_ip) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnHostResolved " << dns_ip;
  }

  void OnHostResolveError(net::HttpNetworkSession *session,
                          net::HttpRequestInfo *request_info) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnHostResolveError "
              << request_info->url.origin_url();
  }
  void OnConnectClosed(net::HttpNetworkSession *session,
                       net::HttpRequestInfo *request_info,
                       net::HttpResponseInfo *response_info) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnConnectClosed ";
  }
  void OnResponseAllReceived(net::HttpNetworkSession *session,
                             net::HttpRequestInfo *request_info,
                             net::HttpResponseInfo *response_info) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnResponseAllReceived ";
  }
};

void send_request(const char *url,
                  net::Method method,
                  net::HttpRequestHeaders headers,
                  std::unique_ptr<net::HttpRequestBody> body) {
  net::NetworkService* service = net::GetNetworkService();
  std::shared_ptr<HttpRequestObserverTest> httpRequestObserverTest =
      std::make_shared<HttpRequestObserverTest>();
//    httpRequestObserverTest.reset();
  std::weak_ptr<HttpRequestObserverTest> httpRequestObserverTest_weak(
      HttpRequestObserverTest);
  service->AddHttpRequestObserver(httpRequestObserverTest);
//    service->RemoveHttpRequestObserver(httpRequestObserverTest_weak);
  net::RequestParams params;
  params.request_info.url = net::URL(url);
  params.request_info.method = method;
  params.request_info.headers = headers;
  params.request_info.body = std::move(body);
//    params.request_info.SetAddressByUrl();
  std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
  if (loader != nullptr) {
    loader->Start();
  } else {

  }
}

int main() {
  for (int i = 0; i < 1; ++i) {
    go([]() {
      net::HttpRequestHeaders headers;
      std::unique_ptr<net::HttpRequestBody> body =
          std::make_unique<net::HttpRequestBufferBody>("application/json", "{}");
      send_request("https://baidu.com", net::Method::GET,
                   headers, std::move(body));
    });
  }
  char ch;
  std::cin >> ch;
}
