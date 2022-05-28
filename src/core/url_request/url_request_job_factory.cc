//
// Created by titto on 2022/5/28.
//

#include "url_request_job_factory.h"

#include "core/base/url/url_constants.h"
#include "core/url_request/url_request.h"
#include "core/url_request/url_request_job.h"
#include "log/logging.h"

namespace tit {
namespace net {

URLRequestJobFactory::ProtocolHandler::~ProtocolHandler() = default;

URLRequestJobFactory::URLRequestJobFactory() {
  SetProtocolHandler(kHttpScheme,
                     std::make_unique<HttpProtocolHandler>());
  SetProtocolHandler(kHttpsScheme,
                     std::make_unique<HttpProtocolHandler>());
  SetProtocolHandler(kWsScheme,
                     std::make_unique<HttpProtocolHandler>());
  SetProtocolHandler(kWssScheme,
                     std::make_unique<HttpProtocolHandler>());
}

URLRequestJobFactory::~URLRequestJobFactory() {}

bool URLRequestJobFactory::SetProtocolHandler(
    const std::string &scheme,
    std::unique_ptr<ProtocolHandler> protocol_handler) {
  handler_map_[scheme] = std::move(protocol_handler);
}

std::unique_ptr<URLRequestJob> URLRequestJobFactory::CreateJob(
    URLRequest *request) const {
    std::string scheme = request->url().scheme();
    auto it = handler_map_.find(scheme);
    if (it == handler_map_.end()) {
      LOG(ERROR) << "Scheme: " << scheme << " not find protocol handler";
      return std::make_unique<URLRequestErrorJob>(request);
    }
    ProtocolHandler* handler = it->second.get();
    return handler->CreateJob(request);
}

std::unique_ptr<URLRequestJob> HttpProtocolHandler::CreateJob(
    URLRequest *request) const {
  return std::unique_ptr<URLRequestJob>();
}

}  // namespace net
}  // namespace tit