#ifndef SQLMANAGETOCLI_H
#define SQLMANAGETOCLI_H

#include<sqlite3.h>
#include<iostream>
#include<string.h>
#include<fstream>
#include"../public.h"

class Sqlmanagetocli
{
private:
    /* data */
    sqlite3 * db=NULL;
    char *zErrMsg =NULL;
    int rc;
    
    

public:
    Sqlmanagetocli(/* args */);

    ~Sqlmanagetocli();

//bool updatashopinf(char *sqlstr);  //更改店铺信息
int getdatashopinf(char *data,int &flg,int unit);    //获取店铺信息
int getmenu(char *data,int &flg,int unit);//获取菜品信息
int upclishopinf(structshopinf &shopinf,char *data,int &flg,int unit);// 获取原始数据
int upclishopinfsave(structshopinf &shopinf,char *data,int &flg,int unit);  //Updata to SQL

//===============================================================//
int addmenu(mymenu &menu,char *data,int &flg); //添加菜品
int upmenusave(mymenu &menu,char *data,int &flg,int unit);//更新菜品 Updata to SQL
int delmenu(char *data,int &flg,int unit);//删除菜品
int upmenu(mymenu &menu,char *data,int &flg,string it);// 获取原始数据

int havemenu(char *data,int &flg,int unit,const char* id);  //是否有新的订单


void okmenu(char *data,int &flg,int menuid); //菜品完成



//大屏显示状态
void list(char *data,int &flg);//   

void GETsqlAdd(char *sqlset_inf,string sqladdrs);//日志存储
void POSTsqlAdd(char *sqlset_inf,string sqladdrs);//日志存储



 
 
};



#endif


//1010 1010