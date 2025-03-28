/*
    FreeRTOS V6.1.1 - Copyright (C) 2011 Real Time Engineers Ltd.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    ***NOTE*** The exception to the GPL is included to allow you to distribute
    a combined work that includes FreeRTOS without being obliged to provide the
    source code for proprietary components outside of the FreeRTOS kernel.
    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public 
    License and the FreeRTOS license exception along with FreeRTOS; if not it 
    can be viewed here: http://www.freertos.org/a00114.html and also obtained 
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/

/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* Demo includes. */
#include "basic_io.h"

#include "mtk_nmea.h"
#include "circular_buffer.h"
#include "nmea.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uart.h"

/* The task function. */
void vTaskFunction( void *pvParameters );

/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */
const char *pcTextForTask1 = "Task 1 is running\n";
const char *pcTextForTask2 = "Task 2 is running\n";

void 	print_s(char *somestr, int size);
void 	print_gga(GGA *g);
void 	print_gll(GLL *g);
void 	print_gsa(GSA *g);
void 	print_gsv(GSV *g);
void 	print_rmc(RMC *g);
void 	print_vtg(VTG *g);
void 	print_field(char*str,unsigned int size);
void 	parse_name(char *,unsigned int);

volatile uint32_t	UART0SendCount = 0;
volatile uint8_t 	UART0SendBuffer[BUFSIZE];

extern volatile circular_buffer	UART0Buffer,UART1Buffer;

extern xSemaphoreHandle xBinarySemaphore;

extern volatile char c;

/*-----------------------------------------------------------*/

int main( void )
{
	printf("");
  /* SystemClockUpdate() updates the SystemFrequency variable */
	  volatile unsigned int i = 0;

	  printf("Start\n");

	//SystemClockUpdate();

 UARTInit(0, 57600);	/* baud rate setting */
 //UARTInit(1, 9600);	/* baud rate setting */


  UART0SendBuffer[0] = (uint8_t)'a';
  UART0SendBuffer[1] = (uint8_t)'n';
  UART0SendBuffer[2] = (uint8_t)'t';
  UART0SendBuffer[3] = (uint8_t)'o';
  UART0SendBuffer[4] = (uint8_t)'n';

  char *pmtkString;

  UART0SendCount = PMTK_TEST_000(&pmtkString);

	if ( UART0SendCount != 0 )
	{
	  LPC_UART0->IER = IER_THRE | IER_RLS;			/* Disable RBR */
	  UARTSend( 0, (uint8_t *)pmtkString, UART0SendCount );
	  LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */

	  free(pmtkString);
	}

	  UART0SendCount = PMTK_CMD_COLD_START_103(&pmtkString);

		if ( UART0SendCount != 0 )
		{
		  LPC_UART0->IER = IER_THRE | IER_RLS;			/* Disable RBR */
		  UARTSend( 0, (uint8_t *)pmtkString, UART0SendCount );
		  LPC_UART0->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */

		  free(pmtkString);
		}

 	 char *readStr1;
 	 int ireadStr1Size = 0;
 	 char next;
  	 char localBuffer[1024];

 	 while (1)
 	 {

 		int error = circ_buff_read_next(&UART0Buffer,&next);

 		if (error == ERROR_OVERREAD)
 			continue;

 		if (next == '$' && ireadStr1Size > 0)
 		{
 			ireadStr1Size = 0;
 			localBuffer[ireadStr1Size] = next;
 			ireadStr1Size++;
 		}
 		else if (next == '$')
 		{
 			localBuffer[ireadStr1Size] = next;
 			ireadStr1Size++;
 		}
 		else if (next == '\n')
 		{
 			localBuffer[ireadStr1Size] = next;
 			ireadStr1Size++;
 			parse_name(localBuffer,ireadStr1Size);
 			ireadStr1Size = 0;
 		}
 		else
 		{
 			localBuffer[ireadStr1Size] = next;
 			ireadStr1Size++;
 		}







 	 }

	/* If all is well we will never reach here as the scheduler will now be
	running.  If we do reach here then it is likely that there was insufficient
	heap available for the idle task to be created. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
portTickType xLastWakeTime;

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	pcTaskName = ( char * ) pvParameters;

	xSemaphoreTake(xBinarySemaphore,0);

	char *readStr1 = "some string";
	int ireadStr1Size = 0;

	for( ;; )
	{
		/* Print out the name of this task. */
		//vPrintString( pcTaskName );

		xSemaphoreTake(xBinarySemaphore,portMAX_DELAY);




		//vTaskDelay( 1000 / portTICK_RATE_MS );


	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}

