//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_HTTP_JOB_H
#define TIT_NETLOADER_URL_REQUEST_HTTP_JOB_H

#include <memory>

#include "core/base/request_priority.h"
#include "core/url_request/url_request_job.h"

namespace tit {
namespace net {

class HttpRequestInfo;
class HttpResponseInfo;
class HttpTransaction;

class URLRequestHttpJob : public URLRequestJob {
 public:

  static std::unique_ptr<URLRequestJob> Create(URLRequest* request);

  URLRequestHttpJob(URLRequest* url_request);

  URLRequestHttpJob(const URLRequestHttpJob&) = delete;
  URLRequestHttpJob& operator=(const URLRequestHttpJob&) = delete;

  ~URLRequestHttpJob() override;

  void Start() override;

 private:

  void StartTransaction();

  RequestPriority priority_;
  HttpRequestInfo* request_info_;
  HttpResponseInfo* response_info_;
  std::unique_ptr<HttpTransaction> transaction_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_HTTP_JOB_H
