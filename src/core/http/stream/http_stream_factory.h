//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_STREAM_FACTORY_H
#define TIT_NETLOADER_HTTP_STREAM_FACTORY_H

#include <memory>

#include "core/http/stream/http_stream.h"

namespace tit {
namespace net {

class ClientSocketHandle;
class HttpNetworkSession;
class HttpStream;
class HttpRequestInfo;

class HttpStreamFactory {
 public:
  explicit HttpStreamFactory(HttpNetworkSession* session);

  virtual ~HttpStreamFactory();

  virtual std::unique_ptr<HttpStream> RequestStream(
      std::unique_ptr<ClientSocketHandle> connection,
      HttpRequestInfo* request_info,
      HttpStream::Delegate* delegate) = 0;

 private:
  HttpNetworkSession* session_;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_STREAM_FACTORY_H
