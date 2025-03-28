#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "nmea.h"
#include "mtk_nmea.h"
#include "nmea_errors.h"

char *strtok_nmea(char *str, char c)
{
    static char *t;
  
    if (str)
      t = str;
    
    char *last = t;
    
    while ((*t != c) && (*t != '\r') &&  (*t != '\n'))
    {
	t++;
    }
    
    if (*t == c)
    {
      *t = '\0';
      t++;
    }
    
    if (last == t)
      return 0;
    else
      return last;
}

int 	nmea_field_valid(char *str)
{
  int error = 1;
  
  if (str == NULL || str == 0 || *str == '\0')
    error = 0;
  
  return error;
}

void 	nmea_set_double_data(double *data,char *str)
{
  if (nmea_field_valid(str))
	*data = (double)atof(str);
   else
       *data = -1;
}

void 	nmea_set_char_data(char *data, char *str, int size)
{
   if (nmea_field_valid(str))
      memcpy(data,str,size);
   else
      memset(data,'\0',size);
}

void 	nmea_set_int_data(int *data,char *str)
{
  	     if (nmea_field_valid(str))
		*data =atoi(str);
	     else
	       *data = -1;
}

int 	nmea_write_char_data(char *data, char **str, int size, int *totalsize)
{
      if (*str == NULL)
      {
	*str = (char*)malloc(size);
	memcpy(*str,data,size);
	*totalsize = size;
      }
      else
      {
	*str = (char*)realloc(*str,*totalsize + size+1);
	char *t = *str + *totalsize;
	*t = ',';
	t++;
	memcpy(t,data,size);
	*totalsize += size + 1;
      }
      
      return 0;
}

int 	nmea_write_int_data(int *data,char **str,int *totalsize)
{
    char d[20] = {0};
    
    sprintf(d,"%i",*data);
    int s = strlen(d);
    
    if (*data == NMEA_INT_UNDEF)
      s = 0;
  
    if (*str == NULL)
    {
      *str = (char*)malloc(s);
      memcpy(str,d,s);
      *totalsize +=s;
    }
    else
    {
      *str = (char*)realloc(*str,*totalsize + s + 1);
      char *t = *str + *totalsize;
      *t = ',';
      t++;
      
      if (s > 0)
      {
	memcpy(t,d,s);
      }
      
      *totalsize += s + 1;
    }
    
    return 0;
}

int 	nmea_write_double_data(double *data,char **str,int *totalsize)
{
     char d[20] = {0};
    sprintf(d,"%.1f",*data);
    int s = strlen(d);
    
    if (*data == NMEA_DOUBLE_UNDEF)
      s = 0;
  
    if (*str == NULL)
    {
      *str = (char*)malloc(s);
      memcpy(*str,d,s);
      *totalsize += s;
    }
    else
    {
      *str = (char*)realloc(*str,*totalsize + s + 1);
      char *t = *str + *totalsize;
      *t = ',';
      t++;
      
      if (s > 0)
      {
	memcpy(t,d,s);
      }
      
      *totalsize += s + 1;
    }
    
    return 0;
}

int 	nmea_write_checksum(char **str,int *totalsize)
{
  char cs[2];
    checksum_mtk(*str,*totalsize,cs);
    
    if (!*str)
	return NMEA_ERROR_NULL;
    else
    {
	*str = (char*)realloc(*str,(*totalsize + 1 + 2+ 2));
	char *t = *str + *totalsize;
	*t= '*';
	t++;
	*t = cs[0];
	t++;
	*t = cs[1];
	t++;
	*t = '\r';
	t++;
	*t = '\n';
	*totalsize += 5;
    }
    
    
    return 0;
}

