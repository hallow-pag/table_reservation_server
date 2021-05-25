/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-26 20:25:03
 * @LastEditors: yokon
 * @Description: 小程序使用的入口
 * @ 再码一行！！！
 */
#ifndef ClieResponse_H
#define ClieResponse_H
#include"../public.h"
#include"ProcessDataCli.h"
class ClieResponse {

public:
  ClieResponse(int FD);
  ~ClieResponse();


  void process();
  int getfd();

int listen_fd;


private:
  ProcessDataCli *Clie;

};

#endif