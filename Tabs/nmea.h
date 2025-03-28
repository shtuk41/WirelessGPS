#ifndef __NMEA_H
#define __NMEA_H

#define 	NMEA_INT_UNDEF	-1
#define 	NMEA_DOUBLE_UNDEF -1

char 	*strtok_nmea(char *str, char c);
int 	nmea_field_valid(char *str);
void 	nmea_set_char_data(char *data, char *str, int size);
void 	nmea_set_double_data(double *data,char *str);
void 	nmea_set_int_data(int *data,char *str);

int 	nmea_write_char_data(char *data, char **str, int size, int *totalsize);
int 	nmea_write_int_data(int *data,char **str,int *totalsize);
int 	nmea_write_double_data(double *data,char **str,int *totalsize);
int 	nmea_write_checksum(char **str,int *totalsize);

/*
*	GGA		Global positioning system fixed data
	Message	ID					$GPGGA				GGA	protocol header
	UTC Time					053740.000			hhmmss.sss
	Latitude					2503.6319			ddmm.mmmm
	N/S indicator				N					N=north or S=south
	Longitude					12136.0099			dddmm.mmmm
	E/W Indicator				E					E=east or W=west
	Position Fix Indicator		1					0		Fix not available or invalid
													1		GPS SPS Mode, fix valid
													2		Differential GPS, SPS Mode, fix valid
													3-5		Not supported
													6		Dead Reckoning Mode, fix valid
	Satellites Used				08					Range 0 to 12
	HDOP						1.1					Horizontal Dilution of Precision
	MSL Altitude				63.8		meters	
	Units						M			meters
	Geoid Separation			15.2		meters
	Units						M			meters
	Age of Diff Corr.						second	Null fields when DGPS is not used
	Diff. Ref. Station ID		0000
	Checksum					*64


*	Example	$GPGGA,053740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64<CR><LF>
*/

typedef enum  {GGA_MESSAGE_ID, GGA_UTC_TIME,GGA_LATITUDE,GGA_NS_INDICATOR,GGA_LONGITUDE,GGA_EW_INDICATOR,GGA_POSITION_FIX_INDICATOR,
	      GGA_SATELLITES_USED,GGA_HDOP,GGA_MSL_ALTITUDE,GGA_UNITS1,GGA_GEOID_SEPARATION,GGA_UNITS2,GGA_AGE_OFF_DIFF_CORR,GGA_DIFF_REF_STATION_ID,GGA_CHECKSUM} GGA_FIELDS;

typedef struct
{
	char			caMessageID[5];
	char			caUtcTime[10];
	char			caLatitude[9];
	char			cNSIndicator;
	char			caLongitude[10];
	char			cEWIndicator;
	int			iPositionFixIndicator;
	char			caSatellitesUsed[2];
	double			dHDOP;
	double			dMSLAltitude;
	char			cUnits1;
	double			dGeoidSeparation;
	char			cUnits2;
	int			iAgeofDiffCorr;
	char			caDiffREfStationID[4];
	char			caChecksum[2];

} GGA;
/*
*	GLL		Geographic position - latitude/longitude
	Message ID		$GPGLL		GLL protocol header
	Latitude		2503.6319	ddmm.mmmm
	N/S indicator	N			N=north or S=south
	Longitude		12136.0099	dddmm.mmmm
	E/W indicator	E			E=case or W=west
	UTC Time		053740.000	hhmmss.sss
	Status			A			A=data valid or V=data not valid
	Mode			A			A=autonomous,D=DGPS,E=DR

	Example	$GPGLL,2503.6319,N,12136.0099,E,053740.000,A,A*52<CR><LF>
*/

typedef enum {GLL_MESSAGE_ID, GLL_LATITUDE,GLL_NS_INDICATOR, 
	      GLL_LONGITUDE,GLL_EW_INDICATOR, GLL_UTC_TIME,GLL_STATUS,GLL_MODE,GLL_CHECKSUM} GLL_FIELDS;

