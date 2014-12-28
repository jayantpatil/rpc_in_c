#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

char* make_request(char*);

void error(char *msg)
{
  perror(msg);
  exit(0);
}

char* make_request(char* a)
{
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[4096],*reply,*buffer1 ;
  portno =5000;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd<0)
    error("ERROR !! Opening Socket");
  server = gethostbyname("localhost");
  if(server == NULL)
    {
      fprintf(stderr,"ERROR !! no such host \n");
      exit(0);
    }
  bzero((char*) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family =AF_INET;
  bcopy((char *) server->h_addr,(char*)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0)
    error("ERROR !! Connecting");
  bzero(buffer,4096);
  strcpy(buffer,a);
  n= write(sockfd,buffer,strlen(buffer));
  if(n<0)
    error("ERROR !! writing to socket");
  reply = (char *)malloc(4096);
  bzero(reply,4096);
  n =  read(sockfd , reply,4096);
  return reply;
}
