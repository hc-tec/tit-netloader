//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_H
#define TIT_NETLOADER_URL_REQUEST_H

#include <memory>
#include <string>
#include <vector>

#include "core/base/request_priority.h"
#include "core/base/url/url.h"
#include "core/http/request/http_request_info.h"
//#include "core/http/response/http_response_info.h"
#include "core/http/http_request_observer.h"

namespace tit {
namespace net {

struct HttpResponseInfo;
class URLRequestContext;
class URLRequestJob;


class URLRequest : public HttpRequestObserver {
 public:

  class Delegate {

  };

  URLRequest(const URL& url,
             RequestPriority priority,
             Delegate* delegate,
             URLRequestContext* context);

  URLRequest(const URLRequest&) = delete;
  URLRequest& operator=(const URLRequest&) = delete;

  ~URLRequest();

  URLRequestContext* context() { return context_; }

  URL& origin_url() { return url_chain_.front(); }
  URL& url() { return url_chain_.back(); }

  std::string method() { return method_; }
  void set_method(std::string method) { method_ = std::move(method); }

  HttpRequestInfo* request_info() { return &request_info_; }
  void set_request_info(const HttpRequestInfo& request_info) {
    request_info_ = request_info;
  }

  RequestPriority priority() { return priority_; }
  void set_priority(RequestPriority priority) { priority_ = priority; }

  int load_flags() const { return load_flags_; }
  void set_load_flags(int load_flags) { load_flags_ = load_flags; }

  void Start();

  // notify observers
  void OnRequestStart();
  void OnRequestEnd();
  void OnRequestError(int err_code);

  // HttpRequestObserver
  void OnResponseAllReceived(HttpNetworkSession* session,
                             HttpRequestInfo* request_info,
                             HttpResponseInfo* response_info) override;

 private:

  Delegate* delegate_;

  URLRequestContext* context_;

  std::vector<URL> url_chain_;
  std::string method_;
  HttpRequestInfo request_info_;
  HttpResponseInfo* response_info_;
  RequestPriority priority_;

  URL redirect_url_;

  std::unique_ptr<URLRequestJob> job_;

  int load_flags_;

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_H