int	ReadGGA(GGA *gga, char *msg, unsigned int length)
{
  

  
      if (!msg)
	return NMEA_ERROR_NULL;
      if (*msg != '$')
	 return NMEA_ERROR_NO_$_SIGN;
      else
	 msg++;

      
      char *msgt = (char*)malloc(length);
      strncpy(msgt,msg,length - 1);
	
       char *testcs1 = strtok(msgt,"*");
      char *testcs2 = strtok(NULL,"\r");
      char cs[2];
      
      checksum_mtk(testcs1,length - 6, cs);
      
      if (strncmp(cs, testcs2,2))
      {
	 free(msgt);
	return NMEA_ERROR_CHECKSUM_CHECK_FAIL;
      }
      
      memcpy(gga->caChecksum,testcs2,2);
      
      strncpy(msgt,msg,length-1);
      
      char delim = ',';
      char *next = strtok_nmea(msgt,delim);
      
      GGA_FIELDS field = GGA_MESSAGE_ID;
      
      while (field != GGA_CHECKSUM)
      {
	switch(field)
	{
	  case GGA_MESSAGE_ID:
	    nmea_set_char_data(gga->caMessageID,next,5);
	    break;
	  case GGA_UTC_TIME:
	    nmea_set_char_data(gga->caUtcTime,next,10);
	    break;	  
	  case GGA_LATITUDE:
	    nmea_set_char_data(gga->caLatitude,next,9);
	    break;	  
	  case  GGA_NS_INDICATOR:
	    nmea_set_char_data(&gga->cNSIndicator,next,1);
	    break;	  
	  case GGA_LONGITUDE:
	    nmea_set_char_data(gga->caLongitude,next,10);
	    break;
	  case GGA_EW_INDICATOR:
	    nmea_set_char_data(&gga->cEWIndicator,next,1);
	   break;	  
	  case  GGA_POSITION_FIX_INDICATOR:
	     nmea_set_int_data(&gga->iPositionFixIndicator,next);
	    break;	  
	  case GGA_SATELLITES_USED:
	     nmea_set_char_data(gga->caSatellitesUsed,next,2);
	    break;
	  case GGA_HDOP:
	     nmea_set_double_data(&(gga->dHDOP),next);
	   break;
	  case GGA_MSL_ALTITUDE:
	     nmea_set_double_data(&gga->dMSLAltitude,next);
	    break;	  
	  case GGA_UNITS1:
	    nmea_set_char_data(&gga->cUnits1,next,1);
	    break;	  
	  case GGA_GEOID_SEPARATION:
	     nmea_set_double_data(&gga->dGeoidSeparation,next);
	    break;	  
	  case GGA_UNITS2:
	     nmea_set_char_data(&gga->cUnits2,next,1);
	     break;
	  case GGA_AGE_OFF_DIFF_CORR:
	      nmea_set_int_data(&gga->iAgeofDiffCorr,next);
	      delim = '*';
	    break;	  
	  case GGA_DIFF_REF_STATION_ID:
	     nmea_set_char_data(gga->caDiffREfStationID,next,4);
	    break;
	  case GGA_CHECKSUM:
	    break;
	}
	 
	 field=(GGA_FIELDS)(field+1);
	 next = strtok_nmea(NULL,delim); 
      }
      
      free(msgt);
  
    return 0;
}

int	WriteGGA(GGA *gga, char **msg, unsigned int *length)
{
    GGA_FIELDS field = GGA_MESSAGE_ID;
    
    *msg = NULL;
    
    int total_size;
    
    *length = 0;
    
    while (field <= GGA_CHECKSUM)
    {
      switch(field)
      {
	    case GGA_MESSAGE_ID:
	      nmea_write_char_data(gga->caMessageID,msg,5,&total_size);
	      break;
	    case GGA_UTC_TIME:
	      nmea_write_char_data(gga->caUtcTime,msg,10,&total_size);
	      break;	  
	    case GGA_LATITUDE:
	      nmea_write_char_data(gga->caLatitude,msg,9,&total_size);
	      break;	  
	    case  GGA_NS_INDICATOR:
	      nmea_write_char_data(&gga->cNSIndicator,msg,1,&total_size);
	      break;	  
	    case GGA_LONGITUDE:
	      nmea_write_char_data(gga->caLongitude,msg,10,&total_size);
	      break;
	    case GGA_EW_INDICATOR:
	      nmea_write_char_data(&gga->cEWIndicator,msg,1,&total_size);
	    break;	  
	    case  GGA_POSITION_FIX_INDICATOR:
	      nmea_write_int_data(&gga->iPositionFixIndicator,msg,&total_size);
	      break;	  
	    case GGA_SATELLITES_USED:
	      nmea_write_char_data(gga->caSatellitesUsed,msg,2,&total_size);
	      break;
	    case GGA_HDOP:
	      nmea_write_double_data(&(gga->dHDOP),msg,&total_size);
	    break;
	    case GGA_MSL_ALTITUDE:
	      nmea_write_double_data(&gga->dMSLAltitude,msg,&total_size);
	      break;	  
	    case GGA_UNITS1:
	      nmea_write_char_data(&gga->cUnits1,msg,1,&total_size);
	      break;	  
	    case GGA_GEOID_SEPARATION:
	      nmea_write_double_data(&gga->dGeoidSeparation,msg,&total_size);
	      break;	  
	    case GGA_UNITS2:
	      nmea_write_char_data(&gga->cUnits2,msg,1,&total_size);
	      break;
	    case GGA_AGE_OFF_DIFF_CORR:
		nmea_write_int_data(&gga->iAgeofDiffCorr,msg,&total_size);
	      break;	  
	    case GGA_DIFF_REF_STATION_ID:
	      nmea_write_char_data(gga->caDiffREfStationID,msg,4,&total_size);
	      break;
	    case GGA_CHECKSUM:
	      nmea_write_checksum(msg,&total_size);
	      break;
      }
      
      field = (GGA_FIELDS)(field+1);
    }
    
    *length = (unsigned int)total_size;
    
   return 0;
}

