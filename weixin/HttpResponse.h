/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-26 20:25:03
 * @LastEditors: yokon
 * @Description: 小程序使用的入口
 * @ 再码一行！！！
 */
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H
#include"../public.h"
#include"ProcessDataWx.h"
class HttpResponse {

public:
  HttpResponse(int FD);
  ~HttpResponse();


  void process();
  int getfd();

int listen_fd;


private:
  ProcessDataWx *WixoutIn;

};

#endif