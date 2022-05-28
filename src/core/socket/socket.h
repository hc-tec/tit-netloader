//
// Created by titto on 2022/5/28.
//

#ifndef TIT_NETLOADER_SOCKET_H
#define TIT_NETLOADER_SOCKET_H

namespace tit {
namespace net {

class Socket {
 public:
  Socket();
  virtual ~Socket();

  virtual int Read(char* buf, int buf_len) = 0;

  virtual int ReadFix(char* buf, int buf_len) = 0;

  virtual int Write(char* buf, int buf_len) = 0;

};

}  // namespace net
}  // namespace tit

#endif  // TIT_NETLOADER_SOCKET_H
