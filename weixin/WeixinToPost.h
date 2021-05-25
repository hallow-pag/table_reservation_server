/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:14:43
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */
#ifndef WeixinTOPOST_H
#define WeixinTOPOST_H
#include "../public.h"
#include "SqlManage.h"
#include <jsoncpp/json/json.h>
#include <map>
using std::map;
class WeixinToPost{
    

public:
    WeixinToPost();
    ~WeixinToPost();
    void managementPOST(char url[]); //POST 函数
    void init(char *other,string addr,int link, map<string,string> map);

private:
    int getunit(char *data,int &flg); //获取店铺ID 


private:
    SqlManage *sqlcli;  
    int unit;
    structshopinf shopinf;

    string othre;
    map<string,string> mapinf;
    string ipaddr;
    int LinkNumber;

    
};


#endif
