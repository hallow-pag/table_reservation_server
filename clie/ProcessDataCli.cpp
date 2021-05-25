/*
 * @Author: yokon's 毕业设计
 * @Date: 2020-11-28 15:39:54
 * @LastEditors: yokon
 * @Description:
 * @ 再码一行！！！
 */

#include"ProcessDataCli.h"
#include "CliToPost.h"
#include "Sqlmanagetocli.h"
#include <string>
#include <utility>


ProcessDataCli::ProcessDataCli() {
get = new CliToGet;
post = new CliToPost;

}


ProcessDataCli::~ProcessDataCli() {

delete post;
delete get;

}


//处理 得到URL 参数
void ProcessDataCli::accept_request() {

  char Request[301];
  char funck[15];
  char Url[200];
  numchars = get_line(LinkNumber, Request, 300); //取第一行 ，请求方式 GET POST ，USL，参数
  int len = strlen(Request);
  read(LinkNumber,othre,80000);
  //recv(LinkNumber, othre, 8000,0); 

  // for(int i=0;i<3000;i++)
  // printf("%c",othre[i]);
  
  try {
    /* code */
     cout << "Request:" << Request << endl;
    sscanf(Request, "%s %[a-z,A-Z,0-9,/,.,_,] HTTP", funck, Url);
  } catch (const std::exception &e) {
    std::cerr << "url err" << '\n'; 
    strcpy(Url, "/0");
  }
  //getCookie(othre); //创建一个Cookie
  cout << "Url:" << Url << endl;
  if (strcasecmp("GET", funck) == 0) {           /* ******GET******** */
    screen(Request, len);
  get->init(ipaddr,LinkNumber, mapcli);
  get->managementGET(Url);


  } else if (strcasecmp("POST", funck) == 0) {    /* ******POST******** */
     //logtotest(string("othersp\n")+othersp);
  char len[8];
  int dlen=0;
  for(int i=0;i<100;i++){
    if(othre[i] == 'D'&&othre[i+4]=='L'){
      int flgsw=0; i+=9;
      while(othre[i]!='\n'){ len[flgsw++] = othre[i++];  }
      len[flgsw] ='\0';
      dlen = chartoint(len);
      
    }
    if(othre[i] == 'D'&&othre[i+4]=='D'){
      othersp.clear();
      othersp.append(othre+i+6,dlen);
    }
  }
 
  getparam(othersp);
  post->init(othersp, ipaddr,LinkNumber, mapcli);
  post->managementPOST(Url);
  }
}
/**
 * @description:初始化参数 连接号、地址
 * @param fd, addr
 * @return {void}
 */
void ProcessDataCli::responses_init(int fd, char *addr) {
  LinkNumber = fd;
  strcpy(ipaddr, addr);
}
/**
 * @description: 获取请求响应第一行数据，超过300字节自动当作恶意访问
 * @param {*}
 * @return {*}
 */
int ProcessDataCli::get_line(int sock, char *buf, int size) {
  int i = 0;
  char c = '\0';
  int n;

  while ((i < size - 1) && (c != '\n') && (i < 300)) {
    n = recv(sock, &c, 1, 0);
    /* DEBUG printf("%02X\n", c); */
    if (n > 0) {
      if (c == '\r') {
        n = recv(sock, &c, 1, MSG_PEEK);
        /* DEBUG printf("%02X\n", c); */
        if ((n > 0) && (c == '\n'))
          recv(sock, &c, 1, 0);
        else
          c = '\n';
      }
      buf[i] = c;
      i++;
    } else
      c = '\n';
  }
  buf[i] = '\0';

  return (i);
}
/**
 * @description: 获取GET参数并保存在mapcli中
 * @param {char Request[] 需要被解析的数据 ,int len 长度 }
 * @return {void }
 */
void ProcessDataCli::screen(char Request[], int len) {
  //logtotest(Request+100);
mapcli.clear();
  int i = 0;
  int n = 0;
  for (; i < len; i++) {
    if (Request[i] == '?')
      break;
  }
  char key[20] = {0};
  char value[20] = {0};

  for (i++; i < len; i++, n++) {
    if (Request[i] == '=') {
      key[n] = '\0';
      n = 0;
      for (i++; i <= len; i++, n++) {
        if (Request[i] == '&' || Request[i] == ' ') {
          value[n] = '\0';
          mapcli.insert(make_pair(string(key), string(value)));
          n = 0;
          i++;
          break;
        }
        if (n > 19)
          n--;
        value[n] = Request[i];
      }
    }
    if (n > 19)
      n--;
    key[n] = Request[i];
  }
  std::map<std::string, std::string>::iterator it;
  cout << "开始 GET解析参数。。。。" << endl;
  for (it = mapcli.begin(); it != mapcli.end(); it++)
    std::cout << (*it).first << " " << (*it).second << std::endl;
    
}



/**
 * @description: 获取POST参数并保存在mapcli中
 * @param {char Request[] 需要被解析的数据 ,}
 * @return {void }
 */
