//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_TRANSACTION_H
#define TIT_NETLOADER_HTTP_TRANSACTION_H

namespace tit {
namespace net {

class HttpRequestInfo;
class HttpResponseInfo;

class HttpTransaction {
 public:
  virtual ~HttpTransaction() {}

  virtual int Start(HttpRequestInfo* request_info) = 0;

  virtual int Restart() = 0;

  virtual const HttpResponseInfo* GetResponseInfo() const = 0;

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_TRANSACTION_H
