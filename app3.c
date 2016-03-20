
#include "fileheader.h"
/*
实现匿名管道全双工模式
*/
int main(int argc, char const *argv[])
{
	int fd[2];
	int ret=pipe(fd);
	if(ret==-1)
	{
		perror("pipe:");
		return;
	}

	int fd2[2];
	ret=pipe(fd2);
	if(ret==-1)
	{
		perror("pipe:");
		return;
	}

	pid_t pid=fork();
	if(pid<0)
	{
		perror("fork:");
		return;
	}

	if(pid==0)
	{
       close(fd[0]);//子进程关闭读端
       close(fd2[1]);
       char  buf[1024];
       gets(buf);
       write(fd[1],buf,strlen(buf));
       bzero(buf,sizeof(buf));
       read(fd2[0],buf,sizeof(buf)-1);
        for(i=0;i<strlen(buf);i++)
       {
       	   if(buf[i]>='a'&&buf[i]<='z')
       	   {
       	   	 buf[i]-=32;
       	   }
       }
       close(fd[1]);
       close(fd2[0]);
    }
	if(pid>0)
	{
       close(fd[1]);//父进程关闭写端
       close(fd2[0]);
       char buf[1024];
       int len=read(fd[0],buf,sizeof(buf)-1);
       buf[len]='\0';
       printf("%s\n",buf);
       bzero(buf,sizeof(buf));
       gets(buf);
       write(fd2[1],buf,strlen(buf));
       close(fd[0]);
       close(fd2[1]);
       wait(NULL);//子进程可能是一个僵死进程
	}
	return 0;
}