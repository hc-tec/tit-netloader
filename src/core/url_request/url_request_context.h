//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_CONTEXT_H
#define TIT_NETLOADER_URL_REQUEST_CONTEXT_H

#include <memory>

namespace tit {
namespace net {

class HttpTransactionFactory;
class URLRequestJobFactory;

class URLRequestContext {
 public:

 private:
  std::unique_ptr<URLRequestJobFactory> url_request_job_factory_;
  std::unique_ptr<HttpTransactionFactory> http_transaction_factory_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_CONTEXT_H
