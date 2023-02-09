//
// Created by titto on 2023/2/8.
//

#ifndef TIT_NETLOADER_URL_REQUEST_OBSERVER_H
#define TIT_NETLOADER_URL_REQUEST_OBSERVER_H

namespace tit {
namespace net {


class URLRequest;
class HttpRequestInfo;
class HttpResponseInfo;

// provide coarse-grained observer API, observes all URLRequest
class URLRequestObserver {
 public:
    virtual void OnRequestStart(URLRequest* request,
                              HttpRequestInfo* requestInfo) {};
    virtual void OnRequestEnd(URLRequest* request,
                              HttpRequestInfo* requestInfo,
                              HttpResponseInfo* responseInfo) {};
    virtual void OnRequestError(URLRequest* request, int err_code) {};
};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_URL_REQUEST_OBSERVER_H