void 	parse_name(char *str, unsigned int length)
{

    if (!str)
      return;

    GGA gga;
    GLL gll;
    GSA gsa;
    GSV gsv;
    RMC rmc;
    VTG vtg;

    int ret;

    if (!strncmp(str,"$PMTK",5))
    {
    	printf("%.*s",length,str);
    }
    else if (!strncmp(str,"$GPGGA",6))
    {
      ret = ReadGGA(&gga,str,length);

      if (!ret)
	print_gga(&gga);
    }
    else if (!strncmp(str,"$GPGLL",6))
    {
      ret = ReadGLL(&gll,str,length);
    //  if (!ret)
	//print_gll(&gll);
    }
    else if (!strncmp(str,"$GPGSA",6))
    {
      ret = ReadGSA(&gsa,str,length);
   //        if (!ret)
	//print_gsa(&gsa);
    }
    else if (!strncmp(str,"$GPGSV",6))
    {
      ret = ReadGSV(&gsv,str,length);
           if (!ret)
	print_gsv(&gsv);
    }
    else if (!strncmp(str,"$GPRMC",6))
    {
      ret = ReadRMC(&rmc,str,length);
           if (!ret)
	print_rmc(&rmc);
    }
    else if (!strncmp(str,"$GPVTG",6))
    {
      ret = ReadVTG(&vtg,str,length);
           if (!ret)
	print_vtg(&vtg);
    }

 }


void 	print_field(char *str, unsigned int size)
{

    int i;
    for (i = 0;i < size;i++)
      printf("%c",str[i]);

}

void 	print_gga(GGA *g)
{
    printf("\nMessage ID:"); print_field(g->caMessageID,5);
    printf("\nUTC Time:"); print_field(g->caUtcTime,10);
    printf("\nLatitude:");print_field(g->caLatitude,9);
    printf("\nNS Indicator: %c",g->cNSIndicator);
    printf("\nLongitude: ");print_field(g->caLongitude,10);
    printf("\nEW Indicator: %c",g->cEWIndicator);
    printf("\nPosition Fix Indicator %u",g->iPositionFixIndicator);
    printf("\nSatellites Used: ");print_field(g->caSatellitesUsed,2);
    printf("\nHDOP: %f",g->dHDOP);
    printf("\nMSL Altitude: %f",g->dMSLAltitude);
    printf("\nUNITS: %c",g->cUnits1);
    printf("\nGeo ID Separation %f",g->dGeoidSeparation);
    printf("\nUNITS: %c",g->cUnits2);
    printf("\nAge Of Diff Corr: %d",g->iAgeofDiffCorr);
    printf("\nDIFF REF Station ID: ");print_field(g->caDiffREfStationID,4);
    printf("\nCHECK SUM: ");print_field(g->caChecksum,2);
    printf("\n");
}

void 	print_gll(GLL *g)
{
    printf("\nMessage ID:"); print_field(g->caMessageID,5);
    printf("\nLatitude:");print_field(g->caLatitude,9);
    printf("\nNS Indicator: %c",g->cNSIndicator);
    printf("\nLongitude:");print_field(g->caLongitude,10);
    printf("\nEW Indicator: %c",g->cEWIndicator);
    printf("\nUETC Time:");print_field(g->caUtcTime,10);
    printf("\nStatus: %c",g->cStatus);
    printf("\nMode: %c",g->cMode);
    printf("\nChecksum:");print_field(g->caChecksum,2);
     printf("\n");
}

void 	print_gsa(GSA *g)
{
  printf("\nMessage ID:"); print_field(g->caMessageID,5);
  printf("\nMode 1: %c",g->cMode1);
  printf("\nMode 2: %c",g->cMode2);

  int ii;

  for (ii = 0; ii < 12; ii++)
  {
    printf("\nID of Satellite %d: ",ii);print_field(g->caIDofSatelliteUsed[ii],2);
  }

  printf("\nPDOP: %f",g->dPDOP);
  printf("\nHDOP: %f",g->dHDOP);
  printf("\nVDOP: %f",g->dVDOP);
  printf("\nChecksum: ");print_field(g->caChecksum,2);
  printf("\n");
}


