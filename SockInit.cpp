/*
 * @description: 
 * @param: 
 * @return: 
 */
#include"SockInit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/sysinfo.h>
#include <sys/epoll.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>


SockInit::SockInit(){

}

SockInit::~SockInit(){

}

int SockInit::toinit(int port){

    struct sockaddr_in server_addr;
    int listen_fd;
    int on = 1;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    fcntl(listen_fd, F_SETFL, O_NONBLOCK);
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

printf("POST: %d\n",port);
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
       
        perror("erro 绑定失败 !!!");
        exit(1);
    }

    if (listen(listen_fd, 5) == -1) {
        perror(" error监听失败 !!! ");
        exit(1);
    }

    printf("Socket创建成功！！！  端口号： %d\n",port);
    return listen_fd;

}