int	ReadGLL(GLL *gll, char *msg, unsigned int length)
{
     if (!msg)
	return NMEA_ERROR_NULL;
      if (*msg != '$')
	 return NMEA_ERROR_NO_$_SIGN;
      else
	 msg++;

      
      char *msgt = (char*)malloc(length);
      strncpy(msgt,msg,length - 1);
	
       char *testcs1 = strtok(msgt,"*");
      char *testcs2 = strtok(NULL,"\r");
      char cs[2];
      
      checksum_mtk(testcs1,length - 6, cs);
      
      if (strncmp(cs, testcs2,2))
      {
	 free(msgt);
	return NMEA_ERROR_CHECKSUM_CHECK_FAIL;
      }
      
      memcpy(gll->caChecksum,testcs2,2);
      
      strncpy(msgt,msg,length-1);
      
      char delim = ',';
      char *next = strtok_nmea(msgt,delim);
      
      GLL_FIELDS field = GLL_MESSAGE_ID;
      
      while (field != GLL_CHECKSUM)
      {
	switch(field)
	{
	  case GLL_MESSAGE_ID:
	    nmea_set_char_data(gll->caMessageID,next,5);
	    break;
	  case GLL_LATITUDE:
	    nmea_set_char_data(gll->caLatitude,next,9);
	    break;
	  case GLL_NS_INDICATOR:
	    nmea_set_char_data(&gll->cNSIndicator,next,1);
	    break;
	  case GLL_LONGITUDE:
	    nmea_set_char_data(gll->caLongitude,next,10);
	    break;
	  case GLL_EW_INDICATOR:
	    nmea_set_char_data(&gll->cEWIndicator,next,1);
	    break;
	  case GLL_UTC_TIME:
	    nmea_set_char_data(gll->caUtcTime,next,10);
	    break;
	  case GLL_STATUS:
	    nmea_set_char_data(&gll->cStatus,next,1);
	    break;
	  case GLL_MODE:
	    nmea_set_char_data(&gll->cMode,next,1);
	    break;
	  case GLL_CHECKSUM:
	    break;
	}
	
	 field = (GLL_FIELDS)(field+1);
	 next = strtok_nmea(NULL,delim); 
      }
      
       free(msgt);
  return 0;
}

int	WriteGLL(GLL *gll, char **msg, unsigned int *length)
{
  GLL_FIELDS field = GLL_MESSAGE_ID;
    
    *msg = NULL;
    
    int total_size;
    
    *length = 0;
    
    while (field <= GLL_CHECKSUM)
    {
      switch(field)
      {
	  case GLL_MESSAGE_ID:
	    nmea_write_char_data(gll->caMessageID,msg,5,&total_size);
	    break;
	  case GLL_LATITUDE:
	    nmea_write_char_data(gll->caLatitude,msg,9,&total_size);
	    break;
	  case GLL_NS_INDICATOR:
	    nmea_write_char_data(&gll->cNSIndicator,msg,1,&total_size);
	    break;
	  case GLL_LONGITUDE:
	    nmea_write_char_data(gll->caLongitude,msg,10,&total_size);
	    break;
	  case GLL_EW_INDICATOR:
	    nmea_write_char_data(&gll->cEWIndicator,msg,1,&total_size);
	    break;
	  case GLL_UTC_TIME:
	    nmea_write_char_data(gll->caUtcTime,msg,10,&total_size);
	    break;
	  case GLL_STATUS:
	    nmea_write_char_data(&gll->cStatus,msg,1,&total_size);
	    break;
	  case GLL_MODE:
	    nmea_write_char_data(&gll->cMode,msg,1,&total_size);
	    break;
	  case GLL_CHECKSUM:
	    nmea_write_checksum(msg,&total_size);
	    break;
      }
      
      field = (GLL_FIELDS)(field+1);
    }
    
    *length = (unsigned int)total_size;
    
   return 0;
}

