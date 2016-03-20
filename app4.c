#include "fileheader.h"
void cp1(char filename1[],char filename2[])//cp文件
{
    char c[1];
	int fd=open(filename1,O_RDWR);
	int fw=open(filename2,O_CREAT|O_EXCL|O_RDWR,0744);
	if(fd<0)
	{
		perror("文件不存在\n");
	}
	if(fw<0)
	{
		if(errno==EEXIST)
		{
			fw=open(filename2,O_RDWR);
		}
		else
		{
			perror("open error");
		}
	}
    int ret=1;
    while(ret!=0)
    {
    	ret=read(fd,c,sizeof(c));
    	write(fw,c,sizeof(c));
    }
    close(fd);
    close(fw);

}

void cp3(char filename2[],int num,char c[])
{ 
 if(num==1)
  {
	 if(strcmp(filename2,"..")!=0)
	{
      mkdir(filename2,0744);
	}
	else
	{
		chdir("..");
	}  
  }
  if(num==2)
  {
     int fd=open(filename2,O_CREAT|O_EXCL|O_APPEND|O_RDWR,0744);
     if(fd<0)
     {
     	if(errno==EEXIST)
		{
			fd=open(filename2,O_APPEND|O_RDWR);
		}
		else
		{
			perror("open error");
		}
     }
     write(fd,c,sizeof(c));
     close(fd);
  }
}
void cp2(char filename1[],char filename2[])
{   
	 char path2[256];
	 char path1[256];
	 strcat(path2,filename2);
	 strcat(path1,filename1);
	 DIR* dir=opendir(filename1);
	 chdir(filename1);
    if(dir!=NULL)
	{     
		  struct dirent *ent=NULL;
          struct stat buf;
          ent=readdir(dir);
		 while(ent!=NULL)
		 {    
             if(strcmp(ent->d_name,".")!=0 && strcmp(ent->d_name,"..")!=0)
		 	 {  
		 	 	 	stat(ent->d_name,&buf);
		 	 	   if(S_ISDIR(buf.st_mode))
		 	 	   {
                     chdir(path2);
                     cp3(ent->d_name,1,0);
                     strcat(path2,"/");
                     strcat(path2,ent->d_name);
                     chdir(path1);
                     strcat(path1,"/");
                     strcat(path1,ent->d_name);
		 	 	   	 cp2(ent->d_name,NULL);
		 	 	     
		 	 	   }
		 	 	   else
		 	 	   {  
		 	 	   	  char c[1];
		 	 	   	  int fd=open(ent->d_name,O_RDWR);
		 	 	   	  int ret=1;
		 	 	   	  while(ret!=0)
		 	 	   	 { 
		 	 	   	  ret=read(fd,c,sizeof(c));
		 	 	   	  chdir(path2);
                      cp3(ent->d_name,2,c);
		 	 	   	}
		 	 	    close(fd);
		 	 	   }
              }
              ent=readdir(dir);
		 }
		  chdir("..");
		  cp3("..",1,0);
	}
}
int main(int argc, char const *argv[])
{   
	int n;
    printf("复制文件还是目录? 文件输入:1  目录输入:2\n");
    scanf("%d",&n);
    if(n==1)
    {
    char filename1[128];
	char filename2[128];
	printf("请输入你想复制的文件名!\n");
	scanf("%s",&filename1);
	printf("请输入你复制后的文件名!\n");
	scanf("%s",&filename2);
	cp1(filename1,filename2);
    }
    else if(n==2)
    {
    char filename1[128];
	char filename2[128];
	printf("请输入你想复制的目录名!\n");
	scanf("%s",&filename1);
	printf("请输入你复制后的目录名!\n");
	scanf("%s",&filename2);
	cp3(filename2,1,0);
	cp2(filename1,filename2);
    }
    else
    {
    	printf("输入有误 请重新运行后输入\n");
    }
    
   
	return 0;
}
