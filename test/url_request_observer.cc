//
// Created by titto on 2023/2/8.
//


#include <co/co.h>

#include <iostream>

#include "core/base/net_error.h"
#include "core/http/request/http_request_body.h"
#include "core/network/network_service.h"
#include "core/network/request_params.h"
#include "core/url_request/url_request_observer.h"
#include "core/http/response/http_response_info.h"

using namespace tit;

class URLRequestObserverTest : public net::URLRequestObserver {
 public:
  void OnRequestStart(net::URLRequest *request,
                      net::HttpRequestInfo *requestInfo) override {
    LOG(DEBUG) << "OnRequestStart: " << requestInfo->url;
  }
  void OnRequestEnd(net::URLRequest *request,
                    net::HttpResponseInfo *responseInfo) override {
    LOG(DEBUG) << "OnRequestEnd: " << responseInfo->status;
  }
  void OnRequestError(net::URLRequest *request, int err_code) override {
    LOG(DEBUG) << "OnRequestError: " << net::ErrorToString(err_code);
  }
};

int main() {
  go([]() {

    net::NetworkService* service = net::GetNetworkService();
    std::shared_ptr<URLRequestObserverTest> urlRequestObserverTest =
        std::make_shared<URLRequestObserverTest>();
    service->AddURLRequestObserver(urlRequestObserverTest);
    net::RequestParams params;
    params.request_info.url = net::URL("http://148.70.204.53:3001/static/rest_framework/css/prettify.css");
    params.request_info.method = net::Method::GET;
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