int	ReadGSA(GSA *gsa, char *msg, unsigned int length)
{
  
     if (!msg)
	return NMEA_ERROR_NULL;
      if (*msg != '$')
	 return NMEA_ERROR_NO_$_SIGN;
      else
	 msg++;

      
      char *msgt = (char*)malloc(length);
      strncpy(msgt,msg,length - 1);
	
       char *testcs1 = strtok(msgt,"*");
      char *testcs2 = strtok(NULL,"\r");
      char cs[2];
      
      checksum_mtk(testcs1,length - 6, cs);
      
      if (strncmp(cs, testcs2,2))
      {
	 free(msgt);
	return NMEA_ERROR_CHECKSUM_CHECK_FAIL;
      }
      
      memcpy(gsa->caChecksum,testcs2,2);
      
      strncpy(msgt,msg,length-1);
      
      char delim = ',';
      char *next = strtok_nmea(msgt,delim);
      
      GSA_FIELDS field = GSA_MESSAGE_ID;
      
      while (field != GSA_CHECKSUM)
      {
	switch(field)
	{
	  case GSA_MESSAGE_ID:
	    nmea_set_char_data(gsa->caMessageID,next,5);
	    break;
	  case GSA_MODE1:
	    nmea_set_char_data(&gsa->cMode1,next,1);
	    break;
	  case GSA_MODE2:
	    nmea_set_char_data(&gsa->cMode2,next,1);
	    break;
	  case GSA_ID_SATELLITE_USED_CH1:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[0],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH2:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[1],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH3:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[2],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH4:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[3],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH5:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[4],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH6:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[5],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH7:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[6],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH8:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[7],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH9:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[8],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH10:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[9],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH11:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[10],next,2);
	    break;
	  case GSA_ID_SATELLITE_USED_CH12:
	    nmea_set_char_data(gsa->caIDofSatelliteUsed[11],next,2);
	    break;
	  case GSA_PDOP:
	    nmea_set_double_data(&gsa->dPDOP,next);
	    break;
	  case GSA_HDOP:
	    nmea_set_double_data(&gsa->dHDOP,next);
	    break;
	  case GSA_VDOP:
	    nmea_set_double_data(&gsa->dVDOP,next);
	    break;
	  case GSA_CHECKSUM:
	    break;
	}
	
	 field = (GSA_FIELDS)(field+1);
	 next = strtok_nmea(NULL,delim); 
      }
      
       free(msgt);
   
  return 0;
}

int	WriteGSA(GSA *gsa, char **msg, unsigned int *length)
{
  GSA_FIELDS field = GSA_MESSAGE_ID;
    
    *msg = NULL;
    
    int total_size;
    
    *length = 0;
    
    while (field <= GSA_CHECKSUM)
    {
      switch(field)
      {
	  case GSA_MESSAGE_ID:
	    nmea_write_char_data(gsa->caMessageID,msg,5,&total_size);
	    break;
	  case GSA_MODE1:
	    nmea_write_char_data(&gsa->cMode1,msg,1,&total_size);
	    break;
	  case GSA_MODE2:
	    nmea_write_char_data(&gsa->cMode2,msg,1,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH1:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[0],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH2:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[1],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH3:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[2],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH4:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[3],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH5:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[4],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH6:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[5],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH7:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[6],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH8:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[7],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH9:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[8],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH10:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[9],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH11:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[10],msg,2,&total_size);
	    break;
	  case GSA_ID_SATELLITE_USED_CH12:
	    nmea_write_char_data(gsa->caIDofSatelliteUsed[11],msg,2,&total_size);
	    break;
	  case GSA_PDOP:
	    nmea_write_double_data(&gsa->dPDOP,msg,&total_size);
	    break;
	  case GSA_HDOP:
	    nmea_write_double_data(&gsa->dHDOP,msg,&total_size);
	    break;
	  case GSA_VDOP:
	    nmea_write_double_data(&gsa->dVDOP,msg,&total_size);
	    break;
	  case GSA_CHECKSUM:
	    nmea_write_checksum(msg,&total_size);
	    break;
      }
      
      field = (GSA_FIELDS)(field+1);
    }
    
    *length = (unsigned int)total_size;
    
   return 0;
}

