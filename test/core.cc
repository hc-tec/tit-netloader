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
    params.request_info.url = net::URL("https://blog.csdn.net/Emperor10/article/details/123179056");
    params.request_info.method = net::Method::GET;
    net::HttpRequestHeaders& headers = params.request_info.headers;

    headers.PutHeaders("accept-encoding", "gzip, deflate, br");
    headers.PutHeaders("accept", "*/*");
//    headers.PutHeaders(net::HttpHeaders::CONNECTION,
//                       net::HttpHeaders::Value::CONNECTION_KEEP_ALIVE);
    headers.PutHeaders("host", params.request_info.url.host());
    headers.PutHeaders("user-agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.64 Safari/537.36 Edg/101.0.1210.53");

//    headers.PutHeaders("upgrade-insecure-requests","1");
//    headers.PutHeaders(":scheme","https");
//    headers.PutHeaders(":authority","zhuanlan.zhihu.com");
//    headers.PutHeaders(":method","GET");

//    headers.PutHeaders("dnt","1");
//    headers.PutHeaders("sec-ch-ua","\" Not A;Brand\";v=\"99\", \"Chromium\";v=\"101\", \"Microsoft Edge\";v=\"101\"");
//    headers.PutHeaders("sec-fetch-site","same-origin");
//    headers.PutHeaders("accept-language","zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6");
//    headers.PutHeaders(":path","/");
//
//    headers.PutHeaders("content-type","/p/133375078");
//    headers.PutHeaders("referer","https://github.com/");

//    params.request_info.body = std::make_shared<net::HttpRequestBufferBody>(
//        "application/json;charset=UTF-8", "ping");
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    loader->Start();
  });
  char ch;
  std::cin >> ch;
}
