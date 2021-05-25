/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:14:43
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */
#ifndef TOGET_H
#define TOGET_H
#include "../public.h"
#include "Sqlmanagetocli.h"
#include <map>
using std::map;
class CliToGet{
    

public:
    CliToGet();
    ~CliToGet();
    void managementGET(char url[]); //GET 函数
    void init(string addr,int link, map<string,string> map);

private:
    int getunit(char *data,int &flg); //获取店铺ID 
    


private:
    Sqlmanagetocli *sqlcli;  
    int unit;
    structshopinf shopinf;
    map<string,string> mapcli;
    string ipaddr;
    int LinkNumber;

    
};


#endif
