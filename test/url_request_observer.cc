//
// Created by titto on 2022/5/30.
//

#include "core/url_request//url_request_observer.h"

#include <co/co.h>

#include <iostream>

#include "core/http/request/http_request_body.h"
#include "core/network/network_service.h"
#include "core/network/request_params.h"

using namespace tit;

class URLRequestObserverTest : public net::URLRequestObserver {
 public:
  void OnConnected(net::HttpNetworkSession *session,
                   net::HttpRequestInfo *request_info) override {
    LOG(INFO) << "URLRequestObserverTest" " OnConnected";
  }
  void OnBeforeRequest(net::HttpNetworkSession *session,
                       net::HttpRequestInfo *request_info,
                       std::string &request_msg) override {
    LOG(INFO) << "URLRequestObserverTest" " OnBeforeRequest";
  }
  void OnResponseHeaderReceived(net::HttpNetworkSession *session,
                                net::HttpResponseInfo *response_info,
                                std::string raw_response) override {
    LOG(INFO) << "URLRequestObserverTest" " OnResponseHeaderReceived";
  }
  void OnResponseBodyReceived(net::HttpNetworkSession *session,
                              net::HttpResponseInfo *response_info,
                              std::string raw_response) override {
    LOG(INFO) << "URLRequestObserverTest" " OnResponseBodyReceived";
  }
};

int main() {
  go([]() {

    net::NetworkService* service = net::GetNetworkService();
    std::shared_ptr<URLRequestObserverTest> urlRequestObserverTest =
        std::make_shared<URLRequestObserverTest>();
//    urlRequestObserverTest.reset();
    std::weak_ptr<URLRequestObserverTest> urlRequestObserverTest_weak(urlRequestObserverTest);
    service->AddURLRequestObserver(urlRequestObserverTest_weak);
//    service->RemoveURLRequestObserver(urlRequestObserverTest_weak);
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
