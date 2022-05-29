//
// Created by titto on 2022/5/29.
//

#include <iostream>
#include <co/co.h>

#include "core/network/network_service.h"
#include "core/url_loader/request_params.h"
#include "core/http/request/http_request_body.h"
#include "core/url_loader/url_loader_interceptor.h"

using namespace tit;

class URLLoaderInterceptorTest : public net::URLLoaderInterceptor {
 public:
  ~URLLoaderInterceptorTest() override {}

  bool Interceptor(net::NetworkService* service,
                   net::RequestParams* params) override {
    if (params->request_info.method == net::Method::HEAD) {
      params->request_info.method = net::Method::POST;
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
    params.request_info.url = net::URL("http://148.70.204.53:3001/signin/");
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
