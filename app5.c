#include "fileheader.h"
//linux 目录树深度  117
int main(int argc, char const *argv[])
{   int n=1;
	int ret=mkdir("a",0744);
	while(ret==0)
	{
      chdir("a");
      ret=mkdir("a",0744);
      n++;
	}
	printf("%d\n",n);
	return 0;
}