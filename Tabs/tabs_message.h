#ifndef __TABS_MESSAGE_H
#define __TABS_MESSAGE_H

#define		TAB_MSG_LENGTH			512
#define 	TAB_MSG_TYPE_NMEA_SENTENCE_ID	1
#define 	TAB_MSG_TYPE_NMEA_SENTENCE	2	


typedef struct 
{
	long mtype;
	char mtext[TAB_MSG_LENGTH];
} Tabs_Message;




#endif
