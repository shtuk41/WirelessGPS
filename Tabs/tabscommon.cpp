#include "tabs.h"

QString TabsCommon::ConvertMessageID(char *in)
{
	QString s;
	
	if (!in)
		s = "UNAVAILABLE";
	else if (!strncmp(in,"GPGGA",5))
		s = "Global Positioning System Fixed Data";
	else if (!strncmp(in,"GPGLL",5))
		s = "Geographic Position Lat Lon";
	else if (!strncmp(in,"GPGSA",5))
		s = "GNSS DOP and Active Satellites";
	else if (!strncmp(in,"GPGSV",5))
		s = "GNSS Satellites in View";
	else if (!strncmp(in,"GPRMC",5))
		s = "Recommended Minimum Specific GNSS Data";	
	else if (!strncmp(in,"GPVTG",5))
		s = "Course Over Ground and Ground Speed";	

		
	return s;	
}

QString TabsCommon::ConvertUTC(char *in)
{
	QString s;
	
	if (!in)
		s = "UNAVAILABLE";
	else
		s.sprintf("%c%c Hours %c%c Minutes %c%c Seconds",in[0],in[1],in[2],in[3],in[4],in[5]);

		
	return s;	
}

QString	TabsCommon::ConvertLatitude(char *in)
{
	QString s;
	
	if (!in || !isdigit(in[0]))
		s = "UNAVAILABLE";
	else
	{
	
		s.sprintf("%c%c Degrees %c%c.%c%c%c%c Minutes ",in[0],in[1],in[2],in[3],in[5],in[6],in[7],in[8]);
	}
	
	return s;
}

QString	TabsCommon::ConvertNSIndicator(char in)
{
	QString s;

	if (in == 'N' || in == 'n')
		s = "North";
	else if (in == 'S' || in == 's')
		s = "South";
	else
		s = "UNAVAILABLE";
		
	return s;
}

