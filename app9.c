#include "fileheader.h"
int main(int argc, char const *argv[])
{
	 char filename1[128];
	char filename2[128];
	printf("请输入你想复制的文件名!\n");
	scanf("%s",&filename1);
	printf("请输入你复制后的文件名!\n");
	scanf("%s",&filename2);
    int fd=open(filename1,O_RDWR);
     if(fd<0)
    {
    	perror("fd error");
    }
     int len=lseek(fd,0,SEEK_END);
    char * addr1=(char*)mmap(NULL,len,PROT_WRITE |PROT_READ,MAP_PRIVATE,fd,0);
     if(addr1==NULL)
    {
        perror("mmap fail:");
        return;
    }
     close(fd);
    int fw=open(filename2,O_CREAT|O_EXCL|O_APPEND|O_RDWR,0744);
    if(fw<0)
    {
    	if(errno==EEXIST)
		{
			fw=open(filename2,O_APPEND|O_RDWR);
		}
		else
		{
			perror("open error");
		}
    }
    ftruncate(fw,len);// int ftruncate(int fd, off_t length);指定文件大小
    char * addr2=(char *)mmap(NULL,len,PROT_WRITE |PROT_READ,MAP_SHARED,fw,0);
    if(addr2==NULL)
    {
        perror("mmap fail:");
        return;
    }
    close(fw);
    memcpy(addr2,addr1,len);
    munmap(addr1,len);
    munmap(addr2,len);
	return 0;
}
