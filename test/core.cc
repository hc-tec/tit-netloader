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
//    params.protocol_type = net::HTTP1_1;
    params.request_info.url = net::URL("https://cm.bilibili.com/cm/api/fees/pc");
    params.request_info.method = net::Method::POST;
    net::HttpRequestHeaders& headers = params.request_info.headers;

    headers.PutHeaders("accept-encoding", "");
    headers.PutHeaders("accept", "*/*");
//    headers.PutHeaders(net::HttpHeaders::CONNECTION,
//                       net::HttpHeaders::Value::CONNECTION_KEEP_ALIVE);
    headers.PutHeaders("host", params.request_info.url.host());
    headers.PutHeaders("user-agent","Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.64 Safari/537.36 Edg/101.0.1210.53");

    params.request_info.body = std::make_shared<net::HttpRequestBufferBody>(
        "application/json;charset=UTF-8", "{\"uploads\":[{\"src_id\":4702,\"ad_server\":\"bilibili\",\"is_ad\":0,\"area\":1,\"ad_cb\":\"\",\"event\":\"show\",\"is_visible\":1,\"idx\":8,\"mid\":\"475310928\",\"client_version\":\"\",\"ts\":1673618582328,\"resource_id\":4694,\"load_ts\":1673618522357,\"server_type\":0,\"id\":1193803,\"event_from\":\"\",\"request_id\":\"1673618521140q172a25a189a133q1733\"}]}");
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    loader->Start();
  });
  char ch;
  std::cin >> ch;
}
