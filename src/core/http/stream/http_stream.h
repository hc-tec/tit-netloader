//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_STREAM_H
#define TIT_NETLOADER_HTTP_STREAM_H

namespace tit {
namespace net {

class HttpRequestInfo;
class HttpResponseInfo;

class HttpStream {
 public:
  virtual ~HttpStream() {}

  virtual void RegisterRequest(HttpRequestInfo* request_info) = 0;

  virtual int InitializeStream() = 0;

  virtual int SendRequest(HttpResponseInfo* response_info) = 0;

  virtual int ReadResponseHeaders() = 0;

  virtual int ReadResponseBody() = 0;

  virtual void Close() = 0;

};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_STREAM_H
