#include"Sqlmanagetocli.h"
#include"../sitting.hpp"

/*************************************************
Function: // 函数名称
Description: // 函数功能、性能等的描述
Calls: // 被本函数调用的函数清单
Called By: // 调用本函数的函数清单
Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
Table Updated: // 被修改的表（此项仅对于牵扯到数据库操作的程序）
Input: // 输入参数说明，包括每个参数的作
// 用、取值说明及参数间关系。
Output: // 对输出参数的说明。
Return: // 函数返回值的说明
Others: // 其它说明
*************************************************/
Sqlmanagetocli::Sqlmanagetocli(/* args */)
{

    rc = sqlite3_open("../Date/hello.db", &db); 
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
    }
}

Sqlmanagetocli::~Sqlmanagetocli(/* args */){

}


/*===================================店铺信息==============================================*/

// /**
//  * @description: 
//  * @param {*}
//  * @return {*}
//  */
// bool Sqlmanagetocli::updatashopinf(char *sqlstr){
//     //sprintf(updatesql,"UPDATE \"main\".\"User\" SET \"username\" = '%s', \"pwd\" = '%s',\"power\" = '%s' WHERE id=%s",user,azResult[4],power,userid);
//     if(sqlite3_exec(db,sqlstr,0,0,&zErrMsg)==0){
//         logtotest("Sqlmanagetocli::updatashopinf:店铺信息根新失败");
//         return false;
//     } 

//     logtotest("Sqlmanagetocli::updatashopinf 数据根新成功！！！");
//     return true;
// }

/**
 * @description: 获取店铺信息
 * @param {*}
 * @return {char*} 
 */
int Sqlmanagetocli::getdatashopinf(char *data,int &flg ,int unit){

    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char sql[200];

        
         sprintf(sql,"select ShopName,photopath,text,addr,PhoneNumber,shoper,shoptyp,fdstype,IsLogin from UserytoShop WHERE id='%d';",unit);
        sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
if(ncolumn<=0){
            logtotest("Sqlmanagetocli::getdatashopinf:未找到相关数据");
              sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-2,"未找到相关数据"); 
            return -1;
        }
        logtotest(sql);
            flg+= sprintf(data+flg,"{\"Date\":");
            flg += sprintf(data+flg,"{\"ShopName\":\"%s\",\"photopath\":\"%s%s\",\"text\":\"%s\",\"addr\":\"%s\",\"PhoneNumber\":\"%s\",\"shoper\":\"%s\",\"shoptyp\":\"%s\",\"fdstype\":\"%s\",\"IsLogin\":\"%s\"}}"
                                ,azResult[ncolumn],urls.c_str(),azResult[ncolumn+1],azResult[ncolumn+2],azResult[ncolumn+3],azResult[ncolumn+4],azResult[ncolumn+5],azResult[ncolumn+6],azResult[ncolumn+7],azResult[ncolumn+8]);

return flg;

}


int Sqlmanagetocli::upclishopinf(structshopinf &shopinf,char *data,int &flg,int unit){
    //SELECT *,rowid "NAVICAT_ROWID" FROM "main"."UserytoShop" WHERE Id=27;
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char sql[200];

        
        sprintf(sql,"SELECT *,rowid \"NAVICAT_ROWID\" FROM \"main\".\"UserytoShop\" WHERE Id='%d';",unit);
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    if(ncolumn<=0){
        logtotest("Sqlmanagetocli::upclishopinf:未找到相关数据");
            sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return -1;
    }
    logtotest(sql);
        shopinf.ShopName = azResult[ncolumn+1];
        shopinf.ip = "";
        shopinf.IsLogin = azResult[ncolumn+3];
        shopinf.photopath = azResult[ncolumn+4];
        shopinf.text = azResult[ncolumn+5];
        shopinf.addr = azResult[ncolumn+6];
        shopinf.PhoneNumber = azResult[ncolumn+7];
        shopinf.shoper = azResult[ncolumn+8];
        shopinf.shoptyp = azResult[ncolumn+9];
        shopinf.fdstype = azResult[ncolumn+10];
return flg;
}
    /*
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
    */
