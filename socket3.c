#include "fileheader.h"
/*
connect:
 int connect(int sockfd, const struct sockaddr *serv_addr,
                   socklen_t addrlen);
const struct sockaddr *serv_addr:服务端地址结构
socklen_t addrlen:服务地址结构长度

*/
int main(int argc, char const *argv[])
{
    int clientfd=socket(AF_INET,SOCK_STREAM,0);
    //监听套接字
    if(clientfd==-1)
    {
    	perror("socket:");
    	exit(-1);
    }
    struct sockaddr_in seraddr;
    bzero(&seraddr,sizeof(seraddr));
    seraddr.sin_family=AF_INET;
    seraddr.sin_port=htons(PORT1);
    //seraddr.sin_addr.s_addr=INADDR_ANY;//使用一个有效的IP地址
	seraddr.sin_addr.s_addr=inet_addr("192.168.252.3");
	
	if(connect(clientfd,(struct sockaddr*)&seraddr,sizeof(seraddr))==-1)
	{
		perror("connect fail:");
		exit(-1);
	}

    printf("a1\n");
    char buf[1024];
    int len=recv(clientfd,buf,sizeof(buf)-1,0);
    buf[len]='\0';
     printf("a2\n");
    printf("recv:%s\n",buf);
	len=send(clientfd,"clientmsg",strlen("clientmsg"),0);
    printf("len=%d\n",len);
	return 0;
}