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
                                net::HttpResponseInfo *response_info,
                                std::string raw_response) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnResponseHeaderReceived";
  }
  void OnResponseBodyReceived(net::HttpNetworkSession *session,
                              net::HttpResponseInfo *response_info,
                              std::string raw_response) override {
    LOG(INFO) << "HttpRequestObserverTest" " OnResponseBodyReceived";
  }
};

int main() {
  go([]() {

    net::NetworkService* service = net::GetNetworkService();
    std::shared_ptr<HttpRequestObserverTest> httpRequestObserverTest =
        std::make_shared<HttpRequestObserverTest>();
//    httpRequestObserverTest.reset();
    std::weak_ptr<HttpRequestObserverTest> httpRequestObserverTest_weak(
        HttpRequestObserverTest);
    service->AddHttpRequestObserver(httpRequestObserverTest);
//    service->RemoveHttpRequestObserver(httpRequestObserverTest_weak);
    net::RequestParams params;
    params.request_info.url = net::URL("http://148.70.204.53:3001/signin/");
    params.request_info.method = net::Method::POST;
    params.request_info.SetAddressByUrl();
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    if (loader != nullptr) {
      loader->Start();
    } else {

    }
  });
  char ch;
  std::cin >> ch;
}
