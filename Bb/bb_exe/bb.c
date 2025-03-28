#include <linux/types.h>
#include <signal.h>
#include <unistd.h>

#include "bb.h"

#define 	SHMEMSIZE 	(sizeof(NMEA_SENTENCE_TABLE))

int Initialize();

int main()
{
	Initialize();

	int pid = fork();
	
	if (pid < 0)
	{
#ifdef		PRINT_STATUS
		printf("fork error.  errno %i", errno);
#endif	
		exit(-1);
	}
	else if (pid == 0)
	{
		//child
		bb_server();
	}
	else
	{
		//parent
		
		bb_process_gps_inputs();
		//kill(pid,SIGKILL);
		int iStatus;
		if (wait(&iStatus) != pid)
		{
#ifdef		PRINT_STATUS	
			printf("wait failed. errno %i\n",errno);
#endif
		}
		atexit(bb_process_gps_inputs_exit);

	}
	

	return 0;
}
/******************************************************************************

	Name:		Initialize()
	Description:	This function initializes Shared Memory Segment
			and semaphore used to handle NMEA_SENTENCE_TABLE records
	Input:		none
	Return:		0 - initialized OK, -1 - error
	Date:		04.28.2013

********************************************************************************/
int Initialize()
{


	if ((iNMEATable_SharedMemID  = shmget(IPC_PRIVATE,SHMEMSIZE,(SHM_R | SHM_W) )) < 0)
	{
#ifdef PRINT_STATUS
		printf("shmget error.  errno %i\n", errno);
#endif		
		return -1;
	}

	if ((pNMEATable_SharedMemPtr = (char*)shmat(iNMEATable_SharedMemID,0,0)) == (void *) -1)
	{
#ifdef PRINT_STATUS	
		printf("shmat error. errno %i\n", errno);
#endif		
		return -1;
	}
	
	if ((iNMEATable_SemaphoreID = semget(IPC_PRIVATE,1,(SHM_R | SHM_W))) < 0)
	{
#ifdef PRINT_STATUS	
		printf("semget error.  errno %i\n",errno);
#endif		
		return -1;
	}
	
	union semun NMEATable_semun;
	
	NMEATable_semun.val = 1;
	
	semctl(iNMEATable_SemaphoreID,0,SETVAL,NMEATable_semun);

	return 0;
}