QString	TabsCommon::ConvertLongitude(char *in)
{

	QString s;
	
	if (!in || !isdigit(in[0]))
		s = "UNAVAILABLE";
	else
	{
		s.sprintf("%c%c%c Degrees %c%c.%c%c%c%c Minutes",in[0],in[1],in[2],in[3],in[4],in[6],in[7],in[8],in[9]);
	}
	
	return s;	
	
} 

 QString	TabsCommon::ConvertEWIndicator(char in)
 {
 	QString s;

	if (in == 'E' || in == 'e')
		s = "East";
	else if (in == 'W' || in == 'w')
		s = "West";
	else
		s = "UNAVAILABLE";
		
	return s;
 }
 
 QString	TabsCommon::ConvertPositionFixIndicator(int in)
 {
	QString s;
	
	switch (in)
	{
		case 0:
			s = "Fix not available or invalid";
		break;
		case 1:
			s = "GPS SPS Mode, fix valid";
		break;
		case 2:
			s = "Differential GPS, SPS Mode, fix valid";
		break;
		case 6:
			s = "Dead Reckoning Mode, fix valid";
		default:
			s = "UNAVAILABLE";
	}
	
	return s;
 }
 
 QString	TabsCommon::ConvertSatellitesUsed(char *in)
 {
 	QString s;

	if (!in || !isdigit(in[0]) || !isdigit(in[1]))
		s = "UNAVAILABLE";
	else
	{
		s.sprintf("%c%c",in[0],in[1]);
	}
		
	return s;
 }
 
  QString	TabsCommon::ConvertHDOP(double in)
  {
	QString s;
	
	if (in == -1)
		s = "UNAVAILABLE";
	else 
		s.sprintf("%f",in);
		
	return s;
  }
  
  QString	TabsCommon::ConvertPDOP(double in)
  {
  	QString s;
	
	if (in == -1)
		s = "UNAVAILABLE";
	else 
		s.sprintf("%f",in);
		
	return s;
  }
  
  QString	TabsCommon::ConvertVDOP(double in)
  {
  	QString s;
	
	if (in == -1)
		s = "UNAVAILABLE";
	else 
		s.sprintf("%f",in);
		
	return s;
  }  
  
  QString	TabsCommon::ConvertMSLAltitude(double in)
  {
  	QString s;
	
	if (in == -1.0)
		s = "UNAVAILABLE";
	else 
		s.sprintf("%f",in);
		
	return s;
  }
  
  QString	TabsCommon::ConvertUnits(char in)
  {
   	QString s;
	
	if (in == 'M' || in == 'm')
		s = "Meters";
	else if (in == 'N' || in == 'n')
		s = "Knots";
	else if (in == 'K' || in == 'k')
		s = "Kilometer per hour";				
	else 
		s = "UNDEFINED";
		
	return s;
  }
  
  QString	TabsCommon::ConvertGeoidSeparation(double in)
  {
    	QString s;
	
	if (in == -1.0)
		s = "UNAVAILABLE";
	else 
		s.sprintf("%f",in);
		
	return s;
  }
  
  QString	TabsCommon::ConvertAgeofDiffCorr(int in)
  {
	QString s;
	
	if (in < 0)
		s = "UNAVAILABLE";
	else
		s.sprintf("%d seconds",in);
	
	return s;
  }
  
  QString	TabsCommon::ConvertDiffRefStationID(char *in)
  {
  	QString s;
	
	s = "0000";
	
	return s;
  }
  
 QString	TabsCommon::ConvertStatus(char in)
 {
  	QString s;
	
	if (in == 'A' || in == 'A')
		s = "Data Valid";
	else if (in == 'V' || in == 'v')
		s = "Data Invalid";
	else 
		s = "UNDEFINED";
		
	return s;
 }
 
 QString	TabsCommon::ConvertMode(char in)
 {
   	QString s;
	
	if (in == 'A' || in == 'A')
		s = "Autonomous";
	else if (in == 'D' || in == 'd')
		s = "DGPS";
	else if (in == 'E' || in == 'e')
		s = "DR";		
	else 
		s = "UNDEFINED";
		
	return s;
 }
 
 QString	TabsCommon::ConvertMode1(char in)
 {
    	QString s;
	
	if (in == 'M' || in == 'm')
		s = "Manual-forced to operation in 2d or 3d";
	else if (in == 'A' || in == 'a')
		s = "Automatic-allowed to automatically switch 2D or 3D";
	else 
		s = "UNDEFINED";
		
	return s;
 }
 
 QString	TabsCommon::ConvertMode2(char in)
 {
 	QString s;
	
	if (in == '1')
		s = "Fix not available";
	else if (in == '2')
		s = "2D";
	else if (in == '3')
		s = "3D";		
	else 
		s = "UNDEFINED";
		
	return s;
 }
 
 QString	TabsCommon::ConvertSatelliteID(char *in)
 {
  	QString s;

	if (!in || !isdigit(in[0]) || !isdigit(in[1]))
		s = "UNAVAILABLE";
	else
	{
		s.sprintf("%c%c",in[0],in[1]);
	}
		
	return s;
 }
 
 QString	TabsCommon::ConvertDate(char *in)
 {
  	QString s;

	if (!in || !isdigit(in[0]) || !isdigit(in[1]))
		s = "UNAVAILABLE";
	else
	{
		s.sprintf("Day: %c%c Month: %c%c Year: %c%c",in[2],in[3],in[0],in[1],in[4],in[5]);
	}
		
	return s;
 }
 
 QString	TabsCommon::ConvertVariationSence(char in)
 {
  	QString s;
	
	if (in == 'E' || in == 'e')
		s = "East";
	else if (in == 'W' || in == 'w')
		s = "West";
	else 
		s = "UNDEFINED";
		
	return s;
 }
 
 QString	TabsCommon::ConvertMagneticVariation(int in)
 {
   	QString s;
	
	if (in == -1)
		s = "UNDEFINED";
	else
		s.sprintf("%d",in);
		
	return s;
}
 
 