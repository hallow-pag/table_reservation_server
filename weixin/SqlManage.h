#ifndef SQLMANAGE_H
#define SQLMANAGE_H

#include<sqlite3.h>
#include<iostream>
#include<string.h>
#include"../public.h"

class SqlManage
{
private:
    /* data */
    sqlite3 * db=NULL;
    char *zErrMsg =NULL;
    int rc;
    

public:
    SqlManage(/* args */);
    ~SqlManage();

void shopinf(char* shopinfs,int flg);  //店铺信息 number 页数
void loginf(char * shopinfs, char * userkey, int flg);
void getMenu(int page, char* getinfs, int flg);
void ShopMenu(char * sid, char * shopinfs, int flg); //用户传入某店铺编号（sid）查找 返回该店铺的菜品
void shopchoose(char * Menuid, char * shopinfs, int flg);//用户传入菜品id 返回菜品及价格
void Userchoose(char * Menuid, char * shopinfs, int flg);//用户传入用户id返回总价
void getbreakfast(char * sid, char * shopinfs, int flg);//用户传入店铺id返回该店铺的所有早餐品类
void getbreakfastshop(char * shopinfs, int flg);//返回所有早餐店铺
void getAllbreakfast(char * shopinfs, int flg);//返回所有早餐品类
void getLunch(char * sid, char * shopinfs, int flg);//用户传入店铺id返回该店铺的所有午餐品类
void getLunchshop(char * shopinfs, int flg);//返回所有午餐店铺
void getAllLunch(char * shopinfs, int flg);//返回所有午餐品类
void getdinner(char * sid, char * shopinfs, int flg);//用户传入店铺id返回该店铺的所有晚餐品类
void getdinnershop(char * shopinfs, int flg);//返回所有晚餐店铺
void getAlldinner(char * shopinfs, int flg);//返回所有晚餐品类
bool getorder(char * sid, char * uid, char * value, char * money, char * shopinfs, int flg,char *status);
void mylist(char *data,int &flg,int unit);//我的订单是否完成
 
bool getorder(char * sid, char * uid, char * value, char * money, char * shopinfs, int flg);
void GETsqlAdd(char *sqlset_inf,string sqladdrs);//日志存储
void POSTsqlAdd(char *sqlset_inf,string sqladdrs);//日志存储
void Usermessage(char * uid, char * stuID, char * name, char * addrs, char * shopinfs, int flg);//用户个人信息上传修改
void checkmessage(char * uid, char * shopinfs, int flg);//用户查看个人信息

};



#endif