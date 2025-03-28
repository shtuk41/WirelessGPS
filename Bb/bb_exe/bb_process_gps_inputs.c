
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

#include "bb.h"

int tty_fd;

void UpdateNMEATable(char *sentence);
void bb_process_gps_inputs_close(int signum);


/******************************************************************************

	Name:		bb_process_gps_inputs()
	Description:	This function processes inputs from LS2000031 and sets 
			NMEA_SENTENCE_TABLE
	Input:		none
	Return:		none
	Date:		04.28.2013

********************************************************************************/




void bb_process_gps_inputs()
{
	tty_fd = open("/dev/ttyO1",O_RDWR | O_NOCTTY);
  
  if (tty_fd < 0)
  {
#ifdef PRINT_STATUS 
      printf("Can't find or open device /dev/ttyS1");
#endif      
      exit(-1);
  }
  
  signal(SIGINT, bb_process_gps_inputs_close);
  
  struct termios ttys1_termios;
  
 if (tcgetattr(tty_fd,&ttys1_termios)!= 0)
 {
#ifdef PRINT_STATUS  
	printf("Error getting attr ");
#endif	
	exit(-1);
 } 


  
  //INPUT FLAGS
  //IGNPAR 	- ingore bytes with parity errors
  //ICRNL  	- map CR to NL
    ttys1_termios.c_iflag = 0;//IGNPAR | ICRNL;
    
  // OUTPUT FLAGS   
    //OCRNL 	- map CR to NL on output
    //ttys1_termios.c_oflag = OCRNL;
    
    //CONTROL FLAGS
    //CS8 	- 8n1 8 bit, no parity, 1 stop bit
    //CLOCAL 	- ingore modem status lines
    //CREAD  	- enable receiving characaters

    //cfsetispeed(&ttys1_termios,B56000);
    //cfsetospeed(&ttys1_termios,B57600);
    ttys1_termios.c_cflag =  B57600 | CS8 | CLOCAL | CREAD;
    
    //LOCAL FLAGS
    //ICANON 	- canonical mode
    ttys1_termios.c_lflag = 0;//ICANON;
    
    //CONTROL CHARACTERS
    //ttys1_termios.c_cc[VMIN] = 250;
    
    //tcflush(tty_fd,TCIOFLUSH);
    tcsetattr(tty_fd,TCSANOW,&ttys1_termios);
    
    char receive_buffer[250];
    char update_buffer[NMEA_SENTENCE_MAX_SIZE];
    
    int	 iUIndex = 0;
    
    while (1)
    {
	int received  = read(tty_fd,receive_buffer,250);
	if (received > 0)
	{
		int ii;
		for (ii = 0; ii < received; ii++)
		{
		//	putc(receive_buffer[ii],stdout);
			if (receive_buffer[ii] == '$')
			{
				iUIndex = 0;
				
				update_buffer[iUIndex] = receive_buffer[ii];
				
				iUIndex++;
			}
			else if (receive_buffer[ii] == '\n')
			{
				if (iUIndex < NMEA_SENTENCE_MAX_SIZE)
					update_buffer[iUIndex] = '\0';	
				
				UpdateNMEATable(update_buffer);
				
				iUIndex++;
				
			}
			else
			{
				if (iUIndex < NMEA_SENTENCE_MAX_SIZE)
					update_buffer[iUIndex] = receive_buffer[ii];
				
				iUIndex++;
				
				
			}
			
			if (iUIndex >= NMEA_SENTENCE_MAX_SIZE)
			{
#ifdef		PRINT_STATUS
				printf("UINDEX > NMEA_SENTENCE_MAX_SIZE\n");
#endif
				exit(-1);
			}
			
			
		}
	}
    }
    
    close(tty_fd);
    
  
}

void	UpdateNMEATable(char *sentence)
{
//update table
	struct sembuf NMEATable_sembuf[1];
	
	NMEATable_sembuf[0].sem_num	= 0;
	NMEATable_sembuf[0].sem_op	= -1;
	NMEATable_sembuf[0].sem_flg	= IPC_NOWAIT | SEM_UNDO;
	
	
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
#ifdef PRINT_PROCESS 	
		printf("Update Table: SEM ID is %d\n",iNMEATable_SemaphoreID);
#endif		

		if (!strncmp(sentence,"$GPGGA",6))
		{
#ifdef PRINT_PROCESS			
			printf("Sentence: %s\n",sentence);
#endif			
			strncpy(((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GGA,sentence,NMEA_SENTENCE_MAX_SIZE);
		}
		else if (!strncmp(sentence,"$GPGLL",6))
		{
#ifdef PRINT_PROCESS			
			printf("Sentence: %s\n",sentence);
#endif
			strncpy(((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GLL,sentence,NMEA_SENTENCE_MAX_SIZE);
		}
		else if (!strncmp(sentence,"$GPGSA",6))
		{
#ifdef PRINT_PROCESS
			printf("Sentence: %s\n",sentence);
#endif		
			strncpy(((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GSA,sentence,NMEA_SENTENCE_MAX_SIZE);
		}
		else if (!strncmp(sentence,"$GPGSV",6))
		{
#ifdef PRINT_PROCESS
			printf("Sentence: %s\n",sentence);
#endif		
			strncpy(((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->GSV,sentence,NMEA_SENTENCE_MAX_SIZE);
		}
		else if (!strncmp(sentence,"$GPRMC",6))
		{
#ifdef PRINT_PROCESS
			printf("Sentence: %s\n",sentence);
#endif		
			strncpy(((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->RMC,sentence,NMEA_SENTENCE_MAX_SIZE);
		}
		else if (!strncmp(sentence,"$GPVTG",6))
		{
#ifdef PRINT_PROCESS
			printf("Sentence: %s\n",sentence);
#endif		
			strncpy(((NMEA_SENTENCE_TABLE *)pNMEATable_SharedMemPtr)->VTG,sentence,NMEA_SENTENCE_MAX_SIZE);
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
	}
		
	//UPDATE TABLE HERE
	
	
	
}

void	bb_process_gps_inputs_exit()
{
	if (shmctl(iNMEATable_SharedMemID, IPC_RMID,0) < 0)
	{
#ifdef PRINT_STATUS		
		printf("shmctl error");
#endif		
		exit(-1);
	}
	
	semctl(iNMEATable_SemaphoreID,0,IPC_RMID);
	close(tty_fd);	
}

void bb_process_gps_inputs_close(int signum)
{
	bb_process_gps_inputs_exit();
	exit(0);
}		
	
	
	

