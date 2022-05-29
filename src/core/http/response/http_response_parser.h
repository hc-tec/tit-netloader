//
// Created by titto on 2022/5/29.
//

#ifndef TIT_NETLOADER_HTTP_RESPONSE_PARSER_H
#define TIT_NETLOADER_HTTP_RESPONSE_PARSER_H

#include <string>

namespace tit {
namespace net {

struct HttpResponseInfo;

class HttpResponseParser {
 public:

  enum State {
    kParseNone,
    kParseHeader,
    kParseBody
  };

  HttpResponseParser();

  void set_response(HttpResponseInfo* response_info);

  void ParseHeaders();

  void ParseBody();

  State state() { return state_; }

  void set_body_final(bool final);
  bool is_body_final() { return is_body_final_; }

  HttpResponseInfo* response_info() { return response_info_; }

  size_t RemainSize();

 private:
  State state_;
  bool is_body_final_;
  HttpResponseInfo* response_info_;

 public:
  std::string cur_header_field;
};

}  // namespace net
}  // namespace tit


#endif  // TIT_NETLOADER_HTTP_RESPONSE_PARSER_H