int Sqlmanagetocli::upclishopinfsave(structshopinf &shopinf,char *data,int &flg,int unit){
   char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char updatesql[400];

        sprintf(updatesql,"UPDATE \"main\".\"UserytoShop\" SET \"ShopName\" = '%s', "
        "\"ip\" = '%s', \"IsLogin\" = '%s', \"photopath\" = '%s',"
         "\"text\" = '%s', \"addr\" = '%s', \"PhoneNumber\" = '%s', "
         "\"shoper\" = '%s', \"shoptyp\" = '%s', \"fdstype\" = '%s' WHERE Id = '%d';"
         ,shopinf.ShopName.c_str()
         ,shopinf.ip.c_str()
         ,shopinf.IsLogin.c_str()
         ,shopinf.photopath.c_str()
         ,shopinf.text.c_str()
         ,shopinf.addr.c_str()
         ,shopinf.PhoneNumber.c_str()
         ,shopinf.shoper.c_str()
         ,shopinf.shoptyp.c_str()
         ,shopinf.fdstype.c_str()
         ,unit);
    if(sqlite3_exec(db,updatesql,0,0,&zErrMsg)==0){
        logtotest(updatesql);
        sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",ok,"成功！"); 
        return flg;
    }

    logtotest("Sqlmanagetocli::upclishopinf:未找到相关数据");
        sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
    return -1;
}
/*===================================店铺信息==============================================*/



/*=======================================菜单====================================*/

int Sqlmanagetocli::addmenu(mymenu &menu,char *data,int &flg) //添加菜品
{
    if(menu.name.length()>10||menu.name.length()<1){
       logtotest("Sqlmanagetocli::getdatashopinf:名字重复");
              sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"名字不规范"); 
        return -1;
    }
    char sql[200];
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    sprintf(sql,"select id from AllMenu where name = '%s'",menu.name.c_str());
    sqlite3_get_table( db , sql, &azResult , &nrow , &ncolumn , &zErrMsg );
        if(nrow!=0){
            logtotest("Sqlmanagetocli::getdatashopinf:名字重复 "+menu.name);
              sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_double,"名字重复"); 
        return -1;
    }
        //INSERT INTO "main"."AllMenu"("sid", "name", "hot", "minet", "money", "photo") VALUES (27, '蜈蚣汤', 1000, 12, 21, 'Date/src/_27/2.png')
sprintf(sql,"INSERT INTO \"main\".\"AllMenu\"(\"sid\", \"name\", \"hot\", \"minet\", \"money\",\"photo\", \"type\",\"eattype\")"
            " VALUES (%s, '%s', '%s', '%s', '%s','%s','%s','%s')"
            ,menu.sid.c_str()
            ,menu.name.c_str()
            ,menu.hot.c_str()
            ,menu.minet.c_str()
            ,menu.money.c_str()
            ,menu.filepath.c_str()
            ,menu.type.c_str()
            ,menu.eattype.c_str()
            );
            logtotest(sql);
    if(0 == sqlite3_exec(db,sql,NULL,NULL,&zErrMsg)){

logtotest("Sqlmanagetocli::getdatashopinf:名字重复");
              sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",ok,"OK!!"); 
        return 1;
    }


sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_row,"err"); 
        return -1;

}

int Sqlmanagetocli::upmenu(mymenu &menu,char *data,int &flg,string it){
    //SELECT *,rowid "NAVICAT_ROWID" FROM "main"."UserytoShop" WHERE Id=27;
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char sql[200];

        
        sprintf(sql,"SELECT *,rowid \"NAVICAT_ROWID\" FROM \"main\".\"AllMenu\" WHERE id='%s';",it.c_str());
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    if(ncolumn<=0){
        logtotest("Sqlmanagetocli::upclishopinf:未找到相关数据");
            sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return -1;
    }
    logtotest(sql);
        menu.sid = azResult[ncolumn+1];
        menu.name = azResult[ncolumn+2];
        menu.hot = azResult[ncolumn+3];
        menu.minet = azResult[ncolumn+4];
        menu.money = azResult[ncolumn+5];
        menu.filepath =azResult[ncolumn+6];
return flg;
}


