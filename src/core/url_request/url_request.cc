//
// Created by titto on 2022/5/28.
//

#include "url_request.h"

#include "core/http/http_transaction_factory.h"
#include "core/url_request/url_request_job.h"
#include "core/url_request/url_request_job_factory.h"
#include "core/url_request/url_request_context.h"

namespace tit {
namespace net {


URLRequest::URLRequest(const URL &url,
                       RequestPriority priority,
                       URLRequest::Delegate *delegate,
                       URLRequestContext *context)
    : delegate_(delegate),
      context_(context),
      priority_(priority),
      load_flags_(0) {
  url_chain_.push_back(url);
}

URLRequest::~URLRequest() {

}

void URLRequest::Start() {
  job_ = context_->job_factory()->CreateJob(this);
  job_->Start();
}

}  // namespace net
}  // namespace tit