int ReadGSV(GSV *gsv, char *msg, unsigned int length)
{
  
    if (!msg)
	return NMEA_ERROR_NULL;
      if (*msg != '$')
	 return NMEA_ERROR_NO_$_SIGN;
      else
	 msg++;

      
      char *msgt = (char*)malloc(length);
      strncpy(msgt,msg,length - 1);
	
       char *testcs1 = strtok(msgt,"*");
      char *testcs2 = strtok(NULL,"\r");
      char cs[2];
      
      checksum_mtk(testcs1,length - 6, cs);
      
      if (strncmp(cs, testcs2,2))
      {
	 free(msgt);
	return NMEA_ERROR_CHECKSUM_CHECK_FAIL;
      }
      
      memcpy(gsv->caChecksum,testcs2,2);
      
      strncpy(msgt,msg,length-1);
      
      char delim = ',';
      char *next = strtok_nmea(msgt,delim);
      
      GSV_FIELDS field = GSV_MESSAGE_ID;
      
      while (field != GSV_CHECKSUM)
      {
	switch(field)
	{
	  case GSV_MESSAGE_ID:
	    nmea_set_char_data(gsv->caMessageID,next,5);
	    break;
	  case GSV_TOTAL_NUMBER_OF_MESSAGES:
	    nmea_set_int_data(&gsv->iTotalNumberOfMessages,next);
	    break;
	  case GSV_MESSAGE_NUMBER:
	    nmea_set_int_data(&gsv->iMessageNumber,next);
	    break;
	  case GSV_SATELLITES_IN_VIEW:
	    nmea_set_int_data(&gsv->iSatellitesInView,next);
	    break;
	  case GSV_SATELLITE_ID_1:
	    nmea_set_char_data(gsv->caSatelliteID[0],next,2);
	    break;
	  case GSV_ELEVATION_1:
	    nmea_set_int_data(&gsv->iaElevation[0],next);
	    break;
	  case GSV_AZIMUTH_1:
	    nmea_set_int_data(&gsv->iaAzimuth[0],next);
	    break;
	  case GSV_SNR_1:
	    nmea_set_int_data(&gsv->iaSNR[0],next);
	    break;
	  case GSV_SATELLITE_ID_2:
	    nmea_set_char_data(gsv->caSatelliteID[1],next,2);
	    break;
	  case GSV_ELEVATION_2:
	    nmea_set_int_data(&gsv->iaElevation[1],next);
	    break;
	  case GSV_AZIMUTH_2:
	    nmea_set_int_data(&gsv->iaAzimuth[1],next);
	    break;
	  case GSV_SNR_2:
	    nmea_set_int_data(&gsv->iaSNR[1],next);
	    break;
	  case GSV_SATELLITE_ID_3:
	    nmea_set_char_data(gsv->caSatelliteID[2],next,2);
	    break;
	  case GSV_ELEVATION_3:
	    nmea_set_int_data(&gsv->iaElevation[2],next);
	    break;
	  case GSV_AZIMUTH_3:
	    nmea_set_int_data(&gsv->iaAzimuth[2],next);
	    break;
	  case GSV_SNR_3:
	    nmea_set_int_data(&gsv->iaSNR[2],next);
	    break;  
	  case GSV_SATELLITE_ID_4:
	    nmea_set_char_data(gsv->caSatelliteID[3],next,2);
	    break;
	  case GSV_ELEVATION_4:
	    nmea_set_int_data(&gsv->iaElevation[3],next);
	    break;
	  case GSV_AZIMUTH_4:
	    nmea_set_int_data(&gsv->iaAzimuth[3],next);
	    break;
	  case GSV_SNR_4:
	    nmea_set_int_data(&gsv->iaSNR[3],next);
	    break;   
	  case GSV_CHECKSUM:
	    break;
	    
	}
	
	 field = (GSV_FIELDS)(field+1);
	 next = strtok_nmea(NULL,delim); 
      }
      
       free(msgt);
  return 0;
  
}	

