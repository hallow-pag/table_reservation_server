/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:14:56
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */


#include"WeixinToPost.h"


WeixinToPost::WeixinToPost(){
  
  //Sqlmanagetocli *sqlcli;
  sqlcli = new SqlManage;

}

void WeixinToPost::init(char *others,string addr,int link, map<string,string> map){
    this->ipaddr = addr;
    othre = others;
    ipaddr = addr;
    LinkNumber = link;
    mapinf.clear();
    mapinf = map;
}

WeixinToPost::~WeixinToPost(){
    delete sqlcli;
}


/**
 * @description: 任务处理---POST请求
 * @param {POST请求地址}
 * @return {*}
 */
void WeixinToPost::managementPOST( char url[]){
char response[320];
char filename[20];
char files[2000];
int flg;
    sqlcli->POSTsqlAdd(url,ipaddr);//日志储存
    flg = sprintf(response,"HTTP/1.1 200 OK \r\nContent-Type: text/plain; charset=utf-8;\r\n\r\n");

    if(strcasecmp(url,"/input")==0){
        int i = 600;
        int f=0,s=0;
        while(i<1000){
            if(othre[i]=='f'&&othre[i+7]=='e'){ break;}
            i++; 
            }
        i += 10;
        while(othre[i]!='\"'){
            if(f==20) break;
                filename[f++] = othre[i++]; 
        }  filename[f] = '\0';
        
        while(i<1200){
            if(othre[i]=='\n'&&othre[i+1]=='\n') break;
             i++;
             }
        i += 1;
        //cout<<"---"<<i<<"---- "<<endl;
        while(othre[i]!='-'||othre[i+4]!='-'){
          if(s==2000) break;
             files[s++] = othre[i++]; 
            
        } files[s]='\0';
       
        //---------------------------------------   
        //定义写入文件
        FILE *pFile;
        //定义文件路径变量
 
        char local_file[40];
        //变量赋值
        sprintf(local_file,"../src/%s",filename);
        //打开文件
        
        pFile = fopen(local_file,"w+");
        //定义写入变量
        if(pFile==NULL) {
            cout<<"---Ree---- "<<endl;
            return ;
        }
 
        fwrite(files,strlen(files),1,pFile);
        fclose(pFile);
        //----------------------------------------

        sprintf(response+flg,"%s","OK");

    }

    else if(strcasecmp(url,"/getorder")==0){
        std::map<std::string,std::string> ::iterator shopsid = mapinf.find("sid");
        std::map<std::string,std::string> ::iterator uid = mapinf.find("uid");
        std::map<std::string,std::string> ::iterator value = mapinf.find("value");
        std::map<std::string,std::string> ::iterator money = mapinf.find("mony");
        std::map<std::string,std::string> ::iterator status = mapinf.find("status");

      if(shopsid == mapinf.end() || uid == mapinf.end() || value == mapinf.end() || money == mapinf.end()||status==mapinf.end()){
        logtotest("url,/getorder: 没有找到参数");
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",err_nametoshort,"参数err");
      }
      else{
        const char * c_sid = ((*shopsid).second).data();
        char * sid = new char[strlen(c_sid)+1];
        strcpy(sid,c_sid);
        const char * c_uid = ((*uid).second).data();
        char * uid = new char[strlen(c_uid)+1];
        strcpy(uid,c_uid);
        const char * c_value = ((*value).second).data();
        char * value = new char[strlen(c_value)+1];
        strcpy(value,c_value);
        const char * c_money = ((*money).second).data();
        char * money = new char[strlen(c_money)+1];
        strcpy(money,c_money);

         const char * c_status = ((*status).second).data();
        char * status = new char[strlen(c_status)+1];
        strcpy(status,c_status);
        sqlcli->getorder(sid, uid, value, money, response, flg,status);
        delete sid;
        delete uid;
        delete value;
        delete money;
      }
        /*
        用户点餐付款后将菜品信息提交到服务器。
        1、获取mapinf中的参数 sid（店铺号）、uid(用户号)、value（点的菜品），mony（金额）。
        2、四个参数都不能为空。为空据就返回-1 。
        3、将这些参数存入数据库menulist表、time在服务器获取gettime()，ischick固定填11(第一位是是否店内就餐，第二位是菜品完成状态),
         成功返回1
        */
          //sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",ok,"这是POST请求方式");  
    }

    else{
        sprintf(response+flg,"%s","NO");
        }

		write(LinkNumber,response,strlen(response));
        close(LinkNumber);

}

/**
 * @description: 获取单元号
 * @param {*}
 * @return {*}
 */
// int WeixinToPost::getunit(char *data,int &flg){
// map<string,string>::iterator st = mapcli.find("unit");
//   if(st == mapcli.end()){
//     logtotest("没有找到该单元！！！");
//     sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少"); 
//   return -1;
//   }
// return strtoint(((*st).second));
// }
