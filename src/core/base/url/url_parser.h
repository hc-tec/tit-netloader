//
// Created by titto on 2022/5/29.
//

#ifndef TIT_NETLOADER_URL_PARSER_H
#define TIT_NETLOADER_URL_PARSER_H

/*
Author:钱波
email: 418511899@qq.com
wei:   18091589062
func  :类
time:  2021年6月9日
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <string>
#include <iostream>

namespace tit {
namespace net {

static inline int judge_equeal(const char *pos,
                               const char *compare,
                               size_t &clen);

static inline int string_find(const char *u, const char *compare);

static inline const char* string_find_pos(const char *u, const char *compare);

typedef struct UrlParam
{
  std::string protocol;
  std::string host;
  unsigned short port = 80;
  std::string uri;
  void clear()
  {
    protocol.clear();
    host.clear();
    uri.clear();
    port = 80;
  }
} TUrlParam;

class TParseUrl
{
 protected:
  static int parse_domain(const char *pos, const char *posend, TUrlParam & param);
  static bool IsNumber(const char * num);
 public:
  explicit TParseUrl(const char * url);
  virtual ~TParseUrl() {};
  TUrlParam v_param;

#define POS_JUDGE if(pos>=posend) return -1
#define POS_JUDGE_OK if(pos>=posend) return 0
  static int ParseUrl(const char *url, TUrlParam &param);

  std::string GetParam(const char *param);

  void SetUrl(const char *url);
};


}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_URL_PARSER_H

