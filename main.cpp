/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-14 13:00:45
 * @LastEditors: yokon
 * @Description:
 * @ 再码一行！！！
 */

#include "clie/ClieResponse.h"
#include "weixin/HttpResponse.h"
#include "SockInit.h"
#include "public.h"

int main(int argc, char *argv[]) {
  int sock_link_http, sock_link_clie;
  SockInit sock;
  sock_link_http = sock.toinit(DEFAULT_PORT_Clie);
  sock_link_clie = sock.toinit(DEFAULT_PORT_Http);

  ClieResponse Clie(sock_link_clie);
  HttpResponse Http(sock_link_http);

  /*** 创建小程序连接线程 ***/
  std::thread threadhttp([&Http]() { Http.process(); });
  sleep(1);
  /*** 创建客户端连接线程 ***/
  std::thread threadclie([&Clie]() { Clie.process(); });

  threadhttp.join();
  threadclie.join();

  while (1) {
    sleep(10);
  }

  return 0;
}
