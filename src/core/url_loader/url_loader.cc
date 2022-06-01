//
// Created by titto on 2022/5/27.
//

#include "url_loader.h"

#include "core/http/http_transaction_factory.h"
#include "core/network/host_resolver.h"
#include "core/network/network_context.h"
#include "core/network/request_params.h"
#include "core/network/resource_scheduler.h"
#include "core/url_request//url_request_context.h"
#include "core/url_request/url_request.h"
#include "core/url_request/url_request_context_builder.h"
#include "core/url_request/url_request_job_factory.h"

namespace tit {
namespace net {

URLLoader::URLLoader(uint64 request_id,
                     const RequestParams &request_params,
                     NetworkContext *network_context,
                     URLLoader::Delegate *delegate)
    : request_id_(request_id),
      delegate_(delegate),
      network_context_(network_context),
      resource_scheduler_(network_context->resource_scheduler()),
      url_request_context_builder_(
          network_context_->url_request_context_builder()) {

  url_request_context_ = url_request_context_builder_->Build();
  url_request_ = url_request_context_->
                 CreateURLRequest(request_params.request_info.url,
                                  request_params.priority,
                                  request_params,
                                  this);
  url_request_->set_request_info(request_params.request_info);
}


URLLoader::~URLLoader() {

}

void URLLoader::Start() {
  url_request_->Start();
}

}  // namespace net
}  // namespace tit