//
// Created by titto on 2022/5/28.
//

#include "http_transaction.h"

namespace tit {
namespace net {

HttpTransaction::HttpTransaction(URLRequestContext *url_request_context)
    : url_request_context_(url_request_context) {}

}  // namespace net
}  // namespace tit