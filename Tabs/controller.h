#ifndef __CONTROLLER_H
#define __CONTROLLER_H

#include "nmea.h"

enum 	CONTROLLER_PAGE {PAGE_MAIN = 0, PAGE_GGA, PAGE_GLL, PAGE_GSA, PAGE_GSV, PAGE_RMC, PAGE_VTG};

class 	Tabs_IO
{

public:
	Tabs_IO();

    GGA		cGGA;
    GLL		cGLL;
    GSA		cGSA;
    GSV		cGSV;
    RMC		cRMC;
    VTG		cVTG;
};




class 	Controller
{
public:
	Controller(int iMsgID) : m_iMsgID(iMsgID) {}
  	Tabs_IO*	GetIO() {return &cTab_IO;}
  	void 		SetPage(CONTROLLER_PAGE e) {m_ePage = e;}
  	void 		Process(); 
	void		Parse_Nmea_Sentence(char *, unsigned int);
  
private:
  	Tabs_IO	cTab_IO;
	CONTROLLER_PAGE 	m_ePage;
	int m_iMsgID;
};


#endif
