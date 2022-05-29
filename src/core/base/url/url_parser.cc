//
// Created by titto on 2022/5/29.
//

#include "url_parser.h"

namespace tit {
namespace net {

inline int judge_equeal(const char *pos, const char *compare, size_t &clen) {
  for (size_t i = 0; i < clen; i++) {
    if (pos[i] != compare[i]) return -1;
  }
  return 0;
}

inline int string_find(const char *u, const char *compare) {
  size_t clen = strlen(compare);
  size_t ulen = strlen(u);
  if (clen > ulen) return -1;
  const char *pos = u;
  const char *posend = u + ulen - 1;
  for (; pos <= posend - clen; pos++) {
    if (judge_equeal(pos, compare, clen) == 0) {
      return (int)(pos - u);
      // return 0;
    }
  }
  return -1;
}

inline const char *string_find_pos(const char *u, const char *compare) {
  size_t clen = strlen(compare);
  size_t ulen = strlen(u);
  if (clen > ulen) return NULL;
  const char *pos = u;
  const char *posend = u + ulen - 1;
  for (; pos <= posend - clen; pos++) {
    if (judge_equeal(pos, compare, clen) == 0) {
      return pos;
      // return 0;
    }
  }
  return NULL;
}

int TParseUrl::parse_domain(const char *pos, const char *posend,
                            TUrlParam &param) {
  int point = string_find(pos, ":");
  if (point >= 0) {
    param.host = std::string(pos, point);
    pos += point + 1;
    std::string tmp = std::string(pos, posend - pos);
    if (IsNumber(tmp.c_str())) param.port = atoi(tmp.c_str());
    return 0;
  }
  return -1;
}

int TParseUrl::ParseUrl(const char *url, TUrlParam &param)
{
  //memset(&param, 0, sizeof(param));
  const char * posend = url + strlen(url) - 1;
  param.uri = url;
  const char * pos = url;
  int point = 0;
  if ((point = string_find(pos, "://")) >= 0)
  {
    param.protocol = std::string(url, point);
  }
  else
    return -1;
  pos += point + 3; //strlen("://")
  POS_JUDGE;
  if ((point = string_find(pos, "/")) >= 0)
  {
    param.host = std::string(pos, point);
    const char *end = pos + point;
    parse_domain(pos, end, param);
    param.uri = std::string(pos + point + 1);
  }
  else
  {
    //the left all is domain
    int hlen = (int)(posend - pos + 1);
    param.host = std::string(pos,hlen);
    const char *end = pos + hlen - 1;
    parse_domain(pos, end, param);
    param.uri = "/";
    return 0;
  }



  return 0;
}
bool TParseUrl::IsNumber(const char *num) {
  int length = (int)strlen(num);
  for (int i = 0; i < length; i++)
  {
    if (i == 0 && (num[i] == '+' || num[i] == '-'))
    {
      if (length > 1)
        continue;
      return false;
    }
    if (!isdigit(num[i]))
      return false;
  }
  return true;
}

TParseUrl::TParseUrl(const char *url) {
  ParseUrl(url, v_param);
}

std::string TParseUrl::GetParam(const char *param) {
  int point = -1;
  const char *ustart = v_param.uri.c_str();

  const char * start = string_find_pos(ustart, "?");
  if (start != NULL)
  {
    ++start;
    //?a=abc&b=ddd
    std::string par = param;
    par +="=";
    start = string_find_pos(start, par.c_str());
    if (start != NULL )
    {
      const char * j = start - 1;
      char c = *j;
      if (c == '&' || c == '?')
      {
        start += par.length();
        const char * end = string_find_pos(start, "&");
        if (end != NULL)
        {
          return std::string(start, end);
        }
        return std::string(start);
      }
    }
  }
  return "";
}

void TParseUrl::SetUrl(const char *url) {
  v_param.clear();
  ParseUrl(url, v_param);
}

}  // namespace net
}  // namespace tit