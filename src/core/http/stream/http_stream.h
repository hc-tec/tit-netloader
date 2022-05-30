//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_STREAM_H
#define TIT_NETLOADER_HTTP_STREAM_H

#include <string>

namespace tit {
namespace net {

struct HttpRequestInfo;
struct HttpResponseInfo;

class HttpStream {
 public:

  class Delegate {
   public:
    virtual ~Delegate() = default;

    virtual void OnConnected(HttpRequestInfo* request_info) = 0;
    virtual void OnBeforeRequest(HttpRequestInfo* request_info,
                                 std::string& request_msg) = 0;
    virtual void OnResponseHeaderReceived(HttpResponseInfo* response_info,
                                          const std::string& raw_response) = 0;
    virtual void OnResponseBodyReceived(HttpResponseInfo* response_info,
                                        const std::string& raw_response) = 0;
  };

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