int WriteGSV(GSV *gsv, char **msg, unsigned int *length)
{
    GSV_FIELDS field = GSV_MESSAGE_ID;
    
    *msg = NULL;
    
    int total_size;
    
    *length = 0;
    
    while (field <= GSV_CHECKSUM)
    {
      switch(field)
      {
	  case GSV_MESSAGE_ID:
	    nmea_write_char_data(gsv->caMessageID,msg,5,&total_size);
	    break;
	  case GSV_TOTAL_NUMBER_OF_MESSAGES:
	    nmea_write_int_data(&gsv->iTotalNumberOfMessages,msg,&total_size);
	    break;
	  case GSV_MESSAGE_NUMBER:
	    nmea_write_int_data(&gsv->iMessageNumber,msg,&total_size);
	    break;
	  case GSV_SATELLITES_IN_VIEW:
	    nmea_write_int_data(&gsv->iSatellitesInView,msg,&total_size);
	    break;
	  case GSV_SATELLITE_ID_1:
	    nmea_write_char_data(gsv->caSatelliteID[0],msg,2,&total_size);
	    break;
	  case GSV_ELEVATION_1:
	    nmea_write_int_data(&gsv->iaElevation[0],msg,&total_size);
	    break;
	  case GSV_AZIMUTH_1:
	    nmea_write_int_data(&gsv->iaAzimuth[0],msg,&total_size);
	    break;
	  case GSV_SNR_1:
	    nmea_write_int_data(&gsv->iaSNR[0],msg,&total_size);
	    break;
	  case GSV_SATELLITE_ID_2:
	    nmea_write_char_data(gsv->caSatelliteID[1],msg,2,&total_size);
	    break;
	  case GSV_ELEVATION_2:
	    nmea_write_int_data(&gsv->iaElevation[1],msg,&total_size);
	    break;
	  case GSV_AZIMUTH_2:
	    nmea_write_int_data(&gsv->iaAzimuth[1],msg,&total_size);
	    break;
	  case GSV_SNR_2:
	    nmea_write_int_data(&gsv->iaSNR[1],msg,&total_size);
	    break;
	  case GSV_SATELLITE_ID_3:
	    nmea_write_char_data(gsv->caSatelliteID[2],msg,2,&total_size);
	    break;
	  case GSV_ELEVATION_3:
	    nmea_write_int_data(&gsv->iaElevation[2],msg,&total_size);
	    break;
	  case GSV_AZIMUTH_3:
	    nmea_write_int_data(&gsv->iaAzimuth[2],msg,&total_size);
	    break;
	  case GSV_SNR_3:
	    nmea_write_int_data(&gsv->iaSNR[2],msg,&total_size);
	    break;  
	  case GSV_SATELLITE_ID_4:
	    nmea_write_char_data(gsv->caSatelliteID[3],msg,2,&total_size);
	    break;
	  case GSV_ELEVATION_4:
	    nmea_write_int_data(&gsv->iaElevation[3],msg,&total_size);
	    break;
	  case GSV_AZIMUTH_4:
	    nmea_write_int_data(&gsv->iaAzimuth[3],msg,&total_size);
	    break;
	  case GSV_SNR_4:
	    nmea_write_int_data(&gsv->iaSNR[3],msg,&total_size);
	    break;   
	  case GSV_CHECKSUM:
	    nmea_write_checksum(msg,&total_size);
	    break;
      }
      
      field = (GSV_FIELDS)(field+1);
    }
    
    *length = (unsigned int)total_size;
    
   return 0;
}

