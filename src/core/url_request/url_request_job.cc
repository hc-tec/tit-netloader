//
// Created by titto on 2022/5/28.
//

#include "url_request_job.h"

#include "core/base/net_error.h"
#include "core/url_request/url_request.h"
#include "log/logging.h"

namespace tit {
namespace net {

URLRequestJob::URLRequestJob(URLRequest *url_request)
    : url_request_(url_request) {

}

URLRequestJob::~URLRequestJob() {}



URLRequestErrorJob::URLRequestErrorJob(URLRequest *request)
    : URLRequestJob(request) {}

int URLRequestErrorJob::Start() {
  LOG(ERROR) << "URLRequestErrorJob execute";
  return ERR_FAILED;
}

}  // namespace net
}  // namespace tit