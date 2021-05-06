#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
void delay(unsigned int xms)  // xms代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=110;y>0;y--);
}
int64_t now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL); // 获取当前精确时间
    return tv.tv_sec * 1000000 + tv.tv_usec;
}
int main(int argc, char *argv[])
{
	double   duration;	/*  记录被测函数运行时间，以秒为单位  */
	unsigned short port = 8888;             // 服务器的端口号
  int sum;
	char *server_ip ="127.0.0.1";    	// 服务器ip地址
	if( argc > 1 ){	        //函数传参，可以更改服务器地址
		server_ip = argv[1];
	}
	if( argc > 2 ){	       //函数传参，可以更改服务器端口号
		port = atoi(argv[2]);
	}
  if( argc > 3 ){        //运行多少次
    sum = atoi(argv[3]);
  }
	struct timeval tv;
	int sockfd;             //定义套接字连接
  int n=0;
  int64_t start = now();//开始计时
	while(n<=sum){
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);// 创建通信端点：套接字
    	if(sockfd < 0) {       //套接字连接失败
    		perror("socket");
    		exit(-1);
    	}
    	struct sockaddr_in server_addr;
    	bzero(&server_addr,sizeof(server_addr)); // 初始化服务器地址
    	server_addr.sin_family = AF_INET;	// IPv4
    	server_addr.sin_port = htons(port);	// 端口
    	inet_pton(AF_INET, server_ip, &server_addr.sin_addr.s_addr);	// ip
    	int err_log = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    	if(err_log != 0){                       //服务器连接失败
    		perror("connect");
    		close(sockfd);
    		exit(-1);
    	}
    	int recv_len = 0;                      //缓冲区长度
      char recv_buf[512] = {0};              //定义要接收数据
    	printf("send data to %s:%d\n",server_ip,port);  //打印数据发送服务器
    	printf("**************************************************\n");
    	{
    		printf("--------------------------%d\n",n);
    		{
    			if(n%4==0||n%4==3){
    				char send_buf[512]= "GET /index.html HTTP/1.1\r\nUser-Agent: curl/7.22.0 (i686-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\nHost:127.0.0.1:8888\r\nAccept: */*\r\n\r\n";
    				printf("send_buf: %s\n", send_buf);
    				send(sockfd, send_buf, strlen(send_buf), 0);   // 向服务器发送信息
    	      if(recv_len = recv(sockfd, recv_buf, sizeof(recv_buf), 0)>0)
    				{
    					printf("***recv_buf: %s\n", recv_buf); // 打印接收的数据
    				}
    			}
    			else if(n%4==1){
            char send_buf[512]= "DELETE /index.html HTTP/1.1\r\nUser-Agent: curl/7.22.0 (i686-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\nHost:127.0.0.1:8888\r\nAccept: */*\r\n\r\n ";
    				printf("send_buf: %s\n", send_buf);
    				send(sockfd, send_buf, strlen(send_buf), 0);   // 向服务器发送信息
    				if(recv_len = recv(sockfd, recv_buf, sizeof(recv_buf), 0)>0)
    				{
    					printf("***recv_buf: %s\n", recv_buf); // 打印接收的数据
    				}
    			}
    			else if(n%4==2){
    				char send_buf[512]= "PUT /index.html HTTP/1.1\r\nUser-Agent: curl/7.22.0 (i686-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\nHost:127.0.0.1:8888\r\nAccept: */*\r\n\r\n";
    				printf("send_buf: %s\n", send_buf);
    				send(sockfd, send_buf, strlen(send_buf), 0);   // 向服务器发送信息
    				if(recv_len = recv(sockfd, recv_buf, sizeof(recv_buf), 0)>0)
    				{
    					printf("***recv_buf: %s\n", recv_buf); // 打印接收的数据
    				}
    			}
          // else if(n%4==3){
          //   char send_buf[512]= "POST /Post_show HTTP/1.1\r\nUser-Agent: curl/7.22.0 (i686-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\nHost: 127.0.0.1:8888\r\nAccept: */*\r\nContent-Length: 19\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n Name=Tzp&ID=000111";
          // //  printf("send_buf: %s\n", send_buf);
          //   //char send_buf[512]= "curl -i -X POST --data 'Name=Tzp&ID=201808010404' 127.0.0.1:8888/Post_show";
          //   //char send_buf[512]= "POST /Post_show/Name=NHU&ID=CSD HTTP/1.1\r\nUser-Agent: curl/7.22.0 (i686-pc-linux-gnu) libcurl/7.22.0 OpenSSL/1.0.1 zlib/1.2.3.4 libidn/1.23 librtmp/2.3\r\nHost: 127.0.0.1:8888\r\nAccept: */*\r\nContent-Length: 19\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n";
          //   printf("send_buf: %s\n", send_buf);
          //   send(sockfd, send_buf, strlen(send_buf), 0);   // 向服务器发送信息
          //   if(recv_len = recv(sockfd, recv_buf, sizeof(recv_buf), 0)>0)
          //   {
          //     printf("***recv_buf: %s\n", recv_buf); // 打印接收的数据
          //   }
          // }
    			n++;
    		}
    	}
    	close(sockfd);
    }
  int64_t end = now();//停止计时
  double sec = (end - start) / 1000000.0;
  printf("耗时sec= %.2f 秒\n", sec);
	return 0;
}