int ReadRMC(RMC *rmc, char *msg, unsigned int length)
{
  
     if (!msg)
	return NMEA_ERROR_NULL;
      if (*msg != '$')
	 return NMEA_ERROR_NO_$_SIGN;
      else
	 msg++;

      
      char *msgt = (char*)malloc(length);
      strncpy(msgt,msg,length - 1);
	
       char *testcs1 = strtok(msgt,"*");
      char *testcs2 = strtok(NULL,"\r");
      char cs[2];
      
      checksum_mtk(testcs1,length - 6, cs);
      
      if (strncmp(cs, testcs2,2))
      {
	 free(msgt);
	return NMEA_ERROR_CHECKSUM_CHECK_FAIL;
      }
      
      memcpy(rmc->caChecksum,testcs2,2);
      
      strncpy(msgt,msg,length-1);
      
      char delim = ',';
      char *next = strtok_nmea(msgt,delim);
      
      RMC_FIELDS field = RMC_MESSAGE_ID;
      
      while (field != RMC_CHECKSUM)
      {
	switch(field)
	{
	  case RMC_MESSAGE_ID:
	    nmea_set_char_data(rmc->caMessageID,next,5);
	  break;
	  case RMC_UTC_TIME:
	    nmea_set_char_data(rmc->caUTCTime,next,10);
	  break;
	  case RMC_STATUS:
	    nmea_set_char_data(&rmc->cStatus,next,1);
	  break;
	  case RMC_LATITUDE:
	    nmea_set_char_data(rmc->caLatitude,next,9);
	  break;
	  case RMC_NS_INDICATOR:
	    nmea_set_char_data(&rmc->cNSIndicator,next,1);
	  break;
	  case RMC_LONGITUDE:
	    nmea_set_char_data(rmc->caLongitude,next,10);
	  break;
	  case RMC_EW_INDICATOR:
	    nmea_set_char_data(&rmc->cEWIndicator,next,1);
	  break;
	  case RMC_SPEED_OVER_GROUND:
	    nmea_set_double_data(&rmc->dSpeedOverGround,next);
	  break;
	  case RMC_COURSE_OVER_GROUND:
	    nmea_set_double_data(&rmc->dCourseOverGround,next);
	  break;
	  case RMC_DATE:
	    nmea_set_char_data(rmc->caDate,next,6);
	  break;
	  case RMC_MAGNETIC_VARIATION:
	    nmea_set_int_data(&rmc->iMagneticVariation,next);
	  break;
	  case RMC_VARIATION_SENSE:
	    nmea_set_char_data(&rmc->cVariationSense,next,1);
	  break;
	  case RMC_MODE:
	    nmea_set_char_data(&rmc->cMode,next,1);
	  break;
	  case RMC_CHECKSUM:
	  break;
	}
	
	 field = (RMC_FIELDS)(field+1);
	 next = strtok_nmea(NULL,delim); 
      }
      
       free(msgt);

  return 0;
}

int WriteRMC(RMC *rmc, char **msg, unsigned int *length)
{
  RMC_FIELDS field = RMC_MESSAGE_ID;
    
    *msg = NULL;
    
    int total_size;
    
    *length = 0;
    
    while (field <= RMC_CHECKSUM)
    {
      switch(field)
      {
	  case RMC_MESSAGE_ID:
	    nmea_write_char_data(rmc->caMessageID,msg,5,&total_size);
	  break;
	  case RMC_UTC_TIME:
	    nmea_write_char_data(rmc->caUTCTime,msg,10,&total_size);
	  break;
	  case RMC_STATUS:
	    nmea_write_char_data(&rmc->cStatus,msg,1,&total_size);
	  break;
	  case RMC_LATITUDE:
	    nmea_write_char_data(rmc->caLatitude,msg,9,&total_size);
	  break;
	  case RMC_NS_INDICATOR:
	    nmea_write_char_data(&rmc->cNSIndicator,msg,1,&total_size);
	  break;
	  case RMC_LONGITUDE:
	    nmea_write_char_data(rmc->caLongitude,msg,10,&total_size);
	  break;
	  case RMC_EW_INDICATOR:
	    nmea_write_char_data(&rmc->cEWIndicator,msg,1,&total_size);
	  break;
	  case RMC_SPEED_OVER_GROUND:
	    nmea_write_double_data(&rmc->dSpeedOverGround,msg,&total_size);
	  break;
	  case RMC_COURSE_OVER_GROUND:
	    nmea_write_double_data(&rmc->dCourseOverGround,msg,&total_size);
	  break;
	  case RMC_DATE:
	    nmea_write_char_data(rmc->caDate,msg,6,&total_size);
	  break;
	  case RMC_MAGNETIC_VARIATION:
	    nmea_write_int_data(&rmc->iMagneticVariation,msg,&total_size);
	  break;
	  case RMC_VARIATION_SENSE:
	    nmea_write_char_data(&rmc->cVariationSense,msg,1,&total_size);
	  break;
	  case RMC_MODE:
	    nmea_write_char_data(&rmc->cMode,msg,1,&total_size);
	  break;
	  case RMC_CHECKSUM:
	    nmea_write_checksum(msg,&total_size);
	  break;
      }
      
      field = (RMC_FIELDS)(field+1);
    }
    
    *length = (unsigned int)total_size;
    
   return 0;
}

