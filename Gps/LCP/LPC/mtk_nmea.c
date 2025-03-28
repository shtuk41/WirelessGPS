
#include <string.h>
#include <stdlib.h>
#include "mtk_nmea.h"


char	hexchar(int i)
{
	char r = '%';

	switch(i)
	{
		case 0x0:
			r = '0';
			break;
		case 0x1:
			r = '1';
			break;
		case 0x2:
			r = '2';
			break;
		case 0x3:
			r = '3';
			break;
		case 0x4:
			r = '4';
			break;
		case 0x5:
			r = '5';
			break;
		case 0x6:
			r = '6';
			break;
		case 0x7:
			r = '7';
			break;
		case 0x8:
			r = '8';
			break;
		case 0x9:
			r = '9';
			break;
		case 0xa:
			r = 'A';
			break;
		case 0xb:
			r = 'B';
			break;
		case 0xc:
			r = 'C';
			break;
		case 0xd:
			r = 'D';
			break;
		case 0xe:
			r = 'E';
			break;
		case 0xf:
			r = 'F';
			break;
	}

	return r;
}


void	checksum_mtk(char *line, int size, char cs[2])
{
	int i;

	int checksum = (int)line[0];

	for (i = 1; i < size;i++)
	{
		int next = (int)line[i];
		checksum ^= next;			
	}

	cs[0] = hexchar(checksum >> 4);
	cs[1] = hexchar(checksum & 0x0F);
}

int PMTK_TEST_000(char **out)
{
	char	*str = "$PMTK000*32\r\n";

	int size = strlen(str);
	*out = (char*)malloc(size);

	memcpy(*out,str,size);

	return size;
}

int PMTK_ACK_001(char **out, char c)
{
	char *str = "$PMTK001,101,";
	int length = strlen(str);
	*out = (char *)malloc(length + 6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c; n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

int PMTK_SYS_MSG_010(char **out,char c)
{
	char *str = "$PMTK010,00";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

int PMTK_CMD_HOT_START_101(char **out)
{
	char *str = "$PMTK101*32\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int PMTK_CMD_WARM_START_102(char **out)
{
	char *str = "$PMTK102*31\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int	PMTK_CMD_COLD_START_103(char **out)
{
	char *str = "$PMTK103*30\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int	PMTK_CMD_FULL_COLD_START_104(char **out)
{
	char *str = "$PMTK104*37\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int PMTK_API_SET_DGPS_MODE_301(char **out,char c)
{
	char *str = "$PMTK301,";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;

}

int	PMTK_API_SET_SBAS_ENABLED_313(char **out, char c)
{
	char *str = "$PMTK313,";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

/*#define	NMEA_SEN_GLL		0	
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
#define	NMEA_SEN_MDBG		16	*/

int	PMTK_API_SET_NMEA_OUTPUT_314(char **out, char setting[17],int reset)
{
	 if (reset)
	 {
		char *str = "$PMTK314,-1*04\r\n";
		int length = strlen(str);
		*out = (char*)malloc(length);
		memcpy(*out,str,length);
		return length;
	 }

	char *str = "$PMTK314,";
	int length = strlen(str);
	*out = (char*)malloc(length + 38);
	memcpy(*out,str,length);
	char *n = *out + length;
	int count = 0;
	for (;count<17;count++)
	{
		*n = setting[count];
		n++;

		if (count != 16)
		{
			*n = ',';
			n++;
		}
	}

	char cs[2];
	checksum_mtk(*out + 1,length + 32,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 38;
}


int PMTK_API_SET_PWR_SAV_MODE_320(char **out, char c)
{
	char *str = "$PMTK320,";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

int		PMTK_API_Q_DGPS_MODE_401(char **out)
{
	char *str = "$PMTK401*37\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int		PMTK_API_Q_SBAS_ENABLED_413(char **out)
{
	char *str = "$PMTK413*34\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int		PMTK_API_Q_NMEA_OUTPUT_414(char **out)
{
	char *str = "$PMTK414*33\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}


int		PMTK_API_Q_PWR_SAV_MOD_420(char **out)
{
	char *str = "$PMTK420*34\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int PMTK_DT_DGPS_MODE_501(char **out, char c)
{
	char *str = "$PMTK501,";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

int PMTK_DT_SBAS_ENABLED_513(char **out,char c)
{
char *str = "$PMTK513,";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

int PMTK_DT_NMEA_OUTPUT_514(char **out, char setting[17])
{
	char *str = "$PMTK514,";
	int length = strlen(str);
	*out = (char*)malloc(length + 38);
	memcpy(*out,str,length);
	char *n = *out + length;
	int count = 0;
	for (;count<17;count++)
	{
		*n = setting[count];
		n++;

		if (count != 16)
		{
			*n = ',';
			n++;
		}
	}

	char cs[2];
	checksum_mtk(*out + 1,length + 32,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 38;
}

int	PMTK_DT_PWR_SAV_MODE_520(char **out,char c)
{
	char *str = "$PMTK520,";
	int length = strlen(str);
	*out = (char*)malloc(length+6);
	memcpy(*out,str,length);
	char *n = (*out + length);
	*n = c;
	n++;
	char cs[2];
	checksum_mtk(*out + 1,length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 6;
}

int		PMTK_Q_VERSION_604(char **out)
{
	char *str = "$PMTK604*30\r\n";
	int length = strlen(str);
	*out = (char*)malloc(length);
	memcpy(*out,str,length);

	return length;
}

int		PMTK_DT_VERSION_704(char **out, char *FWVrsn1, char*FWVrsn2, char*FWVrsn3)
{
	char *str = "$PMTK704,";
	int length = strlen(str);
	int v1length = strlen(FWVrsn1);
	int v2length = strlen(FWVrsn2);
	int v3length = strlen(FWVrsn3);
	*out = (char*)malloc(length + 2 + v1length + v2length + v3length + 5);
	memcpy(*out,str,length);
	char *n = (*out + length);
	memcpy(n,FWVrsn1,v1length);
	n+=v1length;
	*n=',';n++;
	memcpy(n,FWVrsn2,v2length);
	n+=v2length;
	*n=',';n++;
	memcpy(n,FWVrsn3,v3length);
	n+=v3length;

	char cs[2];
	checksum_mtk(*out + 1,length + 1 + v1length + v2length + v3length,cs);
	*n = '*';n++;
	*n = cs[0];n++;
	*n = cs[1];n++;
	*n = '\r';n++;
	*n = '\n';

	return length + 2 + v1length + v2length+ v3length + 5;
}