void 	print_gsv(GSV *g)
{
  	printf("\nMessage ID: ");print_field(g->caMessageID,5);
	printf("\nTotal Number of Messages: %i",g->iTotalNumberOfMessages);
	printf("\nMessage Number: %i", g->iMessageNumber);
	printf("\nSatellites in View: %i", g->iSatellitesInView);
	printf("\nSatellite ID 1: ");print_field(g->caSatelliteID[0],2);	//channel 1 and 4
	printf("\nElvation 1: %i",g->iaElevation[0]);		//channel 1 and 4
	printf("\nAzimuth 1: %i",g->iaAzimuth[0]);			//channel 1 and 4
	printf("\nSNR 1: %i",g->iaSNR[0]);				//channel 1 and 4
	printf("\nSatellite ID 2: ");print_field(g->caSatelliteID[1],2);	//channel 1 and 4
	printf("\nElvation 2: %i",g->iaElevation[1]);		//channel 1 and 4
	printf("\nAzimuth 2: %i",g->iaAzimuth[1]);			//channel 1 and 4
	printf("\nSNR 2: %i",g->iaSNR[1]);				//channel 1 and 4
	printf("\nSatellite ID 3: ");print_field(g->caSatelliteID[2],2);	//channel 1 and 4
	printf("\nElvation 3: %i",g->iaElevation[2]);		//channel 1 and 4
	printf("\nAzimuth 3: %i",g->iaAzimuth[2]);			//channel 1 and 4
	printf("\nSNR 3: %i",g->iaSNR[2]);				//channel 1 and 4
	printf("\nSatellite ID 4: ");print_field(g->caSatelliteID[3],2);	//channel 1 and 4
	printf("\nElvation 4: %i",g->iaElevation[3]);		//channel 1 and 4
	printf("\nAzimuth 4: %i",g->iaAzimuth[3]);			//channel 1 and 4
	printf("\nSNR 4: %i",g->iaSNR[3]);				//channel 1 and 4
	printf("\nChecksum: ");print_field(g->caChecksum,2);
	printf("\n");
}

void 	print_rmc(RMC *g)
{
  	printf("\nMessage ID: "); print_field(g->caMessageID,5);
	printf("\nUTC Time: ");print_field(g->caUTCTime,10);
	printf("\nStatus: %c",g->cStatus);
	printf("\nLatitude: ");print_field(g->caLatitude,9);;
	printf("\nNS Indicator: %c",g->cNSIndicator);
	printf("\nLongitude: ");print_field(g->caLongitude,10);
	printf("\nEW Indicator %c",g->cEWIndicator);
	printf("\nSpeed Over Ground : %f",g->dSpeedOverGround);
	printf("\nCourse Over Ground: %f",g->dCourseOverGround);
	printf("\nDate: ");print_field(g->caDate,6);
	printf("\nMagnetic Variation %i",g->iMagneticVariation);
	printf("\nVariation Sense: %c",g->cVariationSense);
	printf("\nMode: %c",g->cMode);
	printf("\nChecksum: ");print_field(g->caChecksum,2);
	printf("\n");
}

void 	print_vtg(VTG *g)
{
  	printf("\nMessage ID: ");print_field(g->caMessageID,5);
	printf("\nCourse Over Ground 1: %f",g->dCourseOverGround1);
	printf("\nReference 1: %c",g->cReference1);
	printf("\nCourse Over Ground 2: %f", g->dCourseOverGround2);
	printf("\nReference 2: %c", g->cReference2);
	printf("\nSpeed Over Ground 1: %f",g->dSpeedOverGround1);
	printf("\nUnits 1: %c",g->cUnits1);
	printf("\nSpeed Over Ground 2: %f",g->dSpeedOverGround2);
	printf("\nUnits 2: %c",g->cUnits2);
	printf("\nMode: %c", g->cMode);
	printf("\nChecksum: ");print_field(g->caChecksum,2);
	printf("\n");
}

void print_s(char *somestr, int size)
{
	int ii = 0;

	for (; ii < size; ii++)
	{
		printf("%c",somestr[ii]);
	}

	printf("\n");
}



