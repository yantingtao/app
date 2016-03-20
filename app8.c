#include "fileheader.h"
void  readdirs(char *name)
{
      DIR* dir=opendir(name);
      chdir(name);
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
                        printf("%s\n",ent->d_name);
                        readdirs(ent->d_name);
                    }
                    else
                    {
                        printf("\t\t%s\n",ent->d_name);
                    }
                }
                ent=readdir(dir);
          }
          chdir("..");
      }
}
int main(int argc, char const *argv[])
{
   readdirs("app4");
  return 0;
}