int Sqlmanagetocli::upmenusave(mymenu &menu,char *data,int &flg,int unit)//更新菜品
{
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char updatesql[400];
//UPDATE "main"."AllMenu" SET "name" = '蜈蚣汤Puls', "hot" = 1001, "minet" = 13, "money" = 23, "photo" = 'Date/src/_27/3.png' WHERE rowid = 3
        sprintf(updatesql,"UPDATE \"main\".\"AllMenu\" SET \"sid\" = '%s', \"name\" = '%s', "
        "\"hot\" = '%s', \"minet\" = '%s', \"money\" = '%s', \"photo\" = '%s', \"type\" = '%s',"
         "\"eattype\" = '%s' WHERE id = '%d';"
         ,menu.sid.c_str()
        ,menu.name.c_str()
        ,menu.hot.c_str()
        ,menu.minet.c_str()
        ,menu.money.c_str()
        ,menu.filepath.c_str()
        ,menu.type.c_str()
        ,menu.eattype.c_str()
        ,unit);
    if(sqlite3_exec(db,updatesql,0,0,&zErrMsg)==0){
        logtotest(updatesql);
        sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",ok,"成功！"); 
        return flg;
    }

    logtotest("Sqlmanagetocli::upclishopinf:未找到相关数据");
        sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
    return -1;

}

int Sqlmanagetocli::delmenu(char *data,int &flg,int unit)//删除菜品
{
 return 1;
}

int Sqlmanagetocli::getmenu(char *data,int &flg,int unit){//获取菜品
 char **azResult=NULL; //二维数组存放结果
    int nrow=0,i;
    int ncolumn = 0;
    char sql[200];
    flg+= sprintf(data+flg,"{\"Date\":[");
         sprintf(sql,"select id,name,hot,money,photo,type,eattype from AllMenu WHERE sid='%d';",unit);
        sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    if(ncolumn<=0){
        logtotest("Sqlmanagetocli::getdatashopinf:未找到相关数据");
            sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}]}",err_noparam,"未找到相关数据"); 
        return -1;
        }
        for(i = ncolumn;i<(nrow*ncolumn);i+=ncolumn){        
            flg += sprintf(data+flg,"{\"id\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"type\":\"%s\",\"eattype\":\"%s\"},"
                                    ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],urls.c_str(),azResult[i+4],azResult[i+5],azResult[i+6]);

        }
            flg += sprintf(data+flg,"{\"id\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"type\":\"%s\",\"eattype\":\"%s\"}]}"
                                ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],urls.c_str(),azResult[i+4],azResult[i+5],azResult[i+6]);
       
return flg;
}
/*==========================================菜单============================================*/


int Sqlmanagetocli::havemenu(char *data,int &flg,int unit,const char* id)  //是否有新的订单
{
    //SELECT id,shopid,uid,value,ischick,mony,time rowid FROM menu_27;
    char **azResult=NULL; //二维数组存放结果
    int nrow=0,i;
    int ncolumn = 0;
    char sql[200];
    flg+= sprintf(data+flg,"{\"Date\":");
         sprintf(sql,"SELECT id,shopid,uid,value,ischick,mony,time FROM menulist where ischick=11 and id>%s and shopid=%d LIMIT 1;",id,unit);
        sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    if(ncolumn<=0){
            sprintf(data+flg,"0}"); 
        return 1;
        }
        i = ncolumn;
        flg += sprintf(data+flg,"1,\"dt\":{\"id\":\"%s\",\"shopid\":\"%s\",\"uid\":\"%s\",\"value\":\"%s\",\"ischick\":\"%s\",\"mony\":\"%s\",\"time\":\"%s\",\"Menu\":["
                                ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],azResult[i+4],azResult[i+5],azResult[i+6]);
