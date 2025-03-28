// NMEA.cpp : Defines the entry point for the console application.
//

#include "mtk_nmea.h"
#include "circular_buffer.h"
#include "nmea.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void 	print_s(char *somestr, int size);
void 	print_gga(GGA *g);
void 	print_gll(GLL *g);
void 	print_gsa(GSA *g);
void 	print_gsv(GSV *g);
void 	print_rmc(RMC *g);
void 	print_vtg(VTG *g);
void 	print_field(char*str,unsigned int size);
void 	parse_name(char *,unsigned int);

int main(int argc, char* argv[])
{
	char *s = 0;
	int i = PMTK_TEST_000(&s); 

	print_s(s,i);

	free(s);

	s = 0;

	i = PMTK_ACK_001(&s,PMTK_ACK_001_3);

	print_s(s,i);

	free(s);
	s = 0;

	i = PMTK_SYS_MSG_010(&s,PMTK_SYS_MSG_010_1);
	print_s(s,i);

	free(s);
	s = 0;

	i = PMTK_CMD_HOT_START_101(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_CMD_WARM_START_102(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_CMD_COLD_START_103(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_CMD_FULL_COLD_START_104(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_API_SET_DGPS_MODE_301(&s,PMTK_API_SET_DGPS_MODE_301_1);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_API_SET_SBAS_ENABLED_313(&s,PMTK_API_SET_SBAS_ENABLED_313_1);

	print_s(s,i);

	free(s);
	s=0;

	char settings[17] = {PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_5,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_0,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1};


	i = PMTK_API_SET_NMEA_OUTPUT_314(&s,settings,0);

	print_s(s,i);

	free(s);
	s=0;


	i = PMTK_API_SET_NMEA_OUTPUT_314(&s,settings,1);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_API_SET_PWR_SAV_MODE_320(&s,PMTK_API_SET_PWR_SAV_MODE_0);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_API_Q_DGPS_MODE_401(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_API_Q_SBAS_ENABLED_413(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_API_Q_NMEA_OUTPUT_414(&s);

	print_s(s,i);
	free(s);
	s=0;

	i = PMTK_API_Q_PWR_SAV_MOD_420(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_DT_DGPS_MODE_501(&s,PMTK_DT_DGPS_MODE_501_1);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_DT_SBAS_ENABLED_513(&s,PMTK_DT_SBAS_ENABLED_513_1);

	print_s(s,i);

	free(s);
	s=0;

	char settings2[17] = {PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_5,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_0,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1,
						PMTK_API_SET_NMEA_OUTPUT_314_1};


	i = PMTK_DT_NMEA_OUTPUT_514(&s,settings2);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_DT_PWR_SAV_MODE_520(&s,PMTK_DT_PWR_SAV_MODE_520_0);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_Q_VERSION_604(&s);

	print_s(s,i);

	free(s);
	s=0;

	i = PMTK_DT_VERSION_704(&s,"1.881_06","0606_m0138","0000");

	print_s(s,i);

	free(s);
	s=0;

	//char cs[2];
	//checksum_mtk("PMTK604",7,cs);
	
	char *ggastring = "$GPGGA,053740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64\r\n";
	
	printf("%s\n",ggastring);
	
	GGA gga;
	
	int rgga = ReadGGA(&gga,ggastring,strlen(ggastring));
	
	if (rgga == 0)
	  print_gga(&gga);
	
	
	/*ggastring = "$GPGGA,,2503.6319,N,12136.0099,,1,08,1.1,,M,15.2,M,,0000*29\r\n";
	
	printf("%s\n",ggastring);
	
	 rgga = ReadGGA(&gga,ggastring,strlen(ggastring));
	
	if (rgga == 0)
	  print_gga(&gga);	*/
	
	
	char *gllstring = "$GPGLL,2503.6319,N,12136.0099,E,053740.000,A,A*52\r\n";
	
	printf("%s\n",gllstring);
	
	GLL gll;
	
	int rgll = ReadGLL(&gll,gllstring,strlen(gllstring));
	
	if (rgll == 0)
	  print_gll(&gll);
	
	
	char *gsastring = "$GPGSA,A,3,24,07,17,11,28,08,20,04,,,,,2.0,1.1,1.7*35\r\n";
	
	printf("%s\n",gsastring);
	
	GSA gsa;
	
	int rgsa = ReadGSA(&gsa,gsastring,strlen(gsastring));
	
	if (rgsa == 0)
	  print_gsa(&gsa);
	
	char *gsvstring = "$GPGSV,3,2,12,17,41,328,45,07,32,315,45,04,31,250,40,11,25,046,41*75\r\n";
	
	printf("%s\n",gsvstring);
	
	GSV gsv;
	
	int rgsv = ReadGSV(&gsv,gsvstring,strlen(gsvstring));
	
	if (!rgsv)
	  print_gsv(&gsv);
	
	char *rmcstring = "$GPRMC,053740.000,A,2503.6319,N,12136.0099,E,2.69,79.65,100106,,,A*53\r\n";
	
	printf("%s\n",rmcstring);
	
	RMC rmc;
	
	int rrmc = ReadRMC(&rmc,rmcstring,strlen(rmcstring));
	
	if (!rrmc)
	  print_rmc(&rmc);	
	
	char *vtgstring = "$GPVTG,79.65,T,,M,2.69,N,5.0,K,A*38\r\n";
	
	printf("%s\n",vtgstring);
	
	VTG vtg;
	
	int rvtg = ReadVTG(&vtg,vtgstring,strlen(vtgstring));
	
	if (!rvtg)
	  print_vtg(&vtg);
	
	
	char *gga_msg = NULL;
	
	unsigned int gga_size;
	WriteGGA(&gga,&gga_msg,&gga_size);
	
	if (gga_msg)
	{
	  print_s(gga_msg,gga_size);
	  
	  free(gga_msg);
	}
	
	char *gll_msg = NULL;
	
	unsigned int gll_size;
	WriteGLL(&gll,&gll_msg,&gll_size);
	
	if (gll_msg)
	{
	  print_s(gll_msg,gll_size);
	  
	  free(gll_msg);
	}
	
	char *gsa_msg = NULL;
	
	unsigned int gsa_size;
	WriteGSA(&gsa,&gsa_msg,&gsa_size);
	
	if (gsa_msg)
	{
	  print_s(gsa_msg,gsa_size);
	  
	  free(gsa_msg);
	}	
	
	char *gsv_msg = NULL;
	
	unsigned int gsv_size;
	WriteGSV(&gsv,&gsv_msg,&gsv_size);
	
	if (gsv_msg)
	{
	  print_s(gsv_msg,gsv_size);
	  
	  free(gsv_msg);
	}	
	
	
	char *rmc_msg = NULL;
	
	unsigned int rmc_size;
	WriteRMC(&rmc,&rmc_msg,&rmc_size);
	
	if (rmc_msg)
	{
	  print_s(rmc_msg,rmc_size);
	  
	  free(rmc_msg);
	}		
			
		
	char *vtg_msg = NULL;
	
	unsigned int vtg_size;
	WriteVTG(&vtg,&vtg_msg,&vtg_size);
	
	if (rmc_msg)
	{
	  print_s(vtg_msg,vtg_size);
	  
	  free(vtg_msg);
	}
	
	
	char *str1 = "$GPGGA,053740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64\r\n";
	char *str2 = "$GPGLL,2503.6319,N,12136.0099,E,053740.000,A,A*52\r\n";
	//char *str1 = "$SLKJG4562..2$GPGGA,053740.000,2503.6319,N,12136.00";
	//char *str2 = "99,E,1,08,1.1,63.8,M,15.2,M,,0000*64\r\n";
	char *str3 = "$GPGSA,A,3,24,07,17,11,28,08,20,04,,,,,2.0,1.1,1.7*35\r\n";
	char *str4 = "$GPGSV,3,1,12,28,81,285,42,24,67,302,46,31,54,354,,20,51,077,46*73\r\n"; 
	char *str5 = "$GPGSV,3,2,12,17,41,328,45,07,32,315,45,04,31,250,40,11,25,046,41*75\r\n";
	char *str6 = "$GPGSV,3,3,12,08,22,214,38,27,08,190,16,19,05,092,33,23,04,127,*7B\r\n";
	char *str7 = "$GPRMC,053740.000,A,2503.6319,N,12136.0099,E,2.69,79.65,100106,,,A*53\r\n";
	char *str8 = "$GPVTG,79.65,T,,M,2.69,N,5.0,K,A*38\r\n";
	
	circular_buffer		cBuffer;
	
	char *readStr1;
	int  ireadStr1Size = 0;
	
	int inc;
	
	for (inc = 0; inc < 600; inc++)
	{
	  circ_buff_insert_mult(&cBuffer,str1,strlen(str1));
	  circ_buff_insert_mult(&cBuffer,str2,strlen(str2));
	  circ_buff_insert_mult(&cBuffer,str3,strlen(str3));
	  circ_buff_insert_mult(&cBuffer,str4,strlen(str4));
	  circ_buff_insert_mult(&cBuffer,str5,strlen(str5));
	  circ_buff_insert_mult(&cBuffer,str6,strlen(str6));
	  circ_buff_insert_mult(&cBuffer,str7,strlen(str7));
	  circ_buff_insert_mult(&cBuffer,str8,strlen(str8));
	}
	

	   printf("Buffer: %.*s\n\n",CIRC_BUFFER_SIZE,cBuffer.buff);

	
	
	int ps;
	for (ps = 0; ps < 8; ps++)
	{
	  circ_buff_read_between_inclusive(&cBuffer,'$','\n',&readStr1,&ireadStr1Size);
		  
	  if (ireadStr1Size > 0)
	  {
	    printf("String 1 %.*s size %i\n",ireadStr1Size,readStr1,ireadStr1Size);
	    
	    parse_name(readStr1,ireadStr1Size);
	    
	    free(readStr1);
	  }
	}
	
	
	
		
	
	return 0;
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
    
    
    if (!strncmp(str,"$GPGGA",6))
    {
      ret = ReadGGA(&gga,str,length);
      
      if (!ret)
	print_gga(&gga);
    }
    else if (!strncmp(str,"$GPGLL",6))
    {
      ret = ReadGLL(&gll,str,length);
      if (!ret)
	print_gll(&gll);
    }
    else if (!strncmp(str,"$GPGSA",6))
    {
      ret = ReadGSA(&gsa,str,length);
           if (!ret)
	print_gsa(&gsa);
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

