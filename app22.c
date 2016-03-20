#include "fileheader.h"
int main(int argc, char const *argv[])
{
	pid_t pid=fork();
	 char buf[1024];
      char bdf[1024];
      int i;
	int fd=open("/tmp/fifo1",O_CREAT|O_EXCL|O_RDWR|O_APPEND,0744);
      if(fd=-1)
      {

		if(errno==EEXIST)
		{
			fd=open("/tmp/fifo1",O_RDWR|O_APPEND);
		}
		else
		{
			 	perror("mkfifo:");
		}
      }
     int fw=open("/tmp/fifo2",O_CREAT|O_EXCL|O_RDWR|O_APPEND,0744);
      if(fw==-1)
      {

		if(errno==EEXIST)
		{
			fw=open("/tmp/fifo2",O_RDWR|O_APPEND);
		}
		else
		{
			 	perror("mkfifo:");
		}
      }
	if(pid<0)
	{
		perror("fork:");
	}
	if(pid>0)
	{
      
       while(1)
      {
      	gets(buf);
      	// if(buf=="exit")
      	// {
      	// 	break;
      	// }
		flock(fd,LOCK_EX);
	    int ret= write(fd,buf,strlen(buf));
	    printf("input length=%d\n",ret);
	    flock(fd,LOCK_UN);
	     sleep(3);
	    bzero(bdf,sizeof(bdf));		
		flock(fw,LOCK_EX);
	    ret=read(fw,bdf,sizeof(bdf)-2);
	    flock(fw,LOCK_UN);
	    printf("%s\n",bdf);
	    printf("output length=%d\n",ret);
      }
      
	}
	if(pid==0)
	{
	while(1)
	  { 
	  	sleep(3);
        bzero(buf,sizeof(buf));		
		flock(fd,LOCK_EX);
	    read(fd,buf,sizeof(buf)-1);
	    flock(fd,LOCK_UN);
	    for(i=0;i<strlen(buf);i++)
	    {
	    	if(buf[i]>='a' && buf[i]<='z')
	    	{
	    		bdf[i]=buf[i]-32;
	    	}
	    	else
	    	{
	    		bdf[i]=buf[i];
	    	}
	    }
	    flock(fw,LOCK_EX);
	    int  ret= write(fw,bdf,strlen(bdf));
	   // printf("son input length=%d\n",ret);
	    flock(fw,LOCK_UN);	
	  }
	}
	   close(fw);
       close(fd);
	return 0;
}
