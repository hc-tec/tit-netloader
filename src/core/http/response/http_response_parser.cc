//
// Created by titto on 2022/5/29.
//

#include "http_response_parser.h"

#include <http_parser.h>

#include <cassert>
#include <cstring>

#include <string>

#include "core/http/http_status.h"
#include "core/http/response/http_response_info.h"
#include "log/logging.h"

namespace tit {
namespace net {


size_t strnlen(const char* s, size_t maxlen)
{
  const char* p = (const char*)memchr(s, '\0', maxlen);
  if (p == NULL)
    return maxlen;

  return p - s;
}

size_t strlncat(char* dst, size_t len, const char* src, size_t n)
{
  size_t slen = strnlen(src, n);
  size_t dlen = strnlen(dst, len);

  if (dlen < len) {
    size_t rlen = len - dlen;
    size_t ncpy = slen < rlen ? slen : (rlen - 1);
    memcpy(dst + dlen, src, ncpy);
    dst[dlen + ncpy] = '\0';
  }

  assert(len > slen + dlen);
  return slen + dlen;
}


int message_begin_cb(http_parser* p)
{
  return 0;
}

int response_status_cb(http_parser* p, const char* buf, size_t len)
{
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);
  parser->response_info()->status = HttpStatus::HttpStatusMap[p->status_code];
//  LOG(TRACE) << "response status: "
//             << p->status_code << " "
//             << std::string(buf, len);
  return 0;
}

int header_field_cb(http_parser* p, const char* buf, size_t len)
{
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);
  parser->cur_header_field = std::string(buf, len);
//  LOG(TRACE) << "header field: " << std::string(buf, len).data();
  return 0;
}

int header_value_cb(http_parser* p, const char* buf, size_t len)
{
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);
  HttpResponseInfo* response_info = parser->response_info();
  response_info->headers.PutHeaders(parser->cur_header_field,
                                    std::string(buf, len));
//  LOG(TRACE) << "header value: " << std::string(buf, len);
  return 0;
}

int headers_complete_cb(http_parser* p)
{
//  LOG(TRACE) << "header finish";
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);
  http_parser_pause(p, true);
//  messages[num_messages].should_keep_alive = http_should_keep_alive(parser);
  return 0;
}

void check_body_is_final(const http_parser* p)
{
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);

  int is_final = http_body_is_final(p);
  parser->set_body_final(true);
//  LOG(TRACE) << "body is final" << is_final;
}

int body_cb(http_parser* p, const char* buf, size_t len)
{
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);
  HttpResponseInfo* response_info = parser->response_info();
  response_info->body->Buffer(const_cast<char*>(buf), len);
//  LOG(TRACE) << "body read: " << std::string(buf, len);
  check_body_is_final(p);
  return 0;
}



int message_complete_cb(http_parser* p)
{
  HttpResponseParser* parser = static_cast<HttpResponseParser*>(p->data);
//  LOG(TRACE) << "message finish";
  return 0;
}


http_parser_settings settings = { message_begin_cb, nullptr,
                                  response_status_cb, header_field_cb,
                                  header_value_cb, headers_complete_cb,
                                  body_cb, message_complete_cb,
                                  nullptr, nullptr };

void HttpResponseParser::ParseHeaders() {
  state_ = kParseHeader;
  http_parser parser;
  parser.data = this;
  http_parser_init(&parser, HTTP_RESPONSE);
  auto& buffer = response_info_->buffer;
  std::string_view real_buffer;
  buffer.ReadRemainAll(&real_buffer);
  size_t parsed = http_parser_execute(&parser, &settings,
                                      real_buffer.data(), real_buffer.size());
  LOG(TRACE) << "Response parse size: " << parsed;
  if (parsed != real_buffer.size()) {
    buffer.SetPosition(parsed+1);
    std::string_view remain_buffer;
    buffer.ReadRemainAll(&remain_buffer);
    response_info_->body->Buffer(const_cast<char*>(remain_buffer.data()),
                                 remain_buffer.size());
    LOG(TRACE) << "Response Remain data: \n" << remain_buffer.data();
  }
}

void HttpResponseParser::ParseBody() {
  state_ = kParseBody;
  http_parser parser;
  parser.data = this;
  http_parser_init(&parser, HTTP_RESPONSE);
  auto& buffer = response_info_->buffer;
  std::string_view real_buffer;
  buffer.ReadRemainAll(&real_buffer);
  response_info_->body->Buffer(const_cast<char*>(real_buffer.data()),
                               real_buffer.size());
//  size_t parsed = http_parser_execute(&parser, &settings,
//                                      real_buffer.data(), real_buffer.size());
//
//  LOG(TRACE) << "Response parse size: " << parsed;
//  if (parsed != real_buffer.size()) {
//    buffer.SetPosition(parsed);
//    LOG(TRACE) << "Response Remain data: \n" << real_buffer.substr(parsed).data();
//  }
}

HttpResponseParser::HttpResponseParser()
    : state_(kParseNone),
      is_body_final_(false),
      response_info_(nullptr) {}

void HttpResponseParser::set_body_final(bool final) {
  is_body_final_ = final;
}

void HttpResponseParser::set_response(HttpResponseInfo* response_info) {
  response_info_ = response_info;
}

size_t HttpResponseParser::RemainSize() {

  std::string content_length_str = response_info_->headers.
      GetHeader(HttpHeaders::CONTENT_LENGTH);
  if (!content_length_str.empty()) {
    int content_length = atoi(content_length_str.data());
    int remain = content_length - response_info_->body->GetSize();
    if (remain > 0) {
      return remain;
    }
  }
  return 0;
}

}  // namespace net
}  // namespace tit