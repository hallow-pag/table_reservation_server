#include "ClieResponse.h"
#include "ProcessDataCli.h"

ClieResponse::ClieResponse(int FD) { 
  
  listen_fd = FD;
  Clie = new ProcessDataCli;
  
   }
ClieResponse::~ClieResponse() {
  delete Clie;
}

void ClieResponse::process() {
  int conn_fd;
  int ready_fd_num;
  struct sockaddr_in client_addr;
  socklen_t client_addr_size = sizeof(client_addr);
  char buf[128];

  struct epoll_event ev, events[MAX_EVENT_NUM];
  int epoll_fd = epoll_create(MAX_EVENT_NUM);
  ev.data.fd = listen_fd;
  ev.events = EPOLLIN;

  if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &ev) == -1) {
    perror("epoll_ctl error, message: ");
    exit(1);
  }

  while (1) {
    ready_fd_num = epoll_wait(epoll_fd, events, MAX_EVENT_NUM, INFTIM);
    printf("[pid %d] 被唤醒了...\n", getpid());
    if (ready_fd_num == -1) {
      perror("epoll_wait error, message: ");
      continue;
    }
    for (int i = 0; i < ready_fd_num; i++) {
      if (events[i].data.fd == listen_fd) {
        conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                         &client_addr_size);
        if (conn_fd == -1) {
          sprintf(buf, "[pid %d] accept 出错: ", getpid());
          perror(buf);
          continue;
        }
        if (fcntl(conn_fd, F_SETFL, fcntl(conn_fd, F_GETFD, 0) | O_NONBLOCK) ==
            -1) {
          continue;
        }
        ev.data.fd = conn_fd;
        ev.events = EPOLLIN;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev) == -1) {
          perror("epoll_ctl error, message: ");
          close(conn_fd);
        }
        printf("[pid %d] 收到来自 %s:%d 的请求\n", getpid(),
               inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
      } else if (events[i].events & EPOLLIN) {
      conn_fd = events[i].data.fd;

         //开始处理 消息
         Clie->responses_init(conn_fd,inet_ntoa(client_addr.sin_addr));  //初始化
         Clie->accept_request();

        close(conn_fd);
      } else if (events[i].events & EPOLLERR) {
        fprintf(stderr, "epoll error\n");
        close(conn_fd);
      }
    }
  }
}

int ClieResponse::getfd(){
  return listen_fd;
}