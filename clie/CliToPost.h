/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:14:43
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */
#ifndef TOPOST_H
#define TOPOST_H
#include "../public.h"
#include "Sqlmanagetocli.h"
#include <jsoncpp/json/json.h>
#include <map>
using std::map;
class CliToPost{
    

public:
    CliToPost();
    ~CliToPost();
    void managementPOST(char url[]); //POST 函数
    void init(string  &other,string addr,int link, map<string,string> map);

private:
    int getunit(char *data,int &flg); //获取店铺ID 


private:
    Sqlmanagetocli *sqlcli;  
    int unit;
    structshopinf shopinf;

    string othre;
    map<string,string> mapcli;
    string ipaddr;
    int LinkNumber;

    
};


#endif
