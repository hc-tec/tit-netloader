//
// Created by titto on 2022/5/28.
//

#include "url_request_http_job.h"

#include "core/http/http_transaction.h"
#include "core/http/http_transaction_factory.h"
#include "core/http/request/http_request_info.h"
#include "core/http/response/http_response_info.h"
#include "core/url_request/url_request.h"
#include "core/url_request/url_request_context.h"
#include "core/url_request/url_request_job_factory.h"

namespace tit {
namespace net {

std::unique_ptr<URLRequestJob> URLRequestHttpJob::Create(URLRequest *request) {
  return std::make_unique<URLRequestHttpJob>(request);
}

URLRequestHttpJob::URLRequestHttpJob(URLRequest *url_request)
    : URLRequestJob(url_request),
      priority_(url_request->priority()),
      request_info_(url_request->request_info()) {

}

URLRequestHttpJob::~URLRequestHttpJob() {}

void URLRequestHttpJob::Start() {
  // integrate with cookies
  // then start transaction
  StartTransaction();
}

void URLRequestHttpJob::StartTransaction() {
  if (transaction_.get() == nullptr) {
    HttpTransactionFactory* transaction_factory =
        url_request_->context()->transaction_factory();
    transaction_ = transaction_factory->CreateTransaction();
    transaction_->Start(url_request_->request_info());
  } else {
    transaction_->Restart();
  }
}

}  // namespace net
}  // namespace tit