//
// Created by titto on 2022/5/29.
//

#include "core/url_loader/url_loader_interceptor.h"

#include <co/co.h>

#include <iostream>

#include "core/http/request/http_request_body.h"
#include "core/network/network_service.h"
#include "core/network/request_params.h"

using namespace tit;

class URLLoaderInterceptorTest : public net::URLLoaderInterceptor {
 public:
  ~URLLoaderInterceptorTest() override {}

  bool Interceptor(net::NetworkService* service,
                   net::RequestParams* params) override {
    if (params->request_info.method == net::Method::HEAD) {
      params->request_info.method = net::Method::GET;
    }
    return true;
  }

};

int main() {
  go([]() {

    net::NetworkService* service = net::GetNetworkService();
    service->AddURLLoaderInterceptor(
        std::make_shared<URLLoaderInterceptorTest>());

    net::RequestParams params;
    params.request_info.url = net::URL("http://148.70.204.53:3001/static/rest_framework/css/prettify.css");
    params.request_info.method = net::Method::HEAD;
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
