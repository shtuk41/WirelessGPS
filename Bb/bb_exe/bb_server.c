#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "bb.h"



void	HandleNMEARequests(int);
void	BBServerClose(int signum);

int 	master_sock, slave_sock;

void	bb_server()
{
	struct sockaddr_in remote_sin;
  
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
  
	if (bind(master_sock,(struct sockaddr *)&local_sin,sizeof(local_sin)) < 0)
	{
		printf("bind failed");
		exit(-1);
	}
	
	signal(SIGINT,BBServerClose);
	
	
   
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
	      
	      int pid = fork();
	      
	      if (pid < 0)
	      {
#ifdef PRINT_STATUS 
		printf("Server fork failed.  errno %i", errno);
#endif	      
	      }
	      else if (pid == 0)
	      {
			//child
			HandleNMEARequests(slave_sock);
	      }
	      else
	      {
			//parent
		waitpid(pid,0,WNOHANG);
	      }
	}
}

void	HandleNMEARequests(int slave_sock)
{
	int i;
	
	int iMaxSize = 20;
	char buffer[iMaxSize];
	char request[iMaxSize];
	char response[NMEA_SENTENCE_MAX_SIZE];
	
	int  iRIndex = 0;
	
	//GGA = 0.GLL,GSA,GSV,RMC,VTG
	int  iResponse = 0;
	

	while ((i = read(slave_sock,buffer,iMaxSize)) > 0)
	{
		int ii = 0;
	
		for (;ii < i; ii++)
		{
			putc(buffer[ii],stdout);
			if (buffer[ii] == '$')
			{
				iRIndex = 0;	
				request[iRIndex] = '$';
				iRIndex++;
			}
			else if (buffer[ii] == '\n')
			{
				request[iRIndex] = '\0';
				iRIndex++;
				
				if (!strncmp(request,"$GPGGA",6))
					iResponse = 0;
				else if (!strncmp(request,"$GPGLL",6))
					iResponse = 1;
				else if (!strncmp(request,"$GPGSA",6))
					iResponse = 2;
				else if (!strncmp(request,"$GPGSV",6))
					iResponse = 3;
				else if (!strncmp(request,"$GPRMC",6))
					iResponse = 4;
				else if (!strncmp(request,"$GPVTG",6))
					iResponse = 5;
					
				struct sembuf NMEATable_sembuf[1];
	
				NMEATable_sembuf[0].sem_num	= 0;
				NMEATable_sembuf[0].sem_op	= -1;
				NMEATable_sembuf[0].sem_flg	= SEM_UNDO;
	
	
				if (semop(iNMEATable_SemaphoreID,NMEATable_sembuf,1) < 0)
				{
					if (errno == EAGAIN)
					{
			#ifdef PRINT_STATUS 		
						printf("Resource is not available\n");
			#endif			
					}
					else
					{
			#ifdef PRINT_STATUS 		
						printf("semop error\n");
			#endif				
						exit(-1);
					}
				}
				else
				{
			#ifdef PRINT_SERVER 	
					printf("SERVER SEM ID is %d\n",iNMEATable_SemaphoreID);
					
					if (iResponse == 0)
					printf("GGA: %s\n",((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GGA);
					else if (iResponse == 1)
					printf("GLL: %s\n",((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GLL);
					else if (iResponse == 2)
					printf("GSA: %s\n",((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GSA);
					else if (iResponse == 3)
					printf("GSV: %s\n",((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GSV);
					else if (iResponse == 4)
					printf("RMC: %s\n",((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->RMC);
					else if (iResponse == 5)
					printf("VTG: %s\n",((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->VTG);
			#endif	
					
					memset(response,'\0',NMEA_SENTENCE_MAX_SIZE);
					switch(iResponse)
					{
						case 0:
							strncpy(response,((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GGA,NMEA_SENTENCE_MAX_SIZE-1);
							break;
						case 1:
							strncpy(response,((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GLL,NMEA_SENTENCE_MAX_SIZE-1);
							break;
						case 2:
							strncpy(response,((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GSA,NMEA_SENTENCE_MAX_SIZE-1);
							break;
						case 3:
							strncpy(response,((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GSV,NMEA_SENTENCE_MAX_SIZE-1);
							break;
						case 4:
							strncpy(response,((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->RMC,NMEA_SENTENCE_MAX_SIZE-1);
							break;
						case 5:
							strncpy(response,((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->VTG,NMEA_SENTENCE_MAX_SIZE-1);
							break;
					}
		
		
					NMEATable_sembuf[0].sem_num	= 0;
					NMEATable_sembuf[0].sem_op	= 1;
					NMEATable_sembuf[0].sem_flg	= IPC_NOWAIT | SEM_UNDO;	
	
					if (semop(iNMEATable_SemaphoreID,NMEATable_sembuf,1) < 0)
					{
				#ifdef PRINT_STATUS 	
						printf("semop error\n");
				#endif		
						exit(-1);
					}
		  
                                        int iLeft = strlen(response);
					int iCurrent = 0;

					while (iLeft > 0)
					{
					    int n = 0;
					    if ((n = write(slave_sock,&response[iCurrent],iLeft)) <= 0)
					    {
				#ifdef PRINT_STATUS
                                              if (errno == EINTR)
						      printf("EINTR\n");
					      else
						      printf("Something else on write\n");
				 #endif	    
					    }
                                            iLeft-=n;
					    iCurrent+=n;
					}	
				}
					
			}
			else
			{
				request[iRIndex] = buffer[ii];
				iRIndex++;
			}
		}
	}
}

void	BBServerClose(int signum)
{
	shutdown(master_sock, SHUT_RDWR);
	shutdown(slave_sock, SHUT_RDWR);
	exit(0);
}
