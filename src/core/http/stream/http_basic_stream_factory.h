//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_HTTP_BASIC_STREAM_FACTORY_H
#define TIT_NETLOADER_HTTP_BASIC_STREAM_FACTORY_H

#include "core/http/stream/http_stream_factory.h"

namespace tit {
namespace net {

class HttpNetworkSession;

class HttpBasicStreamFactory : public HttpStreamFactory {
 public:
  explicit HttpBasicStreamFactory(HttpNetworkSession* session);
  ~HttpBasicStreamFactory();

  std::unique_ptr<HttpStream> RequestStream(
      std::unique_ptr<ClientSocketHandle> connection,
      HttpRequestInfo *request_info
      ) override;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_BASIC_STREAM_FACTORY_H
