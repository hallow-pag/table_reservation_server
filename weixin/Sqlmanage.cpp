#include"SqlManage.h"
#include"../sitting.hpp"
using std::cout;
using std::endl;


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
SqlManage::SqlManage(/* args */)
{

    rc = sqlite3_open("../Date/hello.db", &db); 
    if(rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); 
        sqlite3_close(db); 
    }
}

/*************************************************
Function: // 析构函数   关闭数据库
*************************************************/
SqlManage::~SqlManage()
{
    sqlite3_close(db); 
    std::cout<<"Colse SQL OK "<<std::endl;
    std::cout<<"~SqlManage.h to BUILD"<<std::endl;

}


/*************************************************
Function: // login
Description: // 查询所有店铺信息
Input: // 用户名;密码;
Output: // 1(登陆成功),-1(未找到用户),0(密码错误);
*************************************************/
void SqlManage::shopinf(char* shopinfs, int flg){
    
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char sql[200];
    sprintf(sql,"select id, ShopName,IsLogin,photopath,text,addr,PhoneNumber,shoper,shoptyp,fdstype from UserytoShop;");
    sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    if(ncolumn<=0){
        logtotest("SqlManage::shopinf:未找到相关数据");
            sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg+= sprintf(shopinfs+flg,"{\"Date\":[");
    int i;
    for(i = ncolumn;i<(nrow*ncolumn);i+=ncolumn){        
        flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"ShopName\":\"%s\",\"IsLogin\":\"%s\",\"photopath\":\"%s%s\",\"text\":\"%s\",\"addr\":\"%s\",\"PhoneNumber\":\"%s\",\"shoper\":\"%s\",\"shoptyp\":\"%s\",\"fdstype\":\"%s\"},"
                                ,azResult[i],azResult[i+1],azResult[i+2],urls.c_str(),azResult[i+3],azResult[i+4],azResult[i+5],azResult[i+6],azResult[i+7],azResult[i+8],azResult[i+9]);
    }
    flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"ShopName\":\"%s\",\"IsLogin\":\"%s\",\"photopath\":\"%s%s\",\"text\":\"%s\",\"addr\":\"%s\",\"PhoneNumber\":\"%s\",\"shoper\":\"%s\",\"shoptyp\":\"%s\",\"fdstype\":\"%s\"}]}"
                        ,azResult[i],azResult[i+1],azResult[i+2],urls.c_str(),azResult[i+3],azResult[i+4],azResult[i+5],azResult[i+6],azResult[i+7],azResult[i+8],azResult[i+9]);
    return ;
}

void SqlManage::loginf(char * shopinfs, char *  userkey, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;
    int ncolumn = 0;
    char sql[200];
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
        sprintf(sql,"select id,key from User_men;");
        sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
        int i, j;
        for(i = 0;i < (nrow + 1)*ncolumn; i += ncolumn){
            for(j = 0; j < ncolumn; j++){
                if(strcmp(azResult[i + j], userkey) == 0){
                    flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"key\":\"%s\"}]}",azResult[i+j-1], azResult[i+j]);
                    return ;
                }
		    }
        }
        char * rt = sqlite3_mprintf("INSERT INTO User_men VALUES(NULL,'%s')",userkey);
        sqlite3_exec(db, rt, 0, 0, &zErrMsg);
        sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
        flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"key\":\"%s\"}]}",azResult[(nrow * ncolumn)], userkey);
        sqlite3_free(rt);
        return ;
} 

/**
 * @description: 获取所有菜品菜单
 * @param {char Request[] 需要被解析的数据 ,flg}
 * @return {void }
 */
void SqlManage::getMenu(int page, char * getinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select name, sid, hot, money, photo, id from AllMenu;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getMenu:未找到相关数据");
        sprintf(getinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(getinfs + flg,"{\"Date\":[");
    int count = 0;
    int i;
    for(i = ncolumn;i<(nrow*ncolumn);i+=ncolumn){      
        if(count < ((page - 1) * 10)){
            count++;
            continue;
        }
        else{
            flg += sprintf(getinfs+flg,"{\"name\":\"%s\",\"sid\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"id\":\"%s\"},"
                                    ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],urls.c_str(),azResult[i+4],azResult[i+5]);
            count++;
            if(count == (page * 10 - 1)){
                break;
            }
        }
    }
    i = (count + 1) * ncolumn;
    flg += sprintf(getinfs+flg,"{\"name\":\"%s\",\"sid\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"id\":\"%s\"}]}"
            ,azResult[i],azResult[i+1],azResult[i+2],azResult[i+3],urls.c_str(),azResult[i+4],azResult[i+5]);
    return ;
}

