/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-03-12 22:14:56
 * @LastEditors: yokon
 * @Description: 
 *  再码一行！！！
 */


#include"CliToPost.h"
#include<fstream>

CliToPost::CliToPost(){
  
  //Sqlmanagetocli *sqlcli;
  sqlcli = new Sqlmanagetocli;

}

void CliToPost::init(string &others,string addr,int link, map<string,string> map){
    this->ipaddr = addr;
    othre = others;
    ipaddr = addr;
    LinkNumber = link;
    mapcli.clear();
    mapcli = map;
}

CliToPost::~CliToPost(){
    delete sqlcli;
}


/**
 * @description: 任务处理---POST请求
 * @param {POST请求地址}
 * @return {*}
 */
void CliToPost::managementPOST( char url[]){
char response[320];
char filename[20];
char files[2000];
int flg;
    sqlcli->POSTsqlAdd(url,ipaddr);//日志储存
    
    flg = sprintf(response,"HTTP/1.1 200 OK \r\nContent-Type: text/plain; charset=utf-8;\r\n\r\n");
    if(strcasecmp(url,"/input")==0){ ///文件入口
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
/* unit? */

    else if(strcasecmp(url,"/cliupshopinf")==0){    //*************************根新店铺信息*********/cliupshopinf**********************//

   map<string,string> ::iterator stunit = mapcli.find("unit");
   if(stunit == mapcli.end())
   { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少unit");  goto endpostpram; }
        if(sqlcli->upclishopinf(shopinf,response, flg, strtoint(stunit->second))==-1){
          goto endpostpram;  //提前结束
        }

  map<string,string> ::iterator ShopName = mapcli.find("ShopName");
  map<string,string> ::iterator IsLogin = mapcli.find("IsLogin");
  map<string,string> ::iterator photopath = mapcli.find("photo");
  map<string,string> ::iterator text = mapcli.find("text");
  map<string,string> ::iterator addr = mapcli.find("addr");
  map<string,string> ::iterator PhoneNumber = mapcli.find("PhoneNumber");
  map<string,string> ::iterator shoper = mapcli.find("shoper");
  map<string,string> ::iterator shoptyp = mapcli.find("shoptyp");
  map<string,string> ::iterator fdstype = mapcli.find("fdstype");
  shopinf.ShopName = ShopName ==mapcli.end()? shopinf.ShopName:ShopName->second;
  shopinf.ip = ipaddr;
  shopinf.IsLogin = IsLogin ==mapcli.end()? shopinf.IsLogin:IsLogin->second;
  shopinf.photopath = "/Date/src/_"+stunit->second+"/"+stunit->second+".jpg";//photopath ==mapcli.end()? shopinf.photopath:photopath->second;
  shopinf.text = text ==mapcli.end()? shopinf.text:text->second;
  shopinf.addr = addr ==mapcli.end()? shopinf.addr:addr->second;
  shopinf.PhoneNumber = PhoneNumber ==mapcli.end()? shopinf.PhoneNumber:PhoneNumber->second;
  shopinf.shoper = shoper ==mapcli.end()? shopinf.shoper:shoper->second;
  shopinf.shoptyp = shoptyp ==mapcli.end()? shopinf.shoptyp:shoptyp->second;
  shopinf.fdstype = fdstype ==mapcli.end()? shopinf.fdstype:fdstype->second;

if(sqlcli->upclishopinfsave(shopinf,response,flg,strtoint(stunit->second))!=-1){
  if(photopath!=mapcli.end())
   writefile(".."+shopinf.photopath,photopath->second);   //img save
  else {sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"没有img的更新");  goto endpostpram; }
 }       
    }

    else if(strcasecmp(url,"/cliaddmen")==0){                       //*************************添加菜品*********/cliaddmen**********************//

    mymenu menu;
    {
  map<string,string> ::iterator name = mapcli.find("name"); //店铺名
  map<string,string> ::iterator hot = mapcli.find("hot");   //店铺热度
  map<string,string> ::iterator minet = mapcli.find("minet");//上菜时间
  map<string,string> ::iterator unit = mapcli.find("sid");//店铺id号
  map<string,string> ::iterator money = mapcli.find("money");//金额
  map<string,string> ::iterator imgtyp = mapcli.find("imgtype");//图片类型
  map<string,string> ::iterator eattype = mapcli.find("eattype");//
  map<string,string> ::iterator type = mapcli.find("type");//
  
  
  if(eattype!=mapcli.end()) menu.eattype = eattype->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少eattype");  goto endpostpram; }
  if(type!=mapcli.end()) menu.type = type->second; 
  //else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少type");  goto endpostpram; }

  if(name!=mapcli.end()) menu.name = name->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少name");  goto endpostpram; }
  if(minet!=mapcli.end()) menu.minet = minet->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少minet");  goto endpostpram; }
  if(hot!=mapcli.end()) menu.hot = hot->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少hot");  goto endpostpram; }
  if(unit!=mapcli.end()) menu.sid = unit->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少sid");  goto endpostpram; }
  if(money!=mapcli.end()) menu.money = money->second;
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少money");  goto endpostpram; }
  if(imgtyp!=mapcli.end()) menu.imgtype = imgtyp->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少imgtype");  goto endpostpram; }
  menu.filepath = "/Date/src/_"+menu.sid+"/"+gettime()+".jpg";
  
    }
      map<string,string> ::iterator photo = mapcli.find("photo");
      if(photo!=mapcli.end()){
        int lc = sqlcli->addmenu(menu, response, flg);
        if(lc!=-1){
          logtotest("开始保存:"+menu.name);
        writefile("../"+menu.filepath,photo->second);
        }
      }
      else
      {
       sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少"); 
      }

    } 
    //完成订单
    else if(strcasecmp(url, "/cliokmenu")==0){

          map<string, string>::iterator st = mapcli.find("id");
          int menuid = strtoint(st->second);
          sqlcli->okmenu(response,flg,menuid);

                    }


    else if(strcasecmp(url,"/cliupmenu")==0){
      
    map<string,string> ::iterator id = mapcli.find("id");
    
    if(id==mapcli.end()) {
      sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少"); 
      goto endpostpram;  //提前结束
    } 
    mymenu menu;

    if(sqlcli->upmenu(menu,response , flg, id->second)==-1)  goto endpostpram;  //提前结束//=================

{
  map<string,string> ::iterator name = mapcli.find("name"); //店铺名
  map<string,string> ::iterator hot = mapcli.find("hot");   //店铺热度
  map<string,string> ::iterator minet = mapcli.find("minet");//上菜时间
  map<string,string> ::iterator money = mapcli.find("money");//金额
  map<string,string> ::iterator imgtyp = mapcli.find("imgtype");//图片类型
  map<string,string> ::iterator type = mapcli.find("type");//图片类型
  map<string,string> ::iterator eattype = mapcli.find("eattype");//图片类型
  
  if(name!=mapcli.end()) menu.name = name->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少name");  goto endpostpram; }
  if(minet!=mapcli.end()) menu.minet = minet->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少minet");  goto endpostpram; }
  if(hot!=mapcli.end()) menu.hot = hot->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少hot");  goto endpostpram; }
  if(money!=mapcli.end()) menu.money = money->second;
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少money");  goto endpostpram; }
  if(imgtyp!=mapcli.end()) menu.imgtype = imgtyp->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少imgtype");  goto endpostpram; }
  if(type!=mapcli.end()) menu.type = type->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少type");  goto endpostpram; }
  if(eattype!=mapcli.end()) menu.eattype = eattype->second; 
  else { sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少eattype");  goto endpostpram; }


    }
      map<string,string> ::iterator photo = mapcli.find("photo");
      if(photo!=mapcli.end()){
        writefile("../"+menu.filepath,photo->second);
      }
    sqlcli->upmenusave(menu,response,flg,strtoint(id->second));//===================
    }

    else{
        sprintf(response+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"路径错误"); 
        }
endpostpram:
		write(LinkNumber,response,strlen(response));
        close(LinkNumber);

}

/**
 * @description: 获取单元号
 * @param {*}
 * @return {*}
 */
int CliToPost::getunit(char *data,int &flg){
map<string,string>::iterator st = mapcli.find("unit");
  if(st == mapcli.end()){
    logtotest("没有找到该单元！！！");
    sprintf(data+flg,"{\"data\":{\"return\":%d,\"text\":\"%s\"}}",-1,"参数缺少"); 
  return -1;
  }
return strtoint(((*st).second));
}
