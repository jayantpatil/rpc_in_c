#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include "client_stub.h"

int main(int argc, char *argv[])
{
  int ch,n;
  clock_t s , e,elapse;
  FILE *fp;
  char *result,temp[1024],*fst, *snd;
  do{
    result = (char *)malloc(4096);
    printf("\n1. Addition\n2. Multiplication \n3.Take Backup of File\n4.Exit\n");
    scanf("%d",&ch);
    switch(ch)
      {
      case 1:
	fst =(char *) malloc(6);
	snd =(char *) malloc(6);
	printf("Enter First no.");
	scanf("%s",fst);
	printf("Enter Second no.");
	scanf("%s",snd);
	strcpy(temp ,"add");
	strcat(temp," ");
	strcat(temp,fst);
	strcat(temp," ");
	strcat(temp,snd);
	s = clock();
	result =(char *) make_request(temp);
	e = clock();
	elapse = (e -s) * CLOCKS_PER_SEC;
	printf("Time Elapsed = %lu\n",elapse);
	printf("Addition = %s\n",result);
	break;
      case 2:
	fst =(char *) malloc(6);
	snd =(char *) malloc(6);
	printf("Enter First no.");
	scanf("%s",fst);
	printf("Enter Second no.");
	scanf("%s",snd);
	strcpy(temp ,"mult");
	strcat(temp," ");
	strcat(temp,fst);
	strcat(temp," ");
	strcat(temp,snd);
	s = clock();
	result =(char *) make_request(temp);
	e = clock();
	elapse = (e -s) * CLOCKS_PER_SEC;
	printf("Time Elapsed = %lu\n",elapse);
	printf("Product = %s\n",result);
	break;
      case 3:
	fst =(char *) malloc(100);
	snd =(char *) malloc(100);
	printf("Enter Filepath on server\n");
	scanf("%s",fst);
	printf("Enter filepath to store backup file\n");
	scanf("%s",snd);
	strcpy(temp ,"BackUpFile");
	strcat(temp," ");
	strcat(temp,fst);
	s = clock();
	result =(char *) make_request(temp);
	e = clock();
	elapse = (e -s) * CLOCKS_PER_SEC;
	printf("Time Elapsed = %lu\n",elapse);
	fp = fopen(snd,"w");
	if(fp==NULL)
	  {
	    fprintf(stderr,"Can't open Input File");
	    exit(1);
	  }
	
	n=fprintf(fp,"%s",result);
	if(n<0)
	  printf("\nUnable to Write in File at local Machine\n");
	else
	  printf("\nBackup Successful\n");
	fclose(fp);
	break;
      case 4:
	exit(0);
      default:
	printf("\nInvalid Choice\n");
      }
  }while(ch!=4);
  return 0;
}
