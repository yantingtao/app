#include "fileheader.h"
//实现wc功能  行数 字符数 
int main(int argc, char const *argv[])
{   
	 char b[1];
	 char d[1];
	char buf[256];
	int w=0;
	int c=0;
	int l=0;
	printf("请输入要查询的文本!\n");
	scanf("%s",buf);
	int fd=open(buf,O_RDWR);
	int fw=open(buf,O_RDWR);
	if(fd<0)
		{
			perror("open error!\n");
		}
   int ret=1;
   read(fw,d,sizeof(d));
   while(ret!=0)
   {
   	c++;
   	ret=read(fd,b,sizeof(b));
   	read(fw,d,sizeof(d));
    if((b[0]==' '&&d[0]!=' '&& d[0]!='\0') ||(b[0]=='\n' && d[0]!='\n'&&d[0]!=' '))
    {
      w++;
    }
    if(b[0]=='\n')
    {
    	l++;
    }
   }
   l--;
   c--;
   printf("行数是:%d\t字符数:%d\t单词数:%d\n",l,c,w);
	return 0;
}