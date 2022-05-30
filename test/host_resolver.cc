//
// Created by titto on 2022/5/30.
//

#include <co/co.h>

#include <iostream>

#include "core/http/request/http_request_body.h"
#include "core/network/network_service.h"
#include "core/network/request_params.h"

#include "core/network/host_resolver.h"

using namespace tit;

int main() {
  go([]() {
    net::URL url = net::URL("http://baidu.com");

    net::SimpleHostResolver host_resolver;
    host_resolver.Start(url);
    net::Address::Ptr address = host_resolver.GetAddressResult();

    std::cout << url.origin_url() << "'s ip address is: "
              << address->ToString() << std::endl;

  });
  char ch;
  std::cin >> ch;
}
