#ifndef __BB_H
#define __BB_H

#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>

#define		NMEA_SENTENCE_MAX_SIZE	100

typedef struct
{
	char GGA[NMEA_SENTENCE_MAX_SIZE];
	char GLL[NMEA_SENTENCE_MAX_SIZE];
	char GSA[NMEA_SENTENCE_MAX_SIZE];
	char GSV[NMEA_SENTENCE_MAX_SIZE];
	char RMC[NMEA_SENTENCE_MAX_SIZE];
	char VTG[NMEA_SENTENCE_MAX_SIZE];
} NMEA_SENTENCE_TABLE;

union semun {
    int              val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                (Linux-specific) */
};

#define		PRINT_STATUS
#define         PRINT_SERVER

void	bb_server();
void	bb_process_gps_inputs();
void	bb_process_gps_inputs_exit();


int iNMEATable_SharedMemID;
char *pNMEATable_SharedMemPtr;
int iNMEATable_SemaphoreID;



#endif