int ReadVTG(VTG *vtg, char *msg, unsigned int length)
{
     if (!msg)
	return NMEA_ERROR_NULL;
      if (*msg != '$')
	 return NMEA_ERROR_NO_$_SIGN;
      else
	 msg++;

      
      char *msgt = (char*)malloc(length);
      strncpy(msgt,msg,length - 1);
	
       char *testcs1 = strtok(msgt,"*");
      char *testcs2 = strtok(NULL,"\r");
      char cs[2];
      
      checksum_mtk(testcs1,length - 6, cs);
      
      if (strncmp(cs, testcs2,2))
      {
	 free(msgt);
	return NMEA_ERROR_CHECKSUM_CHECK_FAIL;
      }
      
      memcpy(vtg->caChecksum,testcs2,2);
      
      strncpy(msgt,msg,length-1);
      
      char delim = ',';
      char *next = strtok_nmea(msgt,delim);
      
      VTG_FIELDS field = VTG_MESSAGE_ID;
      
      while (field != VTG_CHECKSUM)
      {
	switch(field)
	{
	  case VTG_MESSAGE_ID:
	    nmea_set_char_data(vtg->caMessageID,next,5);
	    break;
	  case VTG_COURSE_OVER_GROUND:
	    nmea_set_double_data(&vtg->dCourseOverGround1,next);
	    break;
	  case VTG_REFERENCE_1:
	    nmea_set_char_data(&vtg->cReference1,next,1);
	    break;
	  case VTG_COURSE_OVER_GROUND_2:
	     nmea_set_double_data(&vtg->dCourseOverGround2,next);
	    break;
	  case VTG_REFERENCE_2:
	    nmea_set_char_data(&vtg->cReference2,next,1);
	    break;
	  case VTG_SPEED_OVER_GROUND_1:
	     nmea_set_double_data(&vtg->dSpeedOverGround1,next);
	    break;
	  case VTG_UNITS_1:
	    nmea_set_char_data(&vtg->cUnits1,next,1);
	    break;
	  case VTG_SPEED_OVER_GROUND_2:
	     nmea_set_double_data(&vtg->dSpeedOverGround2,next);
	    break;
	  case VTG_UNITS_2:
	    nmea_set_char_data(&vtg->cUnits2,next,1);
	    break;
	  case VTG_MODE:
	    nmea_set_char_data(&vtg->cMode,next,1);
	    break;
	  case VTG_CHECKSUM:
	    break;
	}
	
	 field = (VTG_FIELDS)(field+1);
	 next = strtok_nmea(NULL,delim); 
      }
      
       free(msgt);
  return 0;
  

}

int WriteVTG(VTG *vtg, char **msg, unsigned int *length)
{
  VTG_FIELDS field = VTG_MESSAGE_ID;
    
    *msg = NULL;
    
    int total_size;
    
    *length = 0;
    
    while (field <= VTG_CHECKSUM)
    {
      switch(field)
      {
	  case VTG_MESSAGE_ID:
	    nmea_write_char_data(vtg->caMessageID,msg,5,&total_size);
	    break;
	  case VTG_COURSE_OVER_GROUND:
	    nmea_write_double_data(&vtg->dCourseOverGround1,msg,&total_size);
	    break;
	  case VTG_REFERENCE_1:
	    nmea_write_char_data(&vtg->cReference1,msg,1,&total_size);
	    break;
	  case VTG_COURSE_OVER_GROUND_2:
	     nmea_write_double_data(&vtg->dCourseOverGround2,msg,&total_size);
	    break;
	  case VTG_REFERENCE_2:
	    nmea_write_char_data(&vtg->cReference2,msg,1,&total_size);
	    break;
	  case VTG_SPEED_OVER_GROUND_1:
	     nmea_write_double_data(&vtg->dSpeedOverGround1,msg,&total_size);
	    break;
	  case VTG_UNITS_1:
	    nmea_write_char_data(&vtg->cUnits1,msg,1,&total_size);
	    break;
	  case VTG_SPEED_OVER_GROUND_2:
	     nmea_write_double_data(&vtg->dSpeedOverGround2,msg,&total_size);
	    break;
	  case VTG_UNITS_2:
	    nmea_write_char_data(&vtg->cUnits2,msg,1,&total_size);
	    break;
	  case VTG_MODE:
	    nmea_write_char_data(&vtg->cMode,msg,1,&total_size);
	    break;
	  case VTG_CHECKSUM:
	    nmea_write_checksum(msg,&total_size);
	    break;	
      }
      
      field = (VTG_FIELDS)(field+1);
    }
    
    *length = (unsigned int)total_size;
    
   return 0;
}