void ProcessDataCli::getparam(string & json) {

  //logtotest("json:"+json);
	long long len = json.size(), i = 0;
	int photolen = 0,count=0;
	int pos_1 = 0, pos_2 = 0;
	string key, value;
	string length = "length";
 mapcli.clear();
	while (pos_1 != len)
	{
		if (json[pos_1] == '"')
		{
			pos_2 = pos_1 + 1;
			while (json[pos_2] != '"')
			{
				pos_2++;
			}
			if(json[pos_2] == '"')
			{
				if(count % 2 != 1)
				{
					value = json.substr(pos_1 + 1, pos_2 - pos_1 - 1);
					
					//cout <<"value:  "<< value << endl;
				}
			else
				{
					key = "";
					if (value == "photo")
					{
						key.append(json, pos_1+1, photolen);
						//key= json.substr(pos_1 + 1, pos_1 + 1+photolen);
					}
					else
					key = json.substr(pos_1 + 1, pos_2 - pos_1 - 1);
					//cout <<"key:  "<< key << endl;
					if (value == length)
					{
						photolen = atoi(key.c_str());
						//cout << "------photolen:" << photolen << endl;
					}
				}
				count++;
				pos_1 = pos_2 + 1;
				pos_2 += 1;
			}
			if (count % 2 == 0)
			{
				mapcli.insert(map<string, string>::value_type(value, key));
			}
			if(value=="photo"&&count%2==0)
			break;
		}
		pos_1++;
	}
	cout<<"------------------------"<<endl;
	//输出测试
	map<string, string>::iterator iter;
	iter = mapcli.begin();
	while (iter != mapcli.end())
	{
    //if (iter->first == "photo") return ;
		cout << iter->first << ":" << iter->second <<" "<< iter->second.length()<<endl;
		iter++;
	}
	return;
}

void ProcessDataCli::screenpost(char Request[], int len)//获取POST参数
{
  string json;
  for(int i=150;i<len&&i<500;i++){
    if(Request[i]=='{'){
      json.append(Request+i);
     Json::Reader reader;
     Json::Value root;
    if (reader.parse(json, root))
    {
      mapcli.clear();
      string  ShopName = root["ShopName"].asString();
      if(!ShopName.empty())  mapcli.insert(std::make_pair("ShopName", ShopName));
      string  ip = root["ip"].asString();
      if(!ip.empty())  mapcli.insert(std::make_pair("ip", ip));
      string  IsLogin = root["IsLogin"].asString();
      if(!IsLogin.empty())  mapcli.insert(std::make_pair("IsLogin", IsLogin));
      string  photopath = root["photopath"].asString();
      if(!photopath.empty())  mapcli.insert(std::make_pair("photopath", photopath));
      string  text = root["text"].asString();
      if(!text.empty())  mapcli.insert(std::make_pair("text", text));
      string  addr = root["addr"].asString();
      if(!addr.empty())  mapcli.insert(std::make_pair("addr", addr));
      string  PhoneNumber = root["PhoneNumber"].asString();
      if(!PhoneNumber.empty())  mapcli.insert(std::make_pair("PhoneNumber", PhoneNumber));
      string  shoper = root["shoper"].asString();
      if(!shoper.empty())  mapcli.insert(std::make_pair("shoper", shoper));
      string  shoptyp = root["shoptyp"].asString();
      if(!shoptyp.empty())  mapcli.insert(std::make_pair("shoptyp", shoptyp));
      string  fdstype = root["fdstype"].asString();
      if(!fdstype.empty())  mapcli.insert(std::make_pair("fdstype", fdstype));

      string  unit2 = root["unit"].asString();
      if(!unit2.empty())  mapcli.insert(std::make_pair("unit", unit2));


    }
      std::map<std::string, std::string>::iterator it;
      cout << "开始 POST 解析参数。。。。" << endl;
      for (it = mapcli.begin(); it != mapcli.end(); it++)
      std::cout << (*it).first << " " << (*it).second << std::endl;

    return ;
    }
    
  }

}


/**
 * @description: 生成20个随机字符
 * @param {*}
 * @return {*}
 */
void ProcessDataCli::randCookie(char *strss) {
  int i;
  srand(time(NULL)); //通过时间函数设置随机数种子，使得每次运行结果随机。
  for (i = 0; i < STR_LEN; i++) {
    strss[i] = rand() % (CHAR_MAX - CHAR_MIN + 1) +
               CHAR_MIN; //生成要求范围内的随机数。
  }
  strss[i] = '\0';
  return;
}

/**
 * @description: 将响应中的Cookie取出，若没有Cookie值将本地cookie设为000000000000000000000
 * @param {*}
 * @return {*}
 */
void ProcessDataCli::getCookie(char *buf) {
  int lentocookie = strlen(buf);
  int ncook = 0;
  for (int i = 400; i < lentocookie; i++) {
    if (buf[i] == 'C' && buf[i + 1] == 'o' && buf[i + 2] == 'o') {
      i = i + 8;
      while (buf[i] != '\n')
        cookie[ncook++] = buf[i++];
      cookie[ncook] = '\0';
      return;
    }
  }
  strcpy(cookie, "000000000000000000000");
  return;
}


