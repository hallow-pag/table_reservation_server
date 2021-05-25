/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-28 15:38:16
 * @LastEditors: yokon
 * @Description: 小程序数据处理
 * @ 再码一行！！！
 */
#ifndef ProcessDataCli_H
#define ProcessDataCli_H

#include "../public.h"
#include "Sqlmanagetocli.h"
#include"CliToGet.h"
#include"CliToPost.h"

class ProcessDataCli {
private:
  /* data */
public:
  ProcessDataCli(/* args */);
  ~ProcessDataCli();
  void accept_request();
  void responses_init(int fd, char *addr);

private:
  int get_line(int sock, char *buf, int size);
  void getCookie(char *buf);
  void randCookie(char *strss);
  
  void screen(char Request[], int len);//获取GET参数
  void screenpost(char Request[], int len);//获取POST参数
  void getparam(string& json);//获取POST参数 不使用jsoncpp
//  void managementGet(char *Url);  
 // void managementPOST( char *Url);

  int getunit(char *data,int &flg);  //获取单元号

 // int client;  //link number

private:
  int LinkNumber;  // sock连接号
  char cookie[22]; // cookie
  char ipaddr[16];
  char userid[5];
  size_t numchars;  // 打开文件 文件号
 char othre[200000]; //恶意路由
  
string othersp;//恶意路由

  //std::map<std::string, std::string> mapcli;  //参数
  map<string,string> mapcli;
  bool islogin; //是否登陆
  structshopinf shopinf;//商家全部信息

  CliToPost * post;
  CliToGet * get;



};

#endif
