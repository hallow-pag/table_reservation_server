#include "HttpResponse.h"
#include "ProcessDataWx.h"

HttpResponse::HttpResponse(int FD) { 
  
  listen_fd = FD;
  WixoutIn = new ProcessDataWx;
  
   }
HttpResponse::~HttpResponse() {
  delete WixoutIn;
}

void HttpResponse::process() {
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
    printf("[pid %d] 😱 震惊！我又被唤醒了...\n", getpid());
    if (ready_fd_num == -1) {
      perror("epoll_wait error, message: ");
      continue;
    }
    for (int i = 0; i < ready_fd_num; i++) {
      if (events[i].data.fd == listen_fd) {
        conn_fd = accept(listen_fd, (struct sockaddr *)&client_addr,
                         &client_addr_size);
        if (conn_fd == -1) {
          sprintf(buf, "[pid %d] ❌ accept 出错了: ", getpid());
          perror(buf);
          continue;
        }

          //设置为非阻塞 O_NONBLOCK
        if (fcntl(conn_fd, F_SETFL, fcntl(conn_fd, F_GETFD, 0) | O_NONBLOCK) == -1) { 
          continue;
        }

        ev.data.fd = conn_fd;
        ev.events = EPOLLIN;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, conn_fd, &ev) == -1) {
          perror("epoll_ctl error, message: ");
          close(conn_fd);
        }
        printf("[pid %d] 📡 收到来自 %s:%d 的请求\n", getpid(),
               inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
      } else if (events[i].events & EPOLLIN) {
      conn_fd = events[i].data.fd;

         //开始处理 消息
         WixoutIn->responses_init(conn_fd,inet_ntoa(client_addr.sin_addr));  //初始化
         WixoutIn->accept_request();

  #if 0
  {
    char Bs[1024];
  //---------服务器收到的数据
  read(conn_fd, Bs, sizeof(Bs));
  printf("---\n%s\n---\n\n---\n", Bs);
  ///-------------------
  char response[1024];
  sprintf(response, "HTTP/1.1 200 OK \r\nContent-Type: text/plain; "
                    "charset=utf-8\r\n\r\n{\"data\":\" 这是返回数据\"}");
  write(conn_fd, response, strlen(response));
  ///--------------------
  // accept_request(conn_fd, &client_addr);
  }
       #endif 
        close(conn_fd);
      } else if (events[i].events & EPOLLERR) {
        fprintf(stderr, "epoll error\n");
        close(conn_fd);
      }
    }
  }
}

int HttpResponse::getfd(){
  return listen_fd;
}