memset(sql,0,sizeof(sql));
//UPDATE "main"."menulist" SET "ischick" = 21 WHERE id = 33
       // sprintf(sql,"DELETE FROM menulist WHERE id = %s",azResult[i]);  ///清处该记录
    //    sprintf(sql,"UPDATE menulist SET ischick = 22 WHERE id = %s",azResult[i]);
    //     sqlite3_exec( db , sql  ,NULL  ,NULL ,&zErrMsg );


memset(sql,0,sizeof(sql));
        //select id,sid,name,hot,minet,money,photo,type,eattype from AllMenu where id in (2,3,4);
sprintf(sql,"select id,name,hot,money,photo,type,eattype from AllMenu where id in (%s);",azResult[i+3]);
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    if(ncolumn<=0){
            sprintf(data+flg,"}]}"); 
        return 1;
        }

        for(i = ncolumn;i<(nrow*ncolumn);i+=ncolumn){        
            flg += sprintf(data+flg,"{\"id\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"type\":\"%s\",\"eattype\":\"%s\"},"
                                    ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],urls.c_str(),azResult[i+4],azResult[i+5],azResult[i+6]);

        }
            flg += sprintf(data+flg,"{\"id\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"type\":\"%s\",\"eattype\":\"%s\"}]}}"
                                ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],urls.c_str(),azResult[i+4],azResult[i+5],azResult[i+6]);

        
return flg;

}


/*==========================================菜单============================================*/
void Sqlmanagetocli::okmenu(char *data,int &flg,int menuid) //菜品完成
{
    char sql[200];
    sprintf(sql,"UPDATE menulist SET ischick = 33 WHERE id = %d",menuid);
        sqlite3_exec( db , sql  ,NULL  ,NULL ,&zErrMsg );

}

void Sqlmanagetocli::list(char *data,int &flg){
    flg+= sprintf(data+flg,"{\"Date\":[");
 char **azResult=NULL; //二维数组存放结果
    int nrow=0,i;
    int ncolumn = 0;
    const char *sql = "select ischick,time,datime,status from menulist;";
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );

        if(ncolumn<=0){
        logtotest("Sqlmanagetocli::getdatashopinf:未找到相关数据");
            sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}]}",err_noparam,"未找到相关数据"); 
        return ;
        }
        for(i = ncolumn;i<(nrow*ncolumn);i+=ncolumn){        
            flg += sprintf(data+flg,"{\"ischick\":\"%s\",\"time\":\"%s\",\"number\":\"%s\",\"status\":\"%s\"},"
                                    ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3]);

        }
            flg += sprintf(data+flg,"{\"ischick\":\"%s\",\"time\":\"%s\",\"number\":\"%s\",\"status\":\"%s\"}]}"
                                ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3]);
       
return;
}

//--------------------------------日志存储---------------------------------//
void Sqlmanagetocli::GETsqlAdd(char *sqlset_inf,string sqladdrs)
{
  char sqltime[30];
    gettime(sqltime);
  char * rt = sqlite3_mprintf("INSERT INTO logcli VALUES(NULL,'%s','%s','%s','%s')","GET",sqladdrs.c_str(),sqladdrs.c_str(),time);
  sqlite3_exec( db , rt  ,NULL  ,NULL ,&zErrMsg );
  sqlite3_free(rt);
}
void Sqlmanagetocli::POSTsqlAdd(char *sqlset_inf,string sqladdrs)
{
  char sqltime[30];
    gettime(sqltime);
  char * rt = sqlite3_mprintf("INSERT INTO logcli VALUES(NULL,'%s','%s','%s','%s')","POST",sqladdrs.c_str(),sqladdrs.c_str(),time);
  sqlite3_exec( db , rt  ,NULL  ,NULL ,&zErrMsg );
  sqlite3_free(rt);
}
