#ifndef __MTK_NMEA
#define __MTK_NMEA


#define PREAMBLE	'$'
#define TALKDERID	"PMTK"
#define	CR			'\r'	//0x0D
#define LF			'\n'	//0x0A
#define COMMA		','

char	hexchar(int i);


/*
	line		- buffer of bytes to perform checksum
	size		- size of buffer line
	cs			- 2 byte output	
	algorithm	- xor of all bytes in buffer line

*/
void	checksum_mtk(char *line, int size, char cs[2]);


/*
	Packet Type		:		000 PMTK_TEST
	Packet Meaning	:		Test Packet
	Data Field		:		None
	Example			:		$PMTK000*32<CR><LF>
*/

int PMTK_TEST_000(char **out);


/*
	Packet Type		:		001 PMTK_ACK
	Packet Meaning	:		Acknowledge packet
	Data Field		:		PktType:  The packet type the acknowledge response
							'0' = invalid packet
							'1' = unsupported packet type
							'2' = valid packet, but action failed
							'3' = valid packet, and action succeeded
	Example			:		$PMTK001,101,0*33<CR><LF>
*/


#define		PMTK_ACK_001_0		'0' //invalid packet
#define		PMTK_ACK_001_1		'1' //unsupported packet type
#define		PMTK_ACK_001_2		'2' //valid packet, but action failed
#define		PMTK_ACK_001_3		'3' //valid packet, and action succeeded


int PMTK_ACK_001(char **out, char c);

/*
	Packet Type		:		010 PMTK_SYS_MSG
	Packet Meaning	:		Output system message
	Data Field		:		Msg: The system message
							'0' = UNKNOWN
							'1' = STARTUP
	Example			:		$PMTK010,001*2E<CR><LF>
*/

#define		PMTK_SYS_MSG_010_0		'0' //UNKNOWN
#define		PMTK_SYS_MSG_010_1		'1' //STARTUP

int PMTK_SYS_MSG_010(char **out,char c);

/*
	Packet Type		:		101 PMTK_CMD_HOT_START
	Packet Meaning	:		Hot Start: Use all available data in the NV Store
	Data Field		:		none
	Example			:		$PMTK101*32<CR><LF>
*/

int PMTK_CMD_HOT_START_101(char **out);

/*
	Packet Type		:		102 PMTK_CMD_WARM_START
	Packet Meaning	:		Warm Restart: Don't use Ephemmeris at re-start
	Data Field		:		none
	Example			:		$PMTK102*31<CR><LF>
*/

int PMTK_CMD_WARM_START_102(char **out);

/*
	Packet Type		:		103 PMKT_CMD_COLD_START
	Packet Meaning	:		Cold Restart: Don't use Time, Position, Almanacs and Ephemeris data at re-start
	Data Field		:		none
	Example			:		$PMTK103*30<CR><CL>
*/

int	PMTK_CMD_COLD_START_103(char **out);

/*
	Packet Type		:		104 PMTK_CMD_FULL_COLD_START
	Packet Meaning	:		Full Cold Restart: It's essentially a Cold Restart, but additionally clear system/user
							configurations at re-start.  That is, reset the receiver to the factory status.
	Data Field		:		none
	Example			:		$PMTK104*37<CR><CL>
*/


int	PMTK_CMD_FULL_COLD_START_104(char **out);

/*
	Packet Type		:		301 PMTK_API_SET_DGPS_MODE
	Packet Meaning	:		API_Set_Dgps_Mode
							DGPS correction data source mode
	Data Field		:		PMTK301,Mode
							Mode: DGPS data source mode
							'0':	No DGPS source
							'1':	RTCM
							'2':	WAAS
	Example			:		$PMTK301,1*2D<CR><CL>
*/

#define		PMTK_API_SET_DGPS_MODE_301_0 '0'
#define		PMTK_API_SET_DGPS_MODE_301_1 '1'
#define		PMTK_API_SET_DGPS_MODE_301_2 '2'

int PMTK_API_SET_DGPS_MODE_301(char **out,char c);

/*
	Packet Type		:		313 PMTK_API_SET_SBAS_ENABLED
	Packet Meaning	:		API_Set_Sbas_Enabled
							Enable to search a SBAS satellite or not
	Data Field		:		Enabled: Enable or disable
							'0' = Disable
							'1' = Enable
	Example			:		$PMTK313,1*2E<CR><CL>
*/

#define		PMTK_API_SET_SBAS_ENABLED_313_0	'0'
#define		PMTK_API_SET_SBAS_ENABLED_313_1 '1'

