#include <string.h>
#include <errno.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>


#include "controller.h"
#include "tabs_message.h"
#include "nmea.h"

using namespace std;


Tabs_IO::Tabs_IO()
{

    	strncpy(cGGA.caMessageID,"0123456789",5);
	strncpy(cGGA.caUtcTime,"0123456789",10);
	strncpy(cGGA.caLatitude,"0123456789",9);
	cGGA.cNSIndicator = 'A';
	strncpy(cGGA.caLongitude,"0123456789",10);
	cGGA.cEWIndicator = 'A';
	cGGA.iPositionFixIndicator = 0;
	strncpy(cGGA.caSatellitesUsed,"0123456789",2);
	cGGA.dHDOP = 0.0;
	cGGA.dMSLAltitude = 0.0;
	cGGA.cUnits1 = 'A';
	cGGA.dGeoidSeparation = 0.0;
	cGGA.cUnits2 = 'A';
	cGGA.iAgeofDiffCorr = 0;
	strncpy(cGGA.caDiffREfStationID,"0123456789",4);
	strncpy(cGGA.caChecksum,"0123456789",2);

    	strncpy(cGLL.caMessageID,"0123456789",5);
	strncpy(cGLL.caLatitude,"0123456789",9);
	cGLL.cNSIndicator = 'A';
	strncpy(cGLL.caLongitude,"0123456789",10);
	cGLL.cEWIndicator = 'A';
	strncpy(cGLL.caUtcTime,"0123456789",10);
	cGLL.cStatus = 'A';
	cGLL.cMode = 'A';
	strncpy(cGLL.caChecksum,"0123456789",2);


    	strncpy(cGSA.caMessageID,"0123456789",5);
	cGSA.cMode1 = 'A';
	cGSA.cMode2 = 'A';
	for (int a = 0; a < 12;a++)
	{
		strncpy(cGSA.caIDofSatelliteUsed[a],"0123456789",2);
	}
	cGSA.dPDOP = 0;
	cGSA.dHDOP = 0;
	cGSA.dVDOP = 0;
	strncpy(cGSA.caChecksum,"0123456789",2);

	strncpy(cGSV.caMessageID,"0123456789",5);
	cGSV.iTotalNumberOfMessages = 0;
	cGSV.iMessageNumber = 0;
	cGSV.iSatellitesInView = 0;
	for (int b = 0; b < 4; b++)
	{
		strncpy(cGSV.caSatelliteID[b],"0123456789",2);	//channel 1 and 4
		cGSV.iaElevation[b] = 0;		//channel 1 and 4	
		cGSV.iaAzimuth[b] = 0;			//channel 1 and 4
		cGSV.iaSNR[b] = 0;				//channel 1 and 4
	}
	strncpy(cGSV.caChecksum,"0123456789",2);
  
    	strncpy(cRMC.caMessageID,"0123456789",5);
	strncpy(cRMC.caUTCTime,"0123456789",10);
	cRMC.cStatus = 'A';
	strncpy(cRMC.caLatitude,"0123456789",9);
	cRMC.cNSIndicator = 'A';
	strncpy(cRMC.caLongitude,"0123456789",10);
	cRMC.cEWIndicator = 'A';
	cRMC.dSpeedOverGround = 0;
	cRMC.dCourseOverGround = 0;
	strncpy(cRMC.caDate,"0123456789",6);
	cRMC.iMagneticVariation = 0;
	cRMC.cVariationSense = 'A';
	cRMC.cMode = 'A';
	strncpy(cRMC.caChecksum,"0123456789",2);


    	strncpy(cVTG.caMessageID,"0123456789",5);
	cVTG.dCourseOverGround1 = 0;
	cVTG.cReference1 = 'A';
	cVTG.dCourseOverGround2 = 0;
	cVTG.cReference2 = 'A';
	cVTG.dSpeedOverGround1 = 0;
	cVTG.cUnits1 = 'A';
	cVTG.dSpeedOverGround2 = 0;
	cVTG.cUnits2 = 'A';
	cVTG.cMode = 'A';
	strncpy(cVTG.caChecksum,"0123456789",2);




}

void Controller::Process()
{
	Tabs_Message	cMsg;
	
	memset(&cMsg,0,sizeof(Tabs_Message));	
	
	//send a message based on m_ePage
	cMsg.mtype = TAB_MSG_TYPE_NMEA_SENTENCE_ID;

	char *msg;
		
	switch (m_ePage)
	{
		case	PAGE_MAIN:
		case 	PAGE_GGA:
			msg = (char*)"GGA";
			break;
		case 	PAGE_GLL:
			msg = (char*)"GLL";
			break;
		case 	PAGE_GSA:
			msg = (char*)"GSA";
			break;
		case 	PAGE_GSV:
			msg = (char*)"GSV";
			break;
		case	PAGE_RMC:
			msg = (char*)"RMC";
			break;
		case 	PAGE_VTG:
			msg = (char*)"VTG";
			break;
		default:
			msg = (char*)"NONE";
	}

	strncpy(cMsg.mtext,msg,strlen(msg));
	
	if (msgsnd(m_iMsgID,&cMsg,TAB_MSG_LENGTH,IPC_NOWAIT) < 0)
	{
		if (errno == EAGAIN)
			cout << "Controller send message EAGAIN" << endl;
		else if (errno == EINTR)
		{
			cout << "Controller send message ENTR" << endl;	
			return;
		}
	}


	//retrieve message from comm
	Tabs_Message	cRetMsg;
	
	memset(&cRetMsg,0,sizeof(Tabs_Message));
	int iMsgSize;

	if ((iMsgSize =msgrcv(m_iMsgID,&cRetMsg,TAB_MSG_LENGTH,TAB_MSG_TYPE_NMEA_SENTENCE,MSG_NOERROR)) < 0)
	{
		if (errno == EIDRM)
		{
			cout << "Controller receieve EIDRM" << endl;
			return;
		}
		if (errno == ENOMSG)
		{
			cout << "Controller receive no message" << endl;
		}
	}
	else
	{
		cout << cRetMsg.mtext << endl;
	}
	
	Parse_Nmea_Sentence(cRetMsg.mtext,strlen(cRetMsg.mtext));

}

void	Controller::Parse_Nmea_Sentence(char *str, unsigned int length)
{
  
    if (!str)
      return;
    
    int ret = 0;
    
    
    if (!strncmp(str,"$GPGGA",6))
    {
      ret = ReadGGA(&(GetIO()->cGGA),str,length);
    }
    else if (!strncmp(str,"$GPGLL",6))
    {
      ret = ReadGLL(&(GetIO()->cGLL),str,length);
    }
    else if (!strncmp(str,"$GPGSA",6))
    {
      ret = ReadGSA(&(GetIO()->cGSA),str,length);
    }
    else if (!strncmp(str,"$GPGSV",6))
    {
      ret = ReadGSV(&(GetIO()->cGSV),str,length);
    }
    else if (!strncmp(str,"$GPRMC",6))
    {
      ret = ReadRMC(&(GetIO()->cRMC),str,length);
    }
    else if (!strncmp(str,"$GPVTG",6))
    {
      ret = ReadVTG(&(GetIO()->cVTG),str,length);
    }
    
    cout << "Ret is " << ret << endl;
      
 }

