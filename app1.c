#include "fileheader.h"
int main(int argc, char const *argv[])
{
	pid_t pid=fork();
	if(pid>0)
	{
		
		printf("grandparent process:%d\n",getpid());
	     int  status;
        pid_t id=wait(NULL);
        if(WIFEXITED(status))
        {
        	printf("status=%d\n",WEXITSTATUS(status));
        }
	}
	if(pid==0)
	{
		pid_t pid=fork();
		if(pid>0)
		{
			sleep(5);
            printf("parent process:%d\n",getpid());
            exit(12);
		}
		if(pid==0)
		{   
			sleep(1);
            printf("son process1:%d\n",getpid());
            sleep(6);
            printf("son process2:%d\n",getpid());
		}
		
		if(pid<0)
		{
           perror("fork2 :");
           exit(0);
		}
	}
	if(pid<0)
	{
		perror("fork1 :");
		exit(0);
	}
	return 0;
}