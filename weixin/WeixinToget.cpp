/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:40:35
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */
#include"WeixinToget.h"


WeixinToGet::WeixinToGet(){
  //Sqlmanagetocli *sqlcli;
  sqlcli = new SqlManage;

}

void WeixinToGet::init(char *others,string addr,int link, map<string,string> map){
    this->ipaddr = addr;
    othre = others;
    ipaddr = addr;
    LinkNumber = link;
    mapcli.clear();
    mapcli = map;
}

WeixinToGet::~WeixinToGet(){
    delete sqlcli;
}

/**
 * @description: 任务处理
 * @param {*}
 * @return {*}
 */
void WeixinToGet::managementGET(char url[]){
    char response[200000];
    int flg;
    
    cout<<"file:"<<url<<endl;
   if((searchStr(url,".jpg")||searchStr(url,".png")||searchStr(url,".html"))){
      char file[100];
      sprintf(file,"..%s",url);
      cout<<file<<endl;
       int headlen = strlen("HTTP/1.1 200 OK \r\nContent-Type: jpg;\r\n\r\n");
        sprintf(response,"HTTP/1.1 200 OK \r\nContent-Type: jpg;\r\n\r\n");
        
        int filefd = open(file,O_RDONLY);
        int filen = read(filefd,response+headlen,sizeof(response)-headlen);
         write(LinkNumber,response,headlen+filen);
        close(filefd);
        return ;
    }
    sqlcli->GETsqlAdd(url,ipaddr);//日志储存
    flg = sprintf(response,"HTTP/1.1 200 OK \r\nContent-Type: text/plain; charset=utf-8;\r\n\r\n");
    /* 店铺列表  */ 
    if(strcasecmp(url,"/showshop")==0){ 
          sqlcli->shopinf(response,flg);
    }
    /* 资源请求 jpg\xml\png\.....  */ 
     
    else if(strcasecmp(url,"/login")==0){
      std::map<std::string,std::string> ::iterator userkey = mapcli.find("key"); 
      if(userkey==mapcli.end()){
        logtotest("url,/login: 没有找到参数key");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char* c_c_userkey = ((*userkey).second).data();
        char* c_userkey = new char[strlen(c_c_userkey)+1];
        strcpy(c_userkey,c_c_userkey);
        sqlcli->loginf(response,c_userkey,flg);
        delete(c_userkey);
      }
      /**
       * ((*userkey).second) ---- key的值 类型为string
       * 
       * 1、key存在
       * 返回 id号
       * 2、key不存在
       * 存入数据库
       * 返回id号
       * 
       */      
    
    }
    else if(strcasecmp(url,"/Menu") == 0)
    {
        std::map<std::string,std::string> ::iterator shoppage = mapcli.find("page"); 
        if(shoppage==mapcli.end()){
        logtotest("url,/showshop: 没有找到参数page");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
        } 
        else{
          int page = atoi(((*shoppage).second).c_str());
          sqlcli->getMenu(page,response,flg);
        }  
    }

    else if(strcasecmp(url,"/Menushop") == 0){
      // 每家店铺的菜单
      //参数：店铺ID 返回该店铺的菜单
      std::map<std::string,std::string> ::iterator shopsid = mapcli.find("sid"); 
      if(shopsid==mapcli.end()){
        logtotest("url,/Menushop: 没有找到参数sid");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_sid = ((*shopsid).second).data();
        char * sid = new char[strlen(c_sid)+1];
        strcpy(sid,c_sid);
        sqlcli->ShopMenu(sid, response, flg);
        delete sid;
      }
    }

    else if(strcasecmp(url,"/shopchoose") == 0){
        std::map<std::string,std::string> ::iterator chooseid = mapcli.find("id");
        if(chooseid==mapcli.end()){
        logtotest("url,/choose: 没有找到参数id");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_Menuid = ((*chooseid).second).data();
        char * Menuid = new char[strlen(c_Menuid)+1];
        strcpy(Menuid,c_Menuid);
        sqlcli->shopchoose(Menuid, response, flg);
        delete Menuid;
      }
    }

    else if(strcasecmp(url,"/Userchoose") == 0){
        std::map<std::string,std::string> ::iterator chooseid = mapcli.find("id");
        if(chooseid==mapcli.end()){
        logtotest("url,/Userchoose: 没有找到参数id");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_Menuid = ((*chooseid).second).data();
        char * Menuid = new char[strlen(c_Menuid)+1];
        strcpy(Menuid,c_Menuid);
        sqlcli->Userchoose(Menuid, response, flg);
        delete Menuid;
      }
    }

    else if(strcasecmp(url, "/breakfast") == 0){
      std::map<std::string,std::string> ::iterator shopsid = mapcli.find("sid");
      if(shopsid == mapcli.end()){
        logtotest("url,/breakfast: 没有找到参数sid");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_sid = ((*shopsid).second).data();
        char * sid = new char[strlen(c_sid)+1];
        strcpy(sid,c_sid);
        sqlcli->getbreakfast(sid, response, flg);
        delete sid;
      }
    }

    else if(strcasecmp(url, "/breakfastshop") == 0){
        sqlcli->getbreakfastshop(response, flg);
    }

    else if(strcasecmp(url, "/Allbreakfast") == 0){
      sqlcli->getAllbreakfast(response, flg);
    }

    else if(strcasecmp(url, "/lunch") == 0){
      std::map<std::string,std::string> ::iterator shopsid = mapcli.find("sid");
      if(shopsid == mapcli.end()){
        logtotest("url,/breakfast: 没有找到参数sid");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_sid = ((*shopsid).second).data();
        char * sid = new char[strlen(c_sid)+1];
        strcpy(sid,c_sid);
        sqlcli->getLunch(sid, response, flg);
        delete sid;
      }
    }

    else if(strcasecmp(url, "/lunchshop") == 0){
        sqlcli->getLunchshop(response, flg);
    }

    else if(strcasecmp(url, "/Alllunch") == 0){
      sqlcli->getAllLunch(response, flg);
    }

    else if(strcasecmp(url, "/dinner") == 0){
      std::map<std::string,std::string> ::iterator shopsid = mapcli.find("sid");
      if(shopsid == mapcli.end()){
        logtotest("url,/breakfast: 没有找到参数sid");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_sid = ((*shopsid).second).data();
        char * sid = new char[strlen(c_sid)+1];
        strcpy(sid,c_sid);
        sqlcli->getdinner(sid, response, flg);
        delete sid;
      }
    }

    else if(strcasecmp(url, "/dinnershop") == 0){
        sqlcli->getdinnershop(response, flg);
    }

    else if(strcasecmp(url, "/Alldinner") == 0){
        sqlcli->getAlldinner(response, flg);
    }

    else if(strcasecmp(url, "/Mylist") == 0){ ///?
      ;
    }


    else if(strcasecmp(url, "/Usermessage") == 0){
      std::map<std::string,std::string> ::iterator uid = mapcli.find("uid");
      std::map<std::string,std::string> ::iterator studentID = mapcli.find("stuID");
      std::map<std::string,std::string> ::iterator studentname = mapcli.find("name");
      std::map<std::string,std::string> ::iterator studentaddrs = mapcli.find("addrs");
      if(studentID == mapcli.end() || uid == mapcli.end() || studentname == mapcli.end() || studentaddrs == mapcli.end()){
        logtotest("url,/Usermessage: 没有找到参数");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_uid = ((*uid).second).data();
        char * uid = new char[strlen(c_uid)+1];
        strcpy(uid,c_uid);
        const char * c_stuid = ((*studentID).second).data();
        char * stuid = new char[strlen(c_stuid)+1];
        strcpy(stuid,c_stuid);
        const char * c_name = ((*studentname).second).data();
        char * name = new char[strlen(c_name)+1];
        strcpy(name,c_name);
        const char * c_addrs = ((*studentaddrs).second).data();
        char * addrs = new char[strlen(c_addrs)+1];
        strcpy(addrs,c_addrs);
        sqlcli->Usermessage(uid, stuid, name, addrs, response, flg);
        delete uid;
        delete stuid;
        delete name;
        delete addrs;
      }
     
    }
    else if(strcasecmp(url, "/checkmessage") == 0){
      std::map<std::string,std::string> ::iterator uid = mapcli.find("uid");
      if(uid == mapcli.end()){
        logtotest("url,/checkmessage: 没有找到参数");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_uid = ((*uid).second).data();
        char * uid = new char[strlen(c_uid)+1];
        strcpy(uid,c_uid);
        sqlcli->checkmessage(uid, response, flg);
        delete uid;
      }
    }

//----------------------------------------------------------------------------------------------
    
    /* ------Erry------ */
    else{
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-7,"路径err"); 

         //检测访问是否安全
      //if(reqisok) Sq->req_dager(url,ipaddr);
    }


    write(LinkNumber,response,strlen(response));
}



/**
 * @description: 获取单元号
 * @param {*}
 * @return {*}
 */
// int WeixinToGet::getunit(char *data,int &flg){
// map<string,string>::iterator st = mapcli.find("unit");
//   if(st == mapcli.end()){
//     logtotest("没有找到该单元！！！");
//     sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少"); 
//   return -1;
//   }
// return strtoint(((*st).second));
// }

