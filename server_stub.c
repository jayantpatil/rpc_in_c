#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char** tokenize_input(char* ,char**);
int work(int , char **,char*);

void error(char *msg)
{
  perror(msg);
  exit(1);
}

int main(int argc, char *argv[])
{
  int sockfd,portno,clilen,newsockfd,pid;
  struct sockaddr_in serv_addr, cli_addr;

  char *arr[4],*file_buffer ;
  //char path[30] = "/home/patil/dc_rpc/test.txt";
  if(argc<2)
    {
      fprintf(stderr," ERROR!! No Port Provided");
      exit(1);
    }

  sockfd = socket(AF_INET , SOCK_STREAM, 0);
  if(sockfd < 0)
    error("ERROR !! Could not open socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = atoi(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if(bind(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr))<0)
    error("ERROR!! on Binding");
  listen(sockfd , 5);
  printf("\nServer is listening for connections...\n");
  clilen = sizeof(cli_addr);
  while(1)
    {
      newsockfd = accept(sockfd,(struct sockaddr*) &cli_addr, &clilen);
      if(newsockfd < 0)
	error("ERROR !! on accept");
      pid = fork();
      if(pid<0)
	error("ERROR !! on fork");
      if(pid ==0)
	{
	  close(sockfd);
	  work(newsockfd,arr,file_buffer);
	  exit(0);
	}
      else close(newsockfd);
    }
  return 0;
}

int work(int sock,char *arr[], char *file_buffer)
{
  int n,i,x;
  char buffer[4096], *path,*temp,no_buf[10] ;
  bzero(buffer,4096);
  n = read(sock,buffer,4096);
  if (n<0) error("ERROR !! reading from socket");
  tokenize_input(buffer,arr);
  if((strcmp(arr[0],"add"))==0)
    {
      temp = malloc(sizeof(strlen("\nAddition = "))+10);
      x = atoi(arr[1])+atoi(arr[2]);
      snprintf(no_buf,10,"%d",x);
      strcpy(temp,no_buf);
      n= write(sock,temp,50);
    }
  else if((strcmp(arr[0],"mult"))==0)
    {
      temp = malloc(sizeof(strlen("\nProduct = "))+10);
      x = atoi(arr[1])*atoi(arr[2]);
      snprintf(no_buf,10,"%d",x);
      strcpy(temp,no_buf);
      n= write(sock,temp,50);
    }
  else if((strcmp(arr[0],"BackUpFile"))==0)
    {
      path =(char *) malloc(sizeof(strlen(arr[1]))+1);
      path = (char*) arr[1];
      file_buffer =(char*) BackUpFile(path,file_buffer);
      n= write(sock,file_buffer,strlen(file_buffer)+1);
    }
  else
    printf("\nService not Hosted by Server");
}

char** tokenize_input(char* str ,char *arr[])
{
  char *str_, *new_string, * cmd, *token ;
  int j;
  str_ = " ";
  while((token = strsep(&str,str_))!=NULL)
    {
      static i;
      arr[i] =malloc(strlen(token)+1);
      strcpy(arr[i],token);
      i++;
    }
}