typedef struct
{
	char			caMessageID[5];
	char			caLatitude[9];
	char			cNSIndicator;
	char			caLongitude[10];
	char			cEWIndicator;
	char			caUtcTime[10];
	char			cStatus;
	char			cMode;
	char			caChecksum[2];
} GLL;
/*
*	GSA		GNSS DOP and active satellites
	Message ID				$GPGSA		GSA protocol header
	Mode 1					A			M	Manual-forced to operate in 2D or 3D mode
										A	Automatic-allowed to automatically switch 2D/3D
	Mode 2					3			1	Fix not available
										2	2D
										3	3D
	ID of satellite used	24			Sv on Channel 1
	ID of satellite used	07			Sv on Channel 2
	ID of satellite used	17			Sv on Channel 3
	ID of satellite used	11			Sv on Channel 4
	ID of satellite used	28			Sv on Channel 5
	ID of satellite used	08			Sv on Channel 6
	ID of satellite used	20			Sv on Channel 7
	ID of satellite used	04			Sv on Channel 8
	ID of satellite used				Sv on Channel 9
	ID of satellite used				Sv on Channel 10
	ID of satellite used				Sv on Channel 11
	ID of satellite used				Sv on Channel 12
	PDOP					2.0			Position Dilution of Precision
	HDOP					1.1			Horizontal Dilution of Precision
	VDOP					1.7			Vertical Diluttion of PRecision
	
	Example	$GPGSA,A,3,24,07,17,11,28,08,20,04,,,,,2.0,1.1,1.7*35
*/
typedef enum {GSA_MESSAGE_ID,GSA_MODE1,GSA_MODE2,
	      GSA_ID_SATELLITE_USED_CH1,
	      GSA_ID_SATELLITE_USED_CH2,
	      GSA_ID_SATELLITE_USED_CH3,
	      GSA_ID_SATELLITE_USED_CH4,
	      GSA_ID_SATELLITE_USED_CH5,
	      GSA_ID_SATELLITE_USED_CH6,
	      GSA_ID_SATELLITE_USED_CH7,
	      GSA_ID_SATELLITE_USED_CH8,
	      GSA_ID_SATELLITE_USED_CH9,
	      GSA_ID_SATELLITE_USED_CH10,
	      GSA_ID_SATELLITE_USED_CH11,
	      GSA_ID_SATELLITE_USED_CH12,
	      GSA_PDOP,
	      GSA_HDOP,
	      GSA_VDOP,
	      GSA_CHECKSUM} GSA_FIELDS;

typedef struct
{
	char			caMessageID[5];
	char			cMode1;
	char			cMode2;
	char			caIDofSatelliteUsed[12][2];
	double			dPDOP;
	double			dHDOP;
	double			dVDOP;
	char			caChecksum[2];
} GSA;
/*
*	GSV		GNSS satellites in view
	Message ID					$GPGSV				GSV protocol header
	Total Number of messages	3					Range 1 to 3
	Message Number				1					Range 1 to 3
	Satellites in view			12
	Satellite ID				28					Channel 1 (Range 01 to 32)
	Elevation					81		degrees		Channel 1 (Range 00 to 90)
	Azimuth						285		degrees		Channel 1 (Range 000 to 359)
	SNR (C/No)					42		dB-Hz		Channel 1 (Range 00 to 99, null when not tracking)
	Satellite ID				20					Channel 4 (Range 01 to 32)
	Elevation					51		degrees		Channel 4 (Range 00 to 90)
	Azimuth						077		degrees		Channel 4 (Range 000 to 359)
	SNR (C/No)					46		dB-Hz		CHannel 4 (Range 00 to 99, null when not tracking)


	Example $GPGSV,3,1,12,28,81,285,42,24,67,302,46,31,54,354,,20,51,077,46*73 
	Example $GPGSV,3,2,12,17,41,328,45,07,32,315,45,04,31,250,40,11,25,046,41*75 
	Example $GPGSV,3,3,12,08,22,214,38,27,08,190,16,19,05,092,33,23,04,127,*7B 


	Example	
*/

typedef enum {GSV_MESSAGE_ID,GSV_TOTAL_NUMBER_OF_MESSAGES,GSV_MESSAGE_NUMBER,
	      GSV_SATELLITES_IN_VIEW,
	      GSV_SATELLITE_ID_1,GSV_ELEVATION_1,GSV_AZIMUTH_1,GSV_SNR_1,
	      GSV_SATELLITE_ID_2,GSV_ELEVATION_2,GSV_AZIMUTH_2,GSV_SNR_2, 
	      GSV_SATELLITE_ID_3,GSV_ELEVATION_3,GSV_AZIMUTH_3,GSV_SNR_3,
	      GSV_SATELLITE_ID_4,GSV_ELEVATION_4,GSV_AZIMUTH_4,GSV_SNR_4,
	      GSV_CHECKSUM}  GSV_FIELDS;