void SqlManage::ShopMenu(char * sid, char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select name,sid, id, hot, minet, money, photo, type from AllMenu;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::shopMenu:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumn; i < (nrow * ncolumn); i += ncolumn){
        if(strcasecmp(azResult[i + 1], sid) == 0){
            flg += sprintf(shopinfs + flg,"{\"name\":\"%s\",\"id\":\"%s\",\"hot\":\"%s\",\"minet\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"type\":\"%s\"}"
                            ,azResult[i],azResult[i + 2],azResult[i + 3],azResult[i + 4],azResult[i + 5],urls.c_str(),azResult[i + 6],azResult[i + 7]);
            break;
        }
    }
    for(j = i + ncolumn; j < ((nrow + 1) * ncolumn); j += ncolumn){
        if(strcasecmp(azResult[j + 1], sid) == 0){
            flg += sprintf(shopinfs + flg,",{\"name\":\"%s\",\"id\":\"%s\",\"hot\":\"%s\",\"minet\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"type\":\"%s\"}"
                            ,azResult[j],azResult[j + 2],azResult[j + 3],azResult[j + 4],azResult[j + 5],urls.c_str(),azResult[j + 6],azResult[j + 7]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

void SqlManage::getbreakfast(char * sid, char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select id,ShopName,shoptyp from UserytoShop;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getbreakfast:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    char **azResultMenu=NULL; //二维数组存放结果
    int nrowMenu=0;  
    int ncolumnMenu = 0;
    char sqlMenu[200];
    sprintf(sqlMenu, "select sid, name, hot, money, photo, eattype from AllMenu;");
    sqlite3_get_table( db, sqlMenu, &azResultMenu, &nrowMenu, &ncolumnMenu, &zErrMsg);
    if(ncolumnMenu<=0){
        logtotest("SqlManage::getbreakfast:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    int n;
    bool Menu = false;
    for(n = ncolumn;n<((nrow + 1)*ncolumn);n+=ncolumn){
        if(strcasecmp(azResult[n], sid) == 0){
            Menu = true;
            if((strcasecmp(azResult[n + 2], "1") == 0 || strcasecmp(azResult[n + 2], "11") == 0 || strcasecmp(azResult[n + 2], "111") == 0 || strcasecmp(azResult[n + 2], "101") == 0)){
                flg += sprintf(shopinfs+flg,"{\"Date\":[");
                int i, j;
                for(i = ncolumnMenu; i < ((nrowMenu + 1) * ncolumnMenu); i += ncolumnMenu){
                    if(strcasecmp(azResultMenu[i], azResult[n]) == 0 && (strcasecmp(azResultMenu[i + 5], "1") == 0 || strcasecmp(azResultMenu[i + 5], "11") == 0 || strcasecmp(azResultMenu[i + 5], "111") == 0 || strcasecmp(azResultMenu[i + 5], "101") == 0)){
                        flg += sprintf(shopinfs + flg,"{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                                        ,azResultMenu[i],azResultMenu[i + 1],azResultMenu[i + 2],azResultMenu[i + 3],urls.c_str(),azResultMenu[i + 4],azResultMenu[i + 5]);
                        break;
                    }
                }
                for(j = i + ncolumnMenu; j < ((nrowMenu + 1) * ncolumnMenu); j += ncolumnMenu){
                    if(strcasecmp(azResultMenu[j], azResult[n]) == 0 && (strcasecmp(azResultMenu[j + 5], "1") == 0 || strcasecmp(azResultMenu[j + 5], "11") == 0 || strcasecmp(azResultMenu[j + 5], "111") == 0 || strcasecmp(azResultMenu[j + 5], "101") == 0)){
                        flg += sprintf(shopinfs + flg,",{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                                        ,azResultMenu[j],azResultMenu[j + 1],azResultMenu[j + 2],azResultMenu[j + 3],urls.c_str(),azResultMenu[j + 4],azResultMenu[j + 5]);
                    }
                }
                flg += sprintf(shopinfs + flg,"]}");
                return ;
            }
            else{
                sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
                return ;
            }
        }
    }
    if(Menu == false){
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
        return ;
    }
    return ;
}

void SqlManage::getbreakfastshop(char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select id,ShopName,shoptyp from UserytoShop;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getbreakfastshop:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumn;i<((nrow + 1)*ncolumn);i+=ncolumn){
        if((strcasecmp(azResult[i + 2], "1") == 0 || strcasecmp(azResult[i + 2], "11") == 0 || strcasecmp(azResult[i + 2], "111") == 0 || strcasecmp(azResult[i + 2], "101") == 0)){
            flg += sprintf(shopinfs + flg, "{\"ShopName\":\"%s\",\"sid\":\"%s\"}", azResult[i + 1], azResult[i]);
            break;
        }
    }
    for(j = i + ncolumn;j<((nrow + 1)*ncolumn);j+=ncolumn){
        if((strcasecmp(azResult[j + 2], "1") == 0 || strcasecmp(azResult[j + 2], "11") == 0 || strcasecmp(azResult[j + 2], "111") == 0 || strcasecmp(azResult[j + 2], "101") == 0)){
            flg += sprintf(shopinfs + flg, ",{\"ShopName\":\"%s\",\"sid\":\"%s\"}", azResult[j + 1], azResult[j]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

void SqlManage::getAllbreakfast(char * shopinfs, int flg){
    char **azResultMenu=NULL; //二维数组存放结果
    int nrowMenu=0;  
    int ncolumnMenu = 0;
    char sqlMenu[200];
    sprintf(sqlMenu, "select sid, name, hot, money, photo, eattype from AllMenu;");
    sqlite3_get_table( db, sqlMenu, &azResultMenu, &nrowMenu, &ncolumnMenu, &zErrMsg);
    if(ncolumnMenu<=0){
        logtotest("SqlManage::getAllbreakfast:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumnMenu; i < ((nrowMenu + 1) * ncolumnMenu); i += ncolumnMenu){
        if((strcasecmp(azResultMenu[i + 5], "1") == 0 || strcasecmp(azResultMenu[i + 5], "11") == 0 || strcasecmp(azResultMenu[i + 5], "111") == 0 || strcasecmp(azResultMenu[i + 5], "101") == 0)){
            flg += sprintf(shopinfs + flg,"{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                            ,azResultMenu[i],azResultMenu[i + 1],azResultMenu[i + 2],azResultMenu[i + 3],urls.c_str(),azResultMenu[i + 4],azResultMenu[i + 5]);
            break;
        }
    }
    for(j = i + ncolumnMenu; j < ((nrowMenu + 1) * ncolumnMenu); j += ncolumnMenu){
        if((strcasecmp(azResultMenu[j + 5], "1") == 0 || strcasecmp(azResultMenu[j + 5], "11") == 0 || strcasecmp(azResultMenu[j + 5], "111") == 0 || strcasecmp(azResultMenu[j + 5], "101") == 0)){
            flg += sprintf(shopinfs + flg,",{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                            ,azResultMenu[j],azResultMenu[j + 1],azResultMenu[j + 2],azResultMenu[j + 3],urls.c_str(),azResultMenu[j + 4],azResultMenu[j + 5]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

void SqlManage::getLunch(char * sid, char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select id,ShopName,shoptyp from UserytoShop;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getLunch:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    char **azResultMenu=NULL; //二维数组存放结果
    int nrowMenu=0;  
    int ncolumnMenu = 0;
    char sqlMenu[200];
    sprintf(sqlMenu, "select sid, name, hot, money, photo, eattype from AllMenu;");
    sqlite3_get_table( db, sqlMenu, &azResultMenu, &nrowMenu, &ncolumnMenu, &zErrMsg);
    if(ncolumnMenu<=0){
        logtotest("SqlManage::getLunch:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    int n;
    bool Menu = false;
    for(n = ncolumn;n<((nrow + 1)*ncolumn);n+=ncolumn){
        if(strcasecmp(azResult[n], sid) == 0){
            Menu = true;
            if((strcasecmp(azResult[n + 2], "10") == 0 || strcasecmp(azResult[n + 2], "11") == 0 || strcasecmp(azResult[n + 2], "111") == 0 || strcasecmp(azResult[n + 2], "110") == 0)){
                flg += sprintf(shopinfs+flg,"{\"Date\":[");
                int i, j;
                for(i = ncolumnMenu; i < ((nrowMenu + 1) * ncolumnMenu); i += ncolumnMenu){
                    if(strcasecmp(azResultMenu[i], azResult[n]) == 0 && (strcasecmp(azResultMenu[i + 5], "10") == 0 || strcasecmp(azResultMenu[i + 5], "11") == 0 || strcasecmp(azResultMenu[i + 5], "111") == 0 || strcasecmp(azResultMenu[i + 5], "110") == 0)){
                        flg += sprintf(shopinfs + flg,"{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                                        ,azResultMenu[i],azResultMenu[i + 1],azResultMenu[i + 2],azResultMenu[i + 3],urls.c_str(),azResultMenu[i + 4],azResultMenu[i + 5]);
                        break;
                    }
                }
                for(j = i + ncolumnMenu; j < ((nrowMenu + 1) * ncolumnMenu); j += ncolumnMenu){
                    if(strcasecmp(azResultMenu[j], azResult[n]) == 0 && (strcasecmp(azResultMenu[j + 5], "10") == 0 || strcasecmp(azResultMenu[j + 5], "11") == 0 || strcasecmp(azResultMenu[j + 5], "111") == 0 || strcasecmp(azResultMenu[j + 5], "110") == 0)){
                        flg += sprintf(shopinfs + flg,",{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                                        ,azResultMenu[j],azResultMenu[j + 1],azResultMenu[j + 2],azResultMenu[j + 3],urls.c_str(),azResultMenu[j + 4],azResultMenu[j + 5]);
                    }
                }
                flg += sprintf(shopinfs + flg,"]}");
                return ;
            }
            else{
                sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
                return ;
            }
        }
    }
    if(Menu == false){
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
        return ;
    }
    return ;
}

void SqlManage::getLunchshop(char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select id,ShopName,shoptyp from UserytoShop;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getLunchshop:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumn;i<((nrow + 1)*ncolumn);i+=ncolumn){
        if((strcasecmp(azResult[i + 2], "10") == 0 || strcasecmp(azResult[i + 2], "11") == 0 || strcasecmp(azResult[i + 2], "111") == 0 || strcasecmp(azResult[i + 2], "110") == 0)){
            flg += sprintf(shopinfs + flg, "{\"ShopName\":\"%s\",\"sid\":\"%s\"}", azResult[i + 1], azResult[i]);
            break;
        }
    }
    for(j = i + ncolumn;j<((nrow + 1)*ncolumn);j+=ncolumn){
        if((strcasecmp(azResult[j + 2], "10") == 0 || strcasecmp(azResult[j + 2], "11") == 0 || strcasecmp(azResult[j + 2], "111") == 0 || strcasecmp(azResult[j + 2], "110") == 0)){
            flg += sprintf(shopinfs + flg, ",{\"ShopName\":\"%s\",\"sid\":\"%s\"}", azResult[j + 1], azResult[j]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

void SqlManage::getAllLunch(char * shopinfs, int flg){
    char **azResultMenu=NULL; //二维数组存放结果
    int nrowMenu=0;  
    int ncolumnMenu = 0;
    char sqlMenu[200];
    sprintf(sqlMenu, "select sid, name, hot, money, photo, eattype from AllMenu;");
    sqlite3_get_table( db, sqlMenu, &azResultMenu, &nrowMenu, &ncolumnMenu, &zErrMsg);
    if(ncolumnMenu<=0){
        logtotest("SqlManage::getAllLunch:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumnMenu; i < ((nrowMenu + 1) * ncolumnMenu); i += ncolumnMenu){
        if((strcasecmp(azResultMenu[i + 5], "10") == 0 || strcasecmp(azResultMenu[i + 5], "11") == 0 || strcasecmp(azResultMenu[i + 5], "111") == 0 || strcasecmp(azResultMenu[i + 5], "110") == 0)){
            flg += sprintf(shopinfs + flg,"{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                            ,azResultMenu[i],azResultMenu[i + 1],azResultMenu[i + 2],azResultMenu[i + 3],urls.c_str(),azResultMenu[i + 4],azResultMenu[i + 5]);
            break;
        }
    }
    for(j = i + ncolumnMenu; j < ((nrowMenu + 1) * ncolumnMenu); j += ncolumnMenu){
        if((strcasecmp(azResultMenu[j + 5], "10") == 0 || strcasecmp(azResultMenu[j + 5], "11") == 0 || strcasecmp(azResultMenu[j + 5], "111") == 0 || strcasecmp(azResultMenu[j + 5], "110") == 0)){
            flg += sprintf(shopinfs + flg,",{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                            ,azResultMenu[j],azResultMenu[j + 1],azResultMenu[j + 2],azResultMenu[j + 3],urls.c_str(),azResultMenu[j + 4],azResultMenu[j + 5]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

void SqlManage::getdinner(char * sid, char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select id,ShopName,shoptyp from UserytoShop;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getdinner:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    char **azResultMenu=NULL; //二维数组存放结果
    int nrowMenu=0;  
    int ncolumnMenu = 0;
    char sqlMenu[200];
    sprintf(sqlMenu, "select sid, name, hot, money, photo, eattype from AllMenu;");
    sqlite3_get_table( db, sqlMenu, &azResultMenu, &nrowMenu, &ncolumnMenu, &zErrMsg);
    if(ncolumnMenu<=0){
        logtotest("SqlManage::getdinner:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    int n;
    bool Menu = false;
    for(n = ncolumn;n<((nrow + 1)*ncolumn);n+=ncolumn){
        if(strcasecmp(azResult[n], sid) == 0){
            Menu = true;
            if((strcasecmp(azResult[n + 2], "100") == 0 || strcasecmp(azResult[n + 2], "101") == 0 || strcasecmp(azResult[n + 2], "111") == 0 || strcasecmp(azResult[n + 2], "110") == 0)){
                flg += sprintf(shopinfs+flg,"{\"Date\":[");
                int i, j;
                for(i = ncolumnMenu; i < ((nrowMenu + 1) * ncolumnMenu); i += ncolumnMenu){
                    if(strcasecmp(azResultMenu[i], azResult[n]) == 0 && (strcasecmp(azResultMenu[i + 5], "100") == 0 || strcasecmp(azResultMenu[i + 5], "101") == 0 || strcasecmp(azResultMenu[i + 5], "111") == 0 || strcasecmp(azResultMenu[i + 5], "110") == 0)){
                        flg += sprintf(shopinfs + flg,"{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                                        ,azResultMenu[i],azResultMenu[i + 1],azResultMenu[i + 2],azResultMenu[i + 3],urls.c_str(),azResultMenu[i + 4],azResultMenu[i + 5]);
                        break;
                    }
                }
                for(j = i + ncolumnMenu; j < ((nrowMenu + 1) * ncolumnMenu); j += ncolumnMenu){
                    if(strcasecmp(azResultMenu[j], azResult[n]) == 0 && (strcasecmp(azResultMenu[j + 5], "100") == 0 || strcasecmp(azResultMenu[j + 5], "101") == 0 || strcasecmp(azResultMenu[j + 5], "111") == 0 || strcasecmp(azResultMenu[j + 5], "110") == 0)){
                        flg += sprintf(shopinfs + flg,",{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                                        ,azResultMenu[j],azResultMenu[j + 1],azResultMenu[j + 2],azResultMenu[j + 3],urls.c_str(),azResultMenu[j + 4],azResultMenu[j + 5]);
                    }
                }
                flg += sprintf(shopinfs + flg,"]}");
                return ;
            }
            else{
                sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
                return ;
            }
        }
    }
    if(Menu == false){
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
        return ;
    }
    return ;
}

void SqlManage::getdinnershop(char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select id,ShopName,shoptyp from UserytoShop;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::getdinnershop:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumn;i<((nrow + 1)*ncolumn);i+=ncolumn){
        if((strcasecmp(azResult[i + 2], "100") == 0 || strcasecmp(azResult[i + 2], "101") == 0 || strcasecmp(azResult[i + 2], "111") == 0 || strcasecmp(azResult[i + 2], "110") == 0)){
            flg += sprintf(shopinfs + flg, "{\"ShopName\":\"%s\",\"sid\":\"%s\"}", azResult[i + 1], azResult[i]);
            break;
        }
    }
    for(j = i + ncolumn;j<((nrow + 1)*ncolumn);j+=ncolumn){
        if((strcasecmp(azResult[j + 2], "100") == 0 || strcasecmp(azResult[j + 2], "101") == 0 || strcasecmp(azResult[j + 2], "111") == 0 || strcasecmp(azResult[j + 2], "110") == 0)){
            flg += sprintf(shopinfs + flg, ",{\"ShopName\":\"%s\",\"sid\":\"%s\"}", azResult[j + 1], azResult[j]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

void SqlManage::getAlldinner(char * shopinfs, int flg){
    char **azResultMenu=NULL; //二维数组存放结果
    int nrowMenu=0;  
    int ncolumnMenu = 0;
    char sqlMenu[200];
    sprintf(sqlMenu, "select sid, name, hot, money, photo, eattype from AllMenu;");
    sqlite3_get_table( db, sqlMenu, &azResultMenu, &nrowMenu, &ncolumnMenu, &zErrMsg);
    if(ncolumnMenu<=0){
        logtotest("SqlManage::getAlldinner:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumnMenu; i < ((nrowMenu + 1) * ncolumnMenu); i += ncolumnMenu){
        if((strcasecmp(azResultMenu[i + 5], "100") == 0 || strcasecmp(azResultMenu[i + 5], "101") == 0 || strcasecmp(azResultMenu[i + 5], "111") == 0 || strcasecmp(azResultMenu[i + 5], "110") == 0)){
            flg += sprintf(shopinfs + flg,"{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                            ,azResultMenu[i],azResultMenu[i + 1],azResultMenu[i + 2],azResultMenu[i + 3],urls.c_str(),azResultMenu[i + 4],azResultMenu[i + 5]);
            break;
        }
    }
    for(j = i + ncolumnMenu; j < ((nrowMenu + 1) * ncolumnMenu); j += ncolumnMenu){
        if((strcasecmp(azResultMenu[j + 5], "100") == 0 || strcasecmp(azResultMenu[j + 5], "101") == 0 || strcasecmp(azResultMenu[j + 5], "111") == 0 || strcasecmp(azResultMenu[j + 5], "110") == 0)){
            flg += sprintf(shopinfs + flg,",{\"sid\":\"%s\",\"name\":\"%s\",\"hot\":\"%s\",\"money\":\"%s\",\"photo\":\"%s%s\",\"eattype\":\"%s\"}"
                            ,azResultMenu[j],azResultMenu[j + 1],azResultMenu[j + 2],azResultMenu[j + 3],urls.c_str(),azResultMenu[j + 4],azResultMenu[j + 5]);
        }
    }
    flg += sprintf(shopinfs + flg,"]}");
    return ;
}

bool SqlManage::getorder(char * sid, char * uid, char * value, char * money, char * shopinfs, int flg,char *status){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select shopid,uid,value,ischick,mony,time from menulist;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    flg += sprintf(shopinfs+flg,"{\"Date\":");
    char time[30];
    gettime(time);
    if(strcmp(sid, "") == 0 || strcmp(uid, "") == 0 || strcmp(value, "") == 0 || strcmp(money, "") == 0){
        return false;
    }
    else{
        const char *datime = gettime().c_str()+8;
        char * rt = sqlite3_mprintf("INSERT INTO menulist VALUES(NULL,'%s','%s','%s','%s','%s','%s','%s','%s')",sid, uid, value, "11",money, time,datime,status);
        int add = sqlite3_exec(db, rt, 0, 0, &zErrMsg);
        if(add == SQLITE_OK){
            sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
            flg += sprintf(shopinfs+flg,"%s}",datime);
            sqlite3_free(rt);
            return true;
        }
        else{
            return false;
        }
    }
}

void SqlManage::Usermessage(char * uid, char * stuID, char * name, char * addrs, char * shopinfs, int flg)
{
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select uid,studentID,name,addrs from Usermessage;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i;
    for(i = ncolumn; i < (nrow + 1) * ncolumn; i += ncolumn){
        if(strcmp(uid, azResult[i]) == 0){
            char * qt = sqlite3_mprintf("UPDATE Usermessage SET studentID='%s', name='%s', addrs='%s' WHERE uid='%s'", stuID, name, addrs, uid);
            int update = sqlite3_exec(db, qt, 0, 0, &zErrMsg);
            if(update == SQLITE_OK){
                sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
                flg += sprintf(shopinfs+flg,"{\"uid\":\"%s\",\"stuID\":\"%s\",\"name\":\"%s\",\"addrs\":\"%s\"}]}",
                azResult[i], azResult[i + 1], azResult[i + 2], azResult[i + 3]);
                sqlite3_free(qt);
                return;
            }
        }
    }
    char * rt = sqlite3_mprintf("INSERT INTO Usermessage VALUES(NULL,'%s','%s','%s','%s')", uid, stuID, name, addrs);
    int add = sqlite3_exec(db, rt, 0, 0, &zErrMsg);
    if(add == SQLITE_OK){
        sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
        flg += sprintf(shopinfs+flg,"{\"uid\":\"%s\",\"stuID\":\"%s\",\"name\":\"%s\",\"addrs\":\"%s\"}]}",
        azResult[(nrow * ncolumn)], azResult[(nrow * ncolumn) + 1], azResult[(nrow * ncolumn) + 2], azResult[(nrow * ncolumn) + 3]);
        sqlite3_free(rt);
        return;
    }
}

void SqlManage::checkmessage(char * uid, char * shopinfs, int flg){
    char **azResult=NULL; //二维数组存放结果
    int nrow=0;  
    int ncolumn = 0;
    char sql[200];
    sprintf(sql, "select uid,studentID,name,addrs from Usermessage;");
    sqlite3_get_table( db, sql, &azResult, &nrow, &ncolumn, &zErrMsg);
    if(ncolumn<=0){
        logtotest("SqlManage::chechmessage:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i;
    for(i = ncolumn; i < (nrow + 1) * ncolumn; i += ncolumn){
        if(strcmp(azResult[i], uid) == 0){
            flg += sprintf(shopinfs+flg,"{\"uid\":\"%s\",\"stuID\":\"%s\",\"name\":\"%s\",\"addrs\":\"%s\"}]}",
            azResult[i], azResult[i + 1], azResult[i + 2], azResult[i + 3]);
            return ;
        }
    }
}

void SqlManage::shopchoose(char * Menuid, char * shopinfs, int flg){
    char **azResultAll=NULL; //二维数组存放结果
    int nrowAll=0;  
    int ncolumnAll = 0;
    char sqlAll[200];
    sprintf(sqlAll, "select * from AllMenu;");
    sqlite3_get_table( db, sqlAll, &azResultAll, &nrowAll, &ncolumnAll, &zErrMsg);
    if(ncolumnAll<=0){
        logtotest("SqlManage::shopchoose:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    int i, j;
    for(i = ncolumnAll; i < ((nrowAll + 1) * ncolumnAll); i += ncolumnAll){
        if(strcasecmp(azResultAll[i], Menuid) == 0){
            if(strcasecmp(azResultAll[i + 1], "27") == 0){
                char ** azResultMe = NULL;
                int nrowMe = 0;
                int ncolumnMe = 0;
                char sqlMe[200];
                sprintf(sqlMe, "select * from menu_27;");
                sqlite3_get_table( db, sqlMe, &azResultMe, &nrowMe, &ncolumnMe, &zErrMsg);
                if(ncolumnMe <= 0){
                    logtotest("SqlManage::shopchoose:未找到相关数据");
                    sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据");
                    return ;
                }
                char * qt = sqlite3_mprintf("INSERT INTO menu_27 VALUES(NULL,'%s','%s','%s','%s')",azResultAll[i + 1],"2",azResultAll[i + 5],Menuid);
                int ret = sqlite3_exec(db, qt, 0, 0, &zErrMsg);
                if(ret == SQLITE_OK){
                    sqlite3_get_table( db , sqlMe , &azResultMe, &nrowMe, &ncolumnMe, &zErrMsg );
                    for(j = ncolumnMe; j < (nrowMe * ncolumnMe); j += ncolumnMe){
                    flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"shopid\":\"%s\",\"uid\":\"%s\",\"value\":\"%s\",\"ischick\":\"%s\"},",
                        azResultMe[j], azResultMe[j + 1], azResultMe[j + 2], azResultMe[j + 3], azResultMe[j + 4]);
                    }
                    flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"shopid\":\"%s\",\"uid\":\"%s\",\"value\":\"%s\",\"ischick\":\"%s\"}]}",
                        azResultMe[j], azResultMe[j + 1], azResultMe[j + 2], azResultMe[j + 3], azResultMe[j + 4]);
                }
                sqlite3_free(qt);
            }
            // else if(strcasecmp(azResultAll[i + 1], "28") == 0){
            //     char ** azResultMe = NULL;
            //     int nrowMe = 0;
            //     int ncolumnMe = 0;
            //     char sqlMe[200];
            //     sprintf(sqlMe, "select * from menu_28;");
            //     sqlite3_get_table( db, sqlMe, &azResultMe, &nrowMe, &ncolumnMe, &zErrMsg);
            //     if(ncolumnMe <= 0){
            //         logtotest("SqlManage::shopchoose:未找到相关数据");
            //         sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据");
            //         return ;
            //     }
            //     char * qt = sqlite3_mprintf("INSERT INTO menu_28 VALUES(NULL,'%s','%s','%s','%s')",azResultAll[i + 1],"2",azResultAll[i + 5],Menuid);
            //     int ret = sqlite3_exec(db, qt, 0, 0, &zErrMsg);
            //     if(ret == SQLITE_OK){
            //         sqlite3_get_table( db , sqlMe , &azResultMe, &nrowMe, &ncolumnMe, &zErrMsg );
            //         for(j = ncolumnMe; j < (nrowMe * ncolumnMe); j += ncolumnMe){
            //         flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"shopid\":\"%s\",\"uid\":\"%s\",\"value\":\"%s\",\"ischick\":\"%s\"},",
            //             azResultMe[j], azResultMe[j + 1], azResultMe[j + 2], azResultMe[j + 3], azResultMe[j + 4]);
            //         }
            //         flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"shopid\":\"%s\",\"uid\":\"%s\",\"value\":\"%s\",\"ischick\":\"%s\"}]}",
            //          azResultMe[j], azResultMe[j + 1], azResultMe[j + 2], azResultMe[j + 3], azResultMe[j + 4]);
            //     }
            //     sqlite3_free(qt);
            // }
        }
    }
}

void SqlManage::Userchoose(char * Menuid, char * shopinfs, int flg){
    char **azResultUser=NULL; //二维数组存放结果
    int nrowUser=0;  
    int ncolumnUser = 0;
    char sqlUser[200];
    sprintf(sqlUser, "select * from Userhis;");
    sqlite3_get_table( db, sqlUser, &azResultUser, &nrowUser, &ncolumnUser, &zErrMsg);
    if(ncolumnUser<=0){
        logtotest("SqlManage::Userchoose:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    char **azResultAll=NULL; //二维数组存放结果
    int nrowAll=0;  
    int ncolumnAll = 0;
    char sqlAll[200];
    sprintf(sqlAll, "select * from AllMenu;");
    sqlite3_get_table( db, sqlAll, &azResultAll, &nrowAll, &ncolumnAll, &zErrMsg);
    if(ncolumnAll<=0){
        logtotest("SqlManage::Userchoose:未找到相关数据");
        sprintf(shopinfs+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_onfand,"未找到相关数据"); 
        return ;
    }
    int i, j;
    for(i = ncolumnAll; i < ((nrowAll + 1) * ncolumnAll); i += ncolumnAll){
        if(strcasecmp(azResultAll[i], Menuid) == 0){
            char * qt = sqlite3_mprintf("INSERT INTO Userhis VALUES(NULL,'%s','%s','%s')",azResultAll[i + 1],"2",azResultAll[i + 5]);
            sqlite3_exec(db, qt, 0, 0, &zErrMsg);
            sqlite3_free(qt);
        }
    }
    int num = 0;
    char value[200];
    flg += sprintf(shopinfs+flg,"{\"Date\":[");
    sqlite3_get_table( db, sqlUser, &azResultUser, &nrowUser, &ncolumnUser, &zErrMsg);
    for(j = ncolumnUser; j < ((nrowUser + 1) * ncolumnUser); j += ncolumnUser){
        if(strcasecmp(azResultUser[j + 2], "2") == 0){
            num += atoi(azResultUser[j + 3]);
            flg += sprintf(shopinfs+flg,"{\"id\":\"%s\",\"shopid\":\"%s\",\"uid\":\"%s\",\"value\":\"%s\"},",
                azResultUser[j], azResultUser[j + 1], azResultUser[j + 2], azResultUser[j + 3]);
        }
    }
    sprintf(value,"%d",num);
    flg += sprintf(shopinfs+flg,"{\"uid\":\"%s\",\"Allvalue\":\"%s\"}]}","2", value);
}


void SqlManage::GETsqlAdd(char *sqlset_inf,string sqladdrs)
{
  
  //string sqltime;
  //sqltime=gettime();
  char sqltime[30];
    gettime(sqltime);
  char * rt = sqlite3_mprintf("INSERT INTO logwx VALUES(NULL,'%s','%s','%s','%s')","GET",sqlset_inf,sqladdrs.c_str(),sqltime);
  sqlite3_exec( db , rt  ,NULL  ,NULL ,&zErrMsg );
  sqlite3_free(rt);
}
void SqlManage::POSTsqlAdd(char *sqlset_inf,string sqladdrs)
{
  char sqltime[30];
    gettime(sqltime);
  char * rt = sqlite3_mprintf("INSERT INTO logwx VALUES(NULL,'%s','%s','%s','%s')","POST",sqlset_inf,sqladdrs.c_str(),time);
  sqlite3_exec( db , rt  ,NULL  ,NULL ,&zErrMsg );
  sqlite3_free(rt);
}