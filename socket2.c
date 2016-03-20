#include "fileheader.h"
/*tcp编程:
a.服务端
b.客户端

套接字:socket 是通信网络中一个终点,可以与其它任意点通信.
实际上是一个类似于文件描述值描述值(表示此通信点)
socket=ip+port+tcp/udp 实现进程(同一台主机上,不同的主机)通信
tcp套接字编程步骤:
见参考图

创建套接字:
int socket(int domain, int type, int protocol);
int domain:域 常用值:
 PF_UNIX, PF_LOCAL(AF_UNIX AF_LOCAL):实现本地进程通信
 PF_INET(AF_INET): IPV4
 PF_INET6(AF_INET6):IPV6

 int type:
 SOCK_STREAM:tcp传输协议
 SOCK_DGRAM:UDP传输协议
 SOCK_RAW:原始协议

int protocol:特定协议,一般为0
返回值:=-1:失败 error

设置地址结构(ip地址 port)
struct sockaddr_in
struct sockaddr_in {
   sa_family_t		sin_family;	//地址家族(AF_INET,AF_INET6)
   __be16		 sin_port;	//端口值 一般 >1024
  struct in_addr	sin_addr;	//ip地址
  unsigned char		__pad[__SOCK_SIZE__ - sizeof(short int) -
			sizeof(unsigned short int) - sizeof(struct in_addr)];
			//填充作用
};

struct in_addr {
	__be32	s_addr;
};

主机网络字节转换(存在大小端模式)
 uint32_t htonl(uint32_t hostlong);
 uint16_t htons(uint16_t hostshort);
 uint32_t ntohl(uint32_t netlong);
 uint16_t ntohs(uint16_t netshort);
 h:host  n:internet s:short  l:long
 //设置端口值网络地址 必须要转换

 地址格式转换函数:
int inet_aton(const char *cp, struct in_addr *inp);
in_addr_t inet_addr(const char *cp);
in_addr_t inet_network(const char *cp);
char *inet_ntoa(struct in_addr in);
struct in_addr inet_makeaddr(int net, int host);
in_addr_t inet_lnaof(struct in_addr in);
in_addr_t inet_netof(struct in_addr in);

绑定
int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
const struct sockaddr *my_addr:

struct sockaddr {
	sa_family_t	sa_family;	
	char		sa_data[14];	
};
监听
int listen(int sockfd, int backlog)
int backlog:监听队列的最大值
/proc/sys/net/ipv4/max_syn_backlog 记录值
/proc/sys/net/ipv4  记录网络配置值

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int sockfd:监听套接字
 struct sockaddr *addr:指向存储客户端地址
 socklen_t *addrlen:指向长度
 返回值:是一个整数,表示请求成功客户在服务都表示值,代表该客户,
 后续通信都用该值

发送函数:
send:
ssize_t send(int s, const void *buf, size_t len, int flags)
int s:accpet返回值
返回值:ssize_t >0:实际发送字节数
发送/接收缓存区大小:
net.ipv4.tcp_wmem = 4096    
net.ipv4.tcp_rmem = 4096  
参考 发送 接收 原理文档




*/
int main(int argc, char const *argv[])
{
    int socket1=socket(AF_INET,SOCK_STREAM,0);
    //监听套接字
    if(socket1==-1)
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
	//seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");//只能实现本地通信
	if(bind(socket1,(struct sockaddr*)&seraddr,sizeof(seraddr))==1)
	{
		perror("bind fail:");
		exit(-1);
	}

    if(listen(socket1,10)==-1)//套接字 LISTENT状态
    {
    	perror("listen fail:");
    	exit(-1);
    }
    struct sockaddr_in clientaddr;
    int addrlen;
    //堵塞 accpt返回
    int clientfd=accept(socket1,(struct sockaddr*)&clientaddr,&addrlen);
    if(clientfd==-1)
    {
    	perror("accpet fail:");
      	exit(-1);
    }


   // 记录的客户标示值

    int len=send(clientfd,"helloworld",strlen("helloworld"),0);
   printf("len=%d\n",len);
    char buf[1024];
    len=recv(clientfd,buf,sizeof(buf)-1,0);
   buf[len]='\0';
    printf("recv:%s\n",buf);
    
	return 0;
}