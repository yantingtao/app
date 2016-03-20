#include "fileheader.h"
typedef struct 
{
	int num;
}data;
void sort(data date[],int num)
{
	int i,j;
	data tmp;
		for(i=0;i<num;i++)
	{
		for(j=i;j<num-i-1;j++)
		{  
            if(date[i].num>date[j].num)
            {
            	tmp=date[i];
            	date[i]=date[j];
            	date[j]=tmp;
            }
		}
	}
}
int main(int argc, char const *argv[])
{    
	 int i,j;
	data buf[128];
	int n;
	int len;
	printf("请输入要排序多少个数?\n");
    scanf("%d",&n);
	int fd=open("app10.dat",O_CREAT|O_EXCL|O_APPEND|O_RDWR,0777);
	    if(fd<=0)
    {
        if(errno==EEXIST)
        {
             fd=open("app10.dat",O_RDWR);
        }
        else
        {
            perror("open:");
            exit(-1);
        }
    }
         
     for(i=0;i<n;i++)
     {
         scanf("%d",&buf[i].num);
     } 
    write(fd,buf,sizeof(buf));
    len=lseek(fd,0,SEEK_END);
    data * addr=(data *)mmap(NULL,len,PROT_WRITE |PROT_READ,MAP_SHARED,fd,0);
     if(addr==NULL)
    {
        perror("mmap fail:");
        return;
    }
	close(fd);
    sort(addr,n);
    for(i=0;i<n;i++)
    {
    	printf("%d\n",addr[i].num);
    }
	return 0;
}