/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:14:43
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */
#ifndef WeixinTOGET_H
#define WeixinTOGET_H
#include "../public.h"
#include "SqlManage.h"
#include <map>
using std::map;
class WeixinToGet{
    

public:
    WeixinToGet();
    ~WeixinToGet();
    void managementGET(char url[]); //GET 函数
    void init(char *other,string addr,int link, map<string,string> map);

private:
    int getunit(char *data,int &flg); //获取店铺ID 
    


private:
    SqlManage *sqlcli;  
    int unit;
    structshopinf shopinf;

    string othre;
    map<string,string> mapcli;
    string ipaddr;
    int LinkNumber;

    
};


#endif
