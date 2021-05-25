/*
 * @Author: yokon's 毕业设计
 * @Date: 2021-01-19 21:53:15
 * @LastEditors: yokon
 * @Description: 
 * @ 再码一行！！！
 */
 #include"public.h"
#include <fstream>

/*************************************************
Function: // gettime
Description: // 获取时间
Input: // string
Output: // 0
*************************************************/
void gettime(char* psTime) {
    time_t nSeconds;
    struct tm * pTM;
    
    time(&nSeconds);
    pTM = localtime(&nSeconds);
    

    /*
    sprintf(psDate,"%04d-%02d-%02d", 
            pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday);
    */
    /* 系统时间，格式: HHMMSS */
    sprintf(psTime, "%02d-%02d-%02d %02d:%02d:%02d",
            pTM->tm_year + 1900, pTM->tm_mon + 1, pTM->tm_mday,
            pTM->tm_hour, pTM->tm_min, pTM->tm_sec);
              
}

/*************************************************
Function: // gettime
Description: // 获取时间
Input: // 0
Output: // string
*************************************************/
string gettime()
{
    time_t t=time(0);
    char tmp[32];
	memset(tmp,0,32);
    strftime(tmp,sizeof(tmp),"%Y%m%d%H%M%S",localtime(&t));
    return tmp;
}

bool writefile(string file,string &date){

	std::ofstream ifs(file, std::ios::out | std::ios::binary);
	     //// const char * !!!!!!!!!
	ifs.write(date.data(), date.length()); 
	cout<<"开始写入 path:"<<file<<"length:"<<date.length()<<endl;
	ifs.close();
	return true;
}

// bool writefile(string file,char * date,int len){
// 		FILE *fq;
// 	  if( ( fq = fopen(file.c_str(),"rb") ) == NULL ){
//         printf("File open.\n");
// 		return false;
//     }

//     bzero(date,len);
//     while(!feof(fq)){
//         len = fread(date, 1, sizeof(date), fq);
//         if(len != write(date, buffer, len)){
//             printf("write.\n");
//             break;
// 	}}

//     fclose(fq);
// }

/*************************************************
Function: // chartoint
Description: // 字符串转int
Input: // string
Output: // int
*************************************************/
int chartoint( char* str){
    if(str[0]=='-')
    return -1;
    int sum = 0,l = strlen(str);
    for(int i=0;i<l&&str[i]!=' ';i++){
		
        sum*=10;
        sum += (str[i]-'0');
    }
return sum;
}

/*************************************************
Function: // strtochar
Description: // 字符串转int
Input: // string
Output: // int
*************************************************/
char* strtochar(string str, char *an){

    int i;
    for(i=0;i<(int)str.size()&&i<20;i++)
    an[i] = str[i];
    an[i] = '\0';
   
return an;
}

/*************************************************
Function: // strtoint
Description: // 字符串转int
Input: // string
Output: // int
*************************************************/
int strtoint(std::string str){
	if(str[0]=='-')
    return -1;
    int sum = 0,l = str.length();
    for(int i=0;i<l;i++){
        sum*=10;
        sum += (str[i]-'0');
    }
return sum;
   

}

/*************************************************
Function: // searchStr
Description: // 字符串字符串1是否包含字符串2
Output: // bool
*************************************************/
bool searchStr(const char *pSource,const char *pSearch)
{
	//在pSource查找字符pSearch是否存在
	int lenSource=strlen(pSource);
	int lenSearch=strlen(pSearch);
	int firstCharNum = lenSource+1;
	//判断搜索字符串是否比源字符串大
	if(lenSearch>lenSource)
	{
		return false;
	}
	//遍历字符串 找到第一个相同的字符位置 firstCharNum
	for(int i=0;i<lenSource;i++)
	{
		if(pSource[i]==pSearch[0])
		{
			//找到目标字符
			firstCharNum = i;
			break;
		}
	}
	if(firstCharNum>lenSource|| (lenSource-firstCharNum)<lenSearch)
	{
		//没有找到相同字符
		return false;
	}
	//首字符之后字符连续相同返回true
	int j=1;
	for(int i=firstCharNum+1;i<(firstCharNum+lenSearch);i++)
	{
		//遍历字符串
		if(pSource[i]==pSearch[j])
		{
				//找到目标字符
			j++;
		}
		else
		{
			//递归调用自己
			const char *newsource=pSource+firstCharNum+1;	
			return searchStr(newsource,pSearch);
		}
	}
	return true;
 
}

/**
 * @description:  打印提示消息
 * @param {*}
 * @return void 
 */
void logtotest(string log){
     cout<<log<<endl;
}


void to_hex( char* buff, int buff_len) {
    char str[33];
    bzero(str, 33);
    int ret = 0;
    for (int i = 0; i < 16 && i < buff_len; i++) {
        ret += sprintf(str + ret, "%02x", buff[i]);
    }
    printf("buff_hex_str:%s\r\n", str);
}


