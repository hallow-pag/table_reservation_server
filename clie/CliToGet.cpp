/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:40:35
 * @LastEditors: yokon
 * @Description:
 *  再码一行！！！
 */
#include "CliToGet.h"

CliToGet::CliToGet() {
  // Sqlmanagetocli *sqlcli;
  sqlcli = new Sqlmanagetocli;
}

void CliToGet::init(string addr, int link, map<string, string> map) {
  this->ipaddr = addr;
  ipaddr = addr;
  LinkNumber = link;
  mapcli.clear();
  mapcli = map;
  unit = 0;
}

CliToGet::~CliToGet() { delete sqlcli; }

/**
 * @description: 任务处理---GET请求
 * @param {GET请求地址}
 * @return {*}
 */
void CliToGet::managementGET(char url[]) {
  char response[200000];
  int flg;
  if ((searchStr(url, ".jpg") || searchStr(url, ".png") ||
       searchStr(url, ".html"))) {
    char file[100];
    sprintf(file, "..%s", url);
    cout << file << endl;
    int headlen = strlen("HTTP/1.1 200 OK \r\nContent-Type: jpg;\r\n\r\n");
    sprintf(response, "HTTP/1.1 200 OK \r\nContent-Type: jpg;\r\n\r\n");

    int filefd = open(file, O_RDONLY);
    if (filefd <= 0) {
      write(LinkNumber, "HTTP/1.1 200 OK \r\nContent-Type: jpg;\r\n\r\n", 80);
      close(filefd);
      return;
    }

    int filen = read(filefd, response + headlen, sizeof(response) - headlen);
    write(LinkNumber, response, headlen + filen);
    close(filefd);
    return;
  }
  /* 资源请求 jpg\xml\png\.....  */


/*
路径请求
移动端所有的非资源GET请求会到达此处将这些请求的信息存入数据库
（CliToPost.cpp）也需要添加
1、在Sqlmanagetocli.h中创建一个函数用来处理日志信息。
2、传入相关信息  type 请求类型，此处固定为GET 、CliToPost.cpp中固定为POST 
              ,set_inf 请求地址信息
              ,addrs   ip地址（ipaddr）
              ,time     调用pbulic.h 中的获取时间函数
3、不需要结束

weixin文件夹也需要添加！！！

*/
sqlcli->GETsqlAdd(url,ipaddr);//日志储存
  flg = sprintf(
      response,
      "HTTP/1.1 200 OK \r\nContent-Type: text/plain; charset=utf-8;\r\n\r\n");
  /* 店铺列表  */
  unit = getunit(response, flg);
  // if (unit == -1) {
  //   goto endqspram; //提前结束
  //   return;
  // }
  if (strcasecmp(url, "/clishowshop") == 0) {
    if (sqlcli->getdatashopinf(response, flg, unit) == -1) { //查询失败
      goto endqspram; //提前结束
      return;
    }
  }

  /* 获取本店菜单 */
  else if (strcasecmp(url, "/cligetnum") == 0) {
    sqlcli->getmenu(response, flg, unit);
  }

  /* registered */
  else if (strcasecmp(url, "/clihat") == 0) {
   map<string,string>::iterator it =  mapcli.find("id");
    sqlcli->havemenu(response, flg, unit,it->second.c_str());

  }

/* 【大屏显示  */
  else if(strcasecmp(url, "/list") == 0){
    sqlcli->list(response,flg);
  }
 

  //-----------------------------------------------------------------------------------------------

  //----------------------------------------------------------------------------------------------

  /* ------Erry------ */
  else {
    sprintf(response + flg, "{\"data\":{\"return\":%d,\"text\":\"%s\"}}", -7,
            "路径err");

    //检测访问是否安全
    // if(reqisok) Sq->req_dager(url,ipaddr);
  }
endqspram: /// GOTO 遇到程序需要提前推出

  write(LinkNumber, response, strlen(response));
}

/**
 * @description: 获取单元号
 * @param {*}
 * @return {*}
 */
int CliToGet::getunit(char *data, int &flg) {
  map<string, string>::iterator st = mapcli.find("unit");
  if (st == mapcli.end()) {
    logtotest("没有找到该单元！！！");
    sprintf(data + flg, "{\"data\":{\"return\":%d,\"text\":\"%s\"}}", -1,
            "参数缺少");
    return -1;
  }
  return strtoint(((*st).second));
}