int	PMTK_API_SET_SBAS_ENABLED_313(char **out, char c);

/*
	Packet Type		:		314 PMTK_API_SET_NMEA_OUTPUT
	Packet Meaning	:		API_Set_NMEA_Out
							Set NMEA sentence output frequencies
	Data Field		:		There are totally 17 data fields that present output frequencies for the 17 supported NMEA sentences individually
							Supported NMEA Sentences

							0	NMEA_SEN_GLL,	//GPGLL interval - Geographic Position - Latitude longitude
							1	NMEA_SEN_RMC,	//GPRMC interval - Recommended Minimum Specific GNSS Sentence
							2	NMEA_SEN_VTG,	//GPVTG interval - Course Over Ground and Ground Speed
							3	NMEA_SEN_GGA,	//GPGGA interval - GPS Fix Data
							4	NMEA_SEN_GSA,	//GPGSA interval - GNSS DOPS and Active Satellites
							5	NMEA_SEN_GSV,	//GPGSV interval - GNSS Satellites in View
							6	NMEA_SEN_GRS,	//GPGRS interval - GNSS Range Residuals
							7	NMEA_SEN_GST,	//GPGST interval - GNSS Pseudorange Errors Statistics
							13	NMEA_SEN_MALM,	//PMTKALM interval - GPS almanac information
							14  NMEA_SEN_MEPH,	//PMTKEPH interval - GPS ephmeris information
							15	NMEA_SEN_MDGP,	//PMTKDGP interval - GPS differential correction information
							16	NMEA_SEN_MDBG,	//PMTKDBG interval - MTK debug information

							Supported Frequency Setting
							0 - Disable or not supported sentence
							1 - Output once every one position fix
							2 - Output once every two position fixes
							3 - Output once every three position fixes
							4 - Output once every four position fixes
							5 - Output once every five position fixes


	Example			:		$PMTK314,1,1,1,1,1,5,1,1,1,1,1,1,0,1,1,1,1*2C<CR><CL>

							This command set GLL output frequency to be outputting once every 1 position fix, and RMC to be outputting
							once every  1 position fix, etc.
							You can also restore the system default setting via issue

							$PMTK314,-1*04<CR<LF>
*/

#define	NMEA_SEN_GLL		0	
#define	NMEA_SEN_RMC		1	
#define	NMEA_SEN_VTG		2	
#define	NMEA_SEN_GGA		3	
#define	NMEA_SEN_GSA		4	
#define	NMEA_SEN_GSV		5	
#define	NMEA_SEN_GRS		6	
#define	NMEA_SEN_GST		7
#define NMEA_SEN_8			8
#define	NMEA_SEN_9			9
#define NMEA_SEN_10			10
#define NMEA_SEN_11			11
#define NMEA_SEN_12			12
#define	NMEA_SEN_MALM		13	
#define	NMEA_SEN_MEPH		14  
#define	NMEA_SEN_MDGP		15	
#define	NMEA_SEN_MDBG		16	

#define		PMTK_API_SET_NMEA_OUTPUT_314_0	'0'
#define		PMTK_API_SET_NMEA_OUTPUT_314_1	'1'
#define		PMTK_API_SET_NMEA_OUTPUT_314_2	'2'
#define		PMTK_API_SET_NMEA_OUTPUT_314_3	'3'
#define		PMTK_API_SET_NMEA_OUTPUT_314_4	'4'
#define		PMTK_API_SET_NMEA_OUTPUT_314_5	'5'


int	PMTK_API_SET_NMEA_OUTPUT_314(char **out, char setting[17],int reset);

/*
	Packet Type		:		320 PMTK_API_SET_PWR_SAV_MODE
	Packet Meaning	:		API_Set_Pwr_Sav_Mode
							Set power saving operation mode
	Data Field		:		PMTK320,Mode
							Mode: 
							0: PWR_SAV_OFF: power saving mode off
							1: PWR_SAV_ON:	power saving mode on
	Example			:		$PMTK320,0*26<CR><CL>
*/

#define		PMTK_API_SET_PWR_SAV_MODE_0	'0'
#define		PMTK_API_SET_PWR_SAV_MODE_1 '1'

int PMTK_API_SET_PWR_SAV_MODE_320(char **out, char c);

/*
	Packet Type		:		401 PMTK_API_Q_DGPS_MODE
	Packet Meaning	:		API_Query_Dgps_Mode
	Data Field		:		None
	Return			:		PMTK_DT_DGPS_MODE
	Example			:		$PMTK401*37<CR><LF>
*/

