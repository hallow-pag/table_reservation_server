/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-26 20:16:14
 * @LastEditors: yokon
 * @Description: 公共头文件及公共参数
 * @ 再码一行！！！
 */
#ifndef PUBLIC_H
#define PUBLIC_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/sysinfo.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <time.h>
#include <sstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;

#define DEFAULT_PORT_Clie 8080
#define DEFAULT_PORT_Http 9000
#define MAX_EVENT_NUM 1024
#define INFTIM -1

#define STR_LEN 20//定义随机输出的字符串长度。
#define CHAR_MIN 'a'
#define CHAR_MAX 'z' //定义输出随机字符串每个字符的最大最小值。

void gettime(char* time); //获取时间 带格式  %02d-%02d-%02d %02d:%02d:%02d
string gettime();           //获取时间 无格式     
int chartoint(char *str);
char* strtochar(std::string str, char *an);
int strtoint(std::string str);  
bool searchStr(const char *pSource,const char *pSearch);
void logtotest(string);  //打印日志
void to_hex( char* buff, int buff_len);//16进制打印

bool writefile(string file,string &date);
bool writefile(string file,char * date,int len);

/*=============Err===================*/
const int ok = 1; //OK!!
const int err_row =-1; //路径错误
const int err_onfand = -2; //没有找到相关数据
const int err_double = -3;// 重复
const int err_nametoshort = -4; //参数不规范
const int err_noparam = -5;
/*=============Err===================*/

const string urle = "http://hunya.fun:8080";

//数据类型
const int UPDATE_DATA = 0x01;  //信息更新
const int CHANGE_DATA = 0x02;  //信息更改
const int DEL_DATA    = 0x03;  //信息删除 

const int GET_DATA    = 0x04;  //信息获取

//处理单元
const int UNIT_SHOP_INF = 0x1001; // 店铺信息数据单元(上传更改)
const int UNIT_SHOP_INS = 0x1002; // 店铺信息数据单元（获取）

const int REPONSE_CLIE = 0x5001; // 客户端接收响应状态 1/OK -1/err


const int SHOP_TYPE_BREAKFIRST = 1; //早餐
const int SHOP_TYPE_LUNCH = 2;//午餐
const int SHOP_TYPE_EVET = 3;//晚餐
const int SHOP_TYPE_LUNCH_EVET = 4;//午餐-晚餐
const int SHOP_TYPE_BREAKFIRSH_LUNCH = 5;//早餐-午餐
const int SHOP_TYPE_ALL = 6;//三餐


const int FDS_TYPE_CH = 1;//中餐
const int FDS_TYPE_JP = 2;//日餐
const int FDS_TYPE_USA = 3;//美餐


//网络头
 
struct Nethead{
    int  bonil;       //设备在线状态
    unsigned int iSrcCommID;     //数据类型
    unsigned int iUnitID;       //处理单元
    unsigned int ilenth;       //数据长度
    unsigned int ishopid;       //店铺ID号（必填）
    unsigned int iChick;       //参数校验
    unsigned int iBl;
    char      lParam[10880];         //数据

    Nethead(){
        bonil = -1;
        iSrcCommID = 0;
        iUnitID = 0;
        ilenth = 0;
        iChick =0;
        iBl = 0;
    }
};

 
struct Photo{
unsigned int upLen; //照片长度
char photo[10240]; // 店铺图片
};

//店铺信息
struct structshopinf
{
    string ShopName;
    string ip;
    string IsLogin;
    string photopath;
    string text;
    string addr;
    string PhoneNumber;
    string shoper;
    string shoptyp;
    string fdstype;
};

//菜单
struct mymenu
{
    string id;
    string sid;
    string name;
    string hot;
    string minet;
    string money;
    string lenth;
    string filepath;
    string imgtype;
    string photo;
    string type;
    string eattype;
};



#endif
