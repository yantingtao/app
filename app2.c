#include "fileheader.h"
int main(int argc, char const *argv[])
{ 		int fd[2];
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
	int i;
	if(pid==0)
	{  
       close(fd[1]);//父进程写端关闭
       close(fd2[0]);//父进程读端关闭
       while(1)
       {
       	char  buf[1024];
       int len=read(fd[0],buf,sizeof(buf)-1);
        if(strcmp(buf,"bye")==0)
       {
       	break;
       }
       buf[len]='\0';
       for(i=0;i<strlen(buf);i++)
       {
       	   if(buf[i]>='a'&&buf[i]<='z')
       	   {
       	   	 buf[i]-=32;
       	   }
       }
       write(fd2[1],buf,strlen(buf));
       }
       close(fd[0]);
       close(fd2[1]);
    }
	if(pid>0)
	{   
       close(fd[0]);//关闭子进程读端
       close(fd2[1]);//关闭子进程写端
      while(1)
      {
      	   char buf[1024];
       bzero(buf,sizeof(buf));
       gets(buf);
       write(fd[1],buf,strlen(buf));
       if(strcmp(buf,"bye")==0)
       {
       	break;
       }
       bzero(buf,sizeof(buf));
       read(fd2[0],buf,sizeof(buf)-1);
       printf("%s\n",buf);
      }
       close(fd[1]);//关闭父进程写端
       close(fd2[0]);//关闭父进程读端
       wait(NULL);//子进程可能是一个僵死进程
	}
	return 0;
}
