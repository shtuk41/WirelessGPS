#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
  struct sockaddr_in remote_sin;
  
  int 	master_sock, slave_sock;
  
  struct sockaddr_in local_sin;
  
  memset(&local_sin,0,sizeof(local_sin));
  
  local_sin.sin_family = AF_INET;
  local_sin.sin_addr.s_addr = INADDR_ANY;
  local_sin.sin_port = 20000;
  
  master_sock = socket(PF_INET,SOCK_STREAM,0);
  
  if (master_sock < 0)
  {
      printf("master socket failed\n");
      exit(-1);
  }
  
  if (bind(master_sock,(struct sockaddr_in *)&local_sin,sizeof(local_sin)) < 0)
  {
      printf("bind failed");
      exit(-1);
   }
   
   if (listen(master_sock,10) < 0)
   {
     printf("listen failed\n");
     exit(-1);
   }
   
   while (1)
   {
      unsigned length = sizeof (remote_sin);
      
      slave_sock = accept(master_sock,(struct sockaddr *)&remote_sin, &length);
      
      if (slave_sock < 0)
      {
	  printf("accept failed\n");
	  exit(-1);
      }
      
      char *response = "response OK\n";
      
      write(slave_sock,response,strlen(response));
   }
   
   exit(0);
    
}