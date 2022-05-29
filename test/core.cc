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

    net::NetworkService* service = net::GetNetworkService();
    net::RequestParams params;
    params.request_info.url = net::URL("http://148.70.204.53:3001/signin/");
    params.request_info.method = net::Method::POST;
    params.request_info.SetAddressByUrl();
    net::HttpRequestHeaders& headers = params.request_info.headers;

    headers.PutHeaders(net::HttpHeaders::ACCEPT_ENCODING,
                       "gzip, deflate");
    headers.PutHeaders(net::HttpHeaders::ACCEPT,
                       "application/json, text/plain, */*");
    headers.PutHeaders(net::HttpHeaders::CONNECTION,
                       net::HttpHeaders::Value::CONNECTION_UPGRADE);
    headers.PutHeaders(net::HttpHeaders::ACCEPT_ENCODING,
                       "gzip, deflate");
    headers.PutHeaders(net::HttpHeaders::HOST,
                       params.request_info.url.host() + ":" + std::to_string(params.request_info.url.port()));
    headers.PutHeaders(net::HttpHeaders::USER_AGENT,
                       "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.64 Safari/537.36 Edg/101.0.1210.53");
    params.request_info.body = std::make_shared<net::HttpRequestBufferBody>(
        "application/json;charset=UTF-8",
        "{\"username\":\"15270949466\",\"password\":\"yigeren1.\"}");
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    loader->Start();
  });
  std::cout << "hello " << std::endl;
  char ch;
  std::cin >> ch;
}
