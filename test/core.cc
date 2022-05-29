//
// Created by titto on 2022/5/27.
//

#include <iostream>
#include <co/co.h>

#include "core/network/network_service.h"
#include "core/url_loader/request_params.h"
#include "core/socket/tcp/address.h"
#include "core/http/request/http_request_body.h"

using namespace tit;

int main() {
  go([]() {
    net::Address::Ptr address =
        net::IPv4Address::Create("148.70.204.53", 3001);
    net::NetworkService* service = net::GetNetworkService();
    net::RequestParams params;
    params.request_info.method = net::Method::GET;
    params.request_info.address = std::move(address);
    params.request_info.body = std::make_shared<net::HttpRequestBufferBody>(
        "", "123"
        );
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    loader->Start();

    co::sleep(1000);
    std::cout << "run coroutine" << std::endl;
  });
  std::cout << "hello " << std::endl;
  co::sleep(1500);
}
