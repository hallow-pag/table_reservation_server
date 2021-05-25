# table_reservation_server
C++服务器

#### 介绍

​		在Linux环境下，编写的一个C++服务器。使用非阻塞的方式创建了多个线程用来负责客户端和移动端的数据处理。

​		在通讯方式上，采用了HTTP协议、使用手写Htt协议头来实现数据传输。使用POST&GET请求能够获取到规范的数据。

​		数据传输结构上采用的是JSON数据格式，这样做是为了方便小程序的数据接收展示。

​		图片信息传输也是将图片字节放入数据包，再在服务器创建文件保存。

​		使用Sqlite3存储信息，图片则是以文件存储在对应目录下。

​		软件编译采用的是gcc, 自己编写Cmake语句进行程序编译。

​		程序开发采用的是VSCode、暴力 原始。


#### 文件结构

```
├─build（编译文件）
├─clie（处理客户端数据）
├─Date（资源文件、数据库文件&图片）
│  └─src
│      ├─_27
│        └─meu
├─md5（加密工具）
│  
├─src（项目说明资源文件）
└─weixin（处理小程序端数据）
```

#### 环境

```
系统 Ubuntu 20
环境 g++ 7.5
数据库 sqlite3 
编译工具 GNU Make 4.1 cmake version 3.10.2
```

#### 使用说明

##### 1、sqlite3 安装

```
下载地址：https://www.sqlite.org/
下载格式：sqlite-autoconf-xxxxxx.tar.gz
安装
$ tar xvzf sqlite-autoconf-3071502.tar.gz
$ cd sqlite-autoconf-3071502
$ ./configure --prefix=/usr/local
$ make
$ make install
```

##### 3、运行

```
$ cd CodeToServer/builed
$ cmake ..
$ make
$ ./scrs_app
```

#### 问题集

1.  #pragma pack(1) 导致map擦入没有对齐导致程序崩溃


#### 参考文档：

  1.Socket网络图片传输[https://www.cnblogs.com/zkfopen/p/9441797.html](https://www.cnblogs.com/zkfopen/p/9441797.html)

  2.linux下操作数据库（sqlite3）[https://blog.csdn.net/zouleideboke/article/details/73649886](https://blog.csdn.net/zouleideboke/article/details/73649886)

  3.JSON 数据在线解析[https://www.json.cn/](https://www.json.cn/)

  4.Git [https://hunya.fun/list/27](https://hunya.fun/list/27)

  5.C++ JSON 解析 [https://gitee.com/mirrors/jsoncpp?_from=gitee_search](https://gitee.com/mirrors/jsoncpp?_from=gitee_search)

  6.进一步熟悉Socket [https://blog.csdn.net/a_ran/article/details/44101065](https://blog.csdn.net/a_ran/article/details/44101065)