typedef struct
{
	char		caMessageID[5];
	int		iTotalNumberOfMessages;
	int		iMessageNumber;
	int		iSatellitesInView;
	char		caSatelliteID[4][2];	//channel 1 and 4
	int		iaElevation[4];		//channel 1 and 4	
	int		iaAzimuth[4];			//channel 1 and 4
	int		iaSNR[4];				//channel 1 and 4
	char		caChecksum[2];
  
} GSV;
/*
*	RMC		Recommended minimum specific GNSS data
	Message ID			$GPRMC
	UTC Time			053740.000				hhmmss.sss
	Status				A						A=data valid or V=data not valid
	Latitude			2503.6319				ddmm.mmmm
	N/S Indicator		N						N=north or S=south
	Longitude			12136.0099				dddmm.mmmm
	E/W Indicator		E						E=east or W=west
	Speed over ground	2.69			knots	True
	Course over ground	79.65			degrees	
	Date				100106					ddmmyy
	Magnetic variation					degrees	
	Variation sense								E=east or W=west (Not shown)
	Mode				A						A=autonomous, D=DGPS,E=DR


	Example	$GPRMC,053740.000,A,2503.6319,N,12136.0099,E,2.69,79.65,100106,,,A*53
*/
typedef enum {RMC_MESSAGE_ID,RMC_UTC_TIME,RMC_STATUS,RMC_LATITUDE,RMC_NS_INDICATOR,RMC_LONGITUDE,RMC_EW_INDICATOR,RMC_SPEED_OVER_GROUND,RMC_COURSE_OVER_GROUND,
	      RMC_DATE,RMC_MAGNETIC_VARIATION,RMC_VARIATION_SENSE,RMC_MODE,RMC_CHECKSUM} RMC_FIELDS;


typedef struct
{
	char			caMessageID[5];
	char			caUTCTime[10];
	char			cStatus;
	char			caLatitude[9];
	char			cNSIndicator;
	char			caLongitude[10];
	char			cEWIndicator;
	double			dSpeedOverGround;
	double			dCourseOverGround;
	char			caDate[6];
	int			iMagneticVariation;
	char			cVariationSense;
	char			cMode;
	char			caChecksum[2];
} RMC;
/*
*	VTG		Course over ground and ground speed
	Message ID			$GPVTG			VTG protocol header
	Course over ground	79.65	degrees	Measured heading
	Reference			T				True
	Course over ground			degrees	Measured heading
	Reference			M				Magentic
	Speed over ground	2.69	knots	Measured speed
	Units				N		knots	
	Speed over ground	5.0		km/hr	Measured speed
	Units				K				Kilometer per hour
	Mode				A				A=autonomous,D=DGPS,E=DR



	Example		$GPVTG,79.65,T,,M,2.69,N,5.0,K,A*38 
*/

typedef enum {VTG_MESSAGE_ID, VTG_COURSE_OVER_GROUND,VTG_REFERENCE_1,VTG_COURSE_OVER_GROUND_2,
	      VTG_REFERENCE_2,VTG_SPEED_OVER_GROUND_1,VTG_UNITS_1,VTG_SPEED_OVER_GROUND_2,VTG_UNITS_2,
	      VTG_MODE,VTG_CHECKSUM} VTG_FIELDS;


typedef struct
{
	char			caMessageID[5];
	double			dCourseOverGround1;
	char			cReference1;
	double			dCourseOverGround2;
	char			cReference2;
	double			dSpeedOverGround1;
	char			cUnits1;
	double			dSpeedOverGround2;
	char			cUnits2;
	char			cMode;
	char			caChecksum[2];

} VTG;


int	ReadGGA(GGA *gga, char *msg, unsigned int length);
int	WriteGGA(GGA *gga, char **msg, unsigned int *length);
int	ReadGLL(GLL *gll, char *msg, unsigned int length);
int	WriteGLL(GLL *gll, char **msg, unsigned int *length);
int	ReadGSA(GSA *gsa, char *msg, unsigned int length);
int	WriteGSA(GSA *gsa, char **msg, unsigned int *length);
int 	ReadGSV(GSV *gsv, char *msg, unsigned int length);
int 	WriteGSV(GSV *gsv, char **msg, unsigned int *lenth);
int 	ReadRMC(RMC *rmc, char *msg, unsigned int length);
int 	WriteRMC(RMC *rmc, char **msg, unsigned int *length);
int 	ReadVTG(VTG *vtg, char *msg, unsigned int length);
int 	WriteVTG(VTG *vtg, char **msg, unsigned int *length);
	
	
	



#endif