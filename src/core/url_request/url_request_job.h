//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_URL_REQUEST_JOB_H
#define TIT_NETLOADER_URL_REQUEST_JOB_H

namespace tit {
namespace net {

class URLRequest;

class URLRequestJob {
 public:
  explicit URLRequestJob(URLRequest* url_request);

  URLRequestJob(const URLRequestJob&) = delete;
  URLRequestJob& operator=(const URLRequestJob&) = delete;

  virtual ~URLRequestJob();

  URLRequest* url_request() const { return url_request_; }

  virtual int Start() = 0;

 protected:
  URLRequest* url_request_;
};

class URLRequestErrorJob : public URLRequestJob {
 public:

  explicit URLRequestErrorJob(URLRequest* request);

  int Start() override;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_URL_REQUEST_JOB_H
