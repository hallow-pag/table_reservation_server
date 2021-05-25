/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-28 15:38:16
 * @LastEditors: yokon
 * @Description: 小程序数据处理
 * @ 再码一行！！！
 */
#ifndef PROCESSDATAWX_H
#define PROCESSDATAWX_H

#include "../public.h"
#include "WeixinToPost.h"
#include "WeixinToget.h"
#include "SqlManage.h"
//#include <map>

class ProcessDataWx {
private:
  /* data */
public:
  ProcessDataWx(/* args */);
  ~ProcessDataWx();
  void accept_request();
  void responses_init(int fd, char *addr);

private:
  int get_line(int sock, char *buf, int size);
  void getCookie(char *buf);
  void randCookie(char *strss);
  
  void screen(char *Request, int len);//获取参数
  void getparam(string& json);//获取POST参数 不使用jsoncpp
  //void managementGet(char *Url);  
  //void managementPOST( char *Url);

 // int client;  //link number

private:
  int LinkNumber;  // sock连接号
  char cookie[22]; // cookie
  char ipaddr[16];
  char userid[5];
  size_t numchars;  // 打开文件 文件号
  char othre[8000]; //恶意路由
  std::map<std::string, std::string> mapinf;  //参数
  //SqlManage *sql;

  bool islogin; //是否登陆
  WeixinToPost * Weixinpost;
  WeixinToGet * Weixinget;
};

#endif
