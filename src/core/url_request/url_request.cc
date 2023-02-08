//
// Created by titto on 2022/5/28.
//

#include "url_request.h"

#include "core/base/net_error.h"
#include "core/http/http_transaction_factory.h"
#include "core/network/host_resolver.h"
#include "core/network/network_context.h"
#include "core/network/resource_scheduler.h"
#include "core/url_request/url_request_context.h"
#include "core/url_request/url_request_context_builder.h"
#include "core/url_request/url_request_job.h"
#include "core/url_request/url_request_job_factory.h"
#include "core/url_request/url_request_observer.h"

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
  OnRequestStart();
  job_ = context_->job_factory()->CreateJob(this);
  int rv = job_->Start();
  if (rv != OK) {
    OnRequestError(rv);
    return;
  }
  OnRequestEnd();
}

void URLRequest::OnRequestStart() {
  auto observers = context_->network_context()->url_request_observers_;
  for(auto& observer : observers) {
    if (!observer.expired()) {
      auto obs_shared = observer.lock();
      obs_shared->OnRequestStart(this, &request_info_);
    }
  }
}

void URLRequest::OnRequestEnd() {
  auto observers = context_->network_context()->url_request_observers_;
  for(auto& observer : observers) {
    if (!observer.expired()) {
      auto obs_shared = observer.lock();
      obs_shared->OnRequestEnd(this, response_info_);
    }
  }
}

void URLRequest::OnRequestError(int err_code) {
  auto observers = context_->network_context()->url_request_observers_;
  for(auto& observer : observers) {
    if (!observer.expired()) {
      auto obs_shared = observer.lock();
      obs_shared->OnRequestError(this, err_code);
    }
  }
}
void URLRequest::OnResponseAllReceived(HttpNetworkSession *session,
                                       HttpRequestInfo *request_info,
                                       HttpResponseInfo *response_info) {
  response_info_ = response_info;
}

}  // namespace net
}  // namespace tit