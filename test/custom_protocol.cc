//
// Created by titto on 2022/5/29.
//

#include <iostream>
#include <co/co.h>

#include "core/network/network_service.h"
#include "core/url_loader/request_params.h"
//#include "core/url_request/url_request.h"
#include "core/url_request/url_request_job.h"
#include "core/url_request/url_request_job_factory.h"

using namespace tit;

class TITTORequestJob : public net::URLRequestJob {
 public:

  TITTORequestJob(net::URLRequest* request)
      : URLRequestJob(request) {}

  void Start() override {
    LOG(INFO) << "Titto Protocol Called";
  }

};

class TITTOProtocolHandler : public net::URLRequestJobFactory::ProtocolHandler {
 public:
  std::unique_ptr<net::URLRequestJob> CreateJob(
      net::URLRequest* request) const override {
    return std::make_unique<TITTORequestJob>(request);
  }
};

int main() {
  go([]() {

    net::NetworkService* service = net::GetNetworkService();
    service->SetProtocolHandler("titto",
                                std::make_unique<TITTOProtocolHandler>());

    net::RequestParams params;
    params.request_info.url = net::URL("titto://1.2.3.4/signin/");
    params.request_info.method = net::Method::HEAD;
    params.request_info.SetAddressByUrl();
    std::unique_ptr<net::URLLoader> loader = service->CreateURLLoader(params);
    loader->Start();
  });
  char ch;
  std::cin >> ch;
}
