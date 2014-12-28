#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "backup.h"

char * BackUpFile(char *n,char *file_buffer)
{
  struct stat st ;
  int filesize;
  FILE *fp;
  char c;
  printf("%s\n",n);
  fp = fopen(n,"r");
  if(fp==NULL)
  {
    fprintf(stderr,"Can't open Input File");
    exit(1);
  }
  stat(n,&st);
  filesize = st.st_size;
  file_buffer = (char *) malloc(sizeof(filesize)+5);
  do{
    static int i;
    c = fgetc(fp);
    file_buffer[i] = c;
    i++;
  
    }while(c!=EOF);
  //fclose(fp);
  return file_buffer;
}