int		PMTK_API_Q_DGPS_MODE_401(char **out);

/*
	Packet Type		:		413 PMTK_API_Q_SBAS_ENABLED
	Packet Meaning	:		API_Query_Sbas_Enabled
	Data Field		:		None
	Return			:		PMTK_DT_SBAS_ENABLED
	Example			:		$PMTK413*34<CR><LF>
*/

int		PMTK_API_Q_SBAS_ENABLED_413(char **out);

/*
	Packet Type		:		414 PMTK_API_Q_NMEA_OUTPUT
	Packet Meaning	:		API_Query_NMEA_Out
							Query current NMEA sentence output frequencies
	Data Field		:		None
	Return			:		PMTK_DT_NMEA_OUTPUT
	Example			:		$PMTK414*33<CR><LF>
*/

int		PMTK_API_Q_NMEA_OUTPUT_414(char **out);

/*
	Packet Type		:		420 PMTK_API_Q_PWR_SAV_MOD
	Packet Meaning	:		API_Query_Pwr_Sav_Mode
							Query power saving operation mode.
	Data Field		:		None
	Return			:		PMTK_DT_PWR_SAV_MODE
	Example			:		$PMTK420*3F<CR><LF>
*/

int		PMTK_API_Q_PWR_SAV_MOD_420(char **out);

/*
	Packet Type		:		501 PMTK_DT_DGPS_MODE
	Packet Meaning	:		DGPS Data Source Mode
	Data Field		:		Mode: DGPS source mode
							'0': No DGPS source
							'1':RTCM
							'2':WAAS
	Example			:		$PMTK501,1*2B<CR><LF>
*/

#define	PMTK_DT_DGPS_MODE_501_0	'0'
#define PMTK_DT_DGPS_MODE_501_1	'1'
#define PMTK_DT_DGPS_MODE_501_2	'2'

int PMTK_DT_DGPS_MODE_501(char **out, char c);

/*
	Packet Type		:		513 PMTK_DT_SBAS_ENABLED
	Packet Meaning	:		Enable to search a SBAS or not
	Data Field		:		Enabled: Enable or disable
							'0': Disable
							'1': Enable
	Example			:		$PMTK513,1*28<CR><LF>
*/

#define PMTK_DT_SBAS_ENABLED_513_0	'0'
#define PMTK_DT_SBAS_ENABLED_513_1	'1'

int PMTK_DT_SBAS_ENABLED_513(char **out,char c);

/*
	Packet Type		:		514 PMTK_DT_NMEA_OUTPUT
	Packet Meaning	:		NMEA sentence output frequency setting
	Data Field		:		There are totally 17 data fields that present output frequencies for the 17 supported
							NMEA sentences individually.  Please refere to PMTK_API_SET_NMEA_OUTPUT for the Supported NMEA
							Sentences and Frequency Setting
	Example			:		$PMTK514,1,1,1,1,1,5,1,1,1,1,1,1,0,1,1,1,1*2A<CR><LF>

							I'm not sure if reset is available, see PMTK_API_SET_NMEA_OUTPUT_314 for example
*/



int PMTK_DT_NMEA_OUTPUT_514(char **out, char setting[17]);

/*
	Packet Type		:		520 PMTK_DT_PWR_SAV_MODE
	Packet Meaning	:		Power saving operation mode
	Data Field		:		PMTK520,Mode
							Mode	0: PWR_SAV_OFF: power saving mode off
									1: PWR_SAV_ON: power saving mode on
	Example			:		$PMTK520,0*24<CR><LF>
*/

#define		PMTK_DT_PWR_SAV_MODE_520_0 '0'
#define		PMTK_DT_PWR_SAV_MODE_520_1 '1'

int	PMTK_DT_PWR_SAV_MODE_520(char **out,char c);

/*
	Packet Type		:		604	PMTK_Q_VERSION
	Packet Meaning	:		Query the version information of FW
	Data Field		:		NONE
	Return			:		PMTK_DT_VERSION
	Example			:		$PMTK604*6D<CR><LF>
*/

int		PMTK_Q_VERSION_604(char **out);

/*
	Packet Type		:		704	PMTK_DT_VERSION
	Packet Meaning	:		Version information of FW
	Data Field		:		PMTK704,FWVrsn1, FWvrsn2, FWVrsn3
							Vrns: MainVersion_ReleaseNumber
	Example			:		$PMTK704,1.881_06,0606_m0138,0000*52<CR><LF>
*/

int		PMTK_DT_VERSION_704(char **out, char *FWVrsn1, char*FWVrsn2, char*FWVrsn3);


#endif