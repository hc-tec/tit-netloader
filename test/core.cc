//
// Created by titto on 2022/5/27.
//

#include <co/co.h>

#include <iostream>

#include "core/version.h"
#include "core/http/request/http_request_body.h"
#include "core/network/network_service.h"
#include "core/network/request_params.h"
#include "core/socket/tcp/address.h"

using namespace tit;

int main() {
  go([]() {

    net::NetworkService* service = net::GetNetworkService();
    net::RequestParams params;
    params.request_info.url = net::URL("http://baidu.com");
    params.request_info.method = net::Method::POST;
    net::HttpRequestHeaders& headers = params.request_info.headers;

    headers.PutHeaders(net::HttpHeaders::ACCEPT_ENCODING,
                       "gzip, deflate");
    headers.PutHeaders(net::HttpHeaders::ACCEPT,
                       "application/json, text/plain, */*");
    headers.PutHeaders(net::HttpHeaders::CONNECTION,
                       net::HttpHeaders::Value::CONNECTION_KEEP_ALIVE);
    headers.PutHeaders(net::HttpHeaders::ACCEPT_ENCODING,
                       "gzip, deflate");
    headers.PutHeaders(net::HttpHeaders::HOST,
                       params.request_info.url.host() + ":" +
                           std::to_string(params.request_info.url.port()));
    headers.PutHeaders(net::HttpHeaders::USER_AGENT,
                       "tit net loader" TIT_NET_LOADER_VERSION);
    params.request_info.body = std::make_shared<net::HttpRequestBufferBody>(
        "application/json;charset=UTF-8",
        "{\"username\":\"152709494\",\"password\":\"yigeren\"}");
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    loader->Start();
  });
  char ch;
  std::cin >> ch;
}
