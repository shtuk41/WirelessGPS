#ifndef __TABS_H
#define __TABS_H


#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QTime>
#include <QSpinBox>
#include "controller.h"

using namespace std;

class 	TabsCommon
{
public:
    virtual void Update(Controller *r) = 0;
    QString	ConvertMessageID(char *); 
    QString	ConvertUTC(char *in); 
    QString	ConvertLatitude(char *in); 
    QString	ConvertNSIndicator(char in);
    QString	ConvertLongitude(char *in); 
    QString	ConvertEWIndicator(char in); 
    QString	ConvertPositionFixIndicator(int in);
    QString	ConvertSatellitesUsed(char *in); 
    QString	ConvertHDOP(double in); 
    QString	ConvertPDOP(double in); 
    QString	ConvertVDOP(double in); 
    QString	ConvertMSLAltitude(double in); 
    QString	ConvertUnits(char in);
    QString	ConvertGeoidSeparation(double in);
    QString	ConvertAgeofDiffCorr(int in);
    QString	ConvertDiffRefStationID(char *in);
    QString	ConvertStatus(char in); 
    QString	ConvertMode(char in);
    QString	ConvertMode1(char in);
    QString	ConvertMode2(char in);
    QString	ConvertSatelliteID(char *in);
    QString	ConvertDate(char *in);
    QString	ConvertVariationSence(char in);
    QString	ConvertMagneticVariation(int in);
};

class	TabMAIN : public QWidget,TabsCommon
{
	Q_OBJECT;
public:
	TabMAIN(QWidget *parent = 0);
	
	void Update(Controller *r);
	
private slots:	
	void Sync();
	void SetLimit(int);
private:
	double	ConvertToRadians(double);
	double	GetLatitudeDegrees(char *);
	double	GetLongitudeDegrees(char *);
	int	ConvertCharToDigit(char);

	QLabel *m_caDistance_label;
	
	QString m_dDistance_string;
	
	QSpinBox *m_cDistanceLim_spinbox;
	
	QPushButton *m_cSync_pb;
	
	double	m_dDistanceLimit_meters;
	
	double	m_dFixedLatitude_deg;
	double	m_dFixedLongitude_deg;
	
	double	m_dCurrentObjectLatitude_deg;
	double	m_dCurrentObjectLongitude_deg;
	
	bool	m_bConnected;
	bool 	m_bConnected_Last;

};

class 	TabGGA : public QWidget,TabsCommon
{
  Q_OBJECT
public:
  TabGGA(QWidget *parent = 0);
  
  void Update(Controller *r);
  
private:
   QLabel *m_caMessageID_label;
   QLabel *m_caUTCTime_label;
   QLabel *m_caLatitude_label;
   QLabel *m_cNSIndicator_label;
   QLabel *m_caLongitude_label;
   QLabel *m_cEWIndicator_label;
   QLabel *m_iPositionFixIndicator_label;
   QLabel *m_caSatellitesUsed_label;
   QLabel *m_dHDOP_label;
   QLabel *m_dMSLAltitude_label;
   QLabel *m_cUnits1_label;
   QLabel *m_dGeoidSeparation_label;
   QLabel *m_cUnits2_label;
   QLabel *m_iAgeofDiffCorr_label;
   QLabel *m_caDiffREfStationID_label;
   QLabel *m_caChecksum_label;

   QString m_caMessageID_string;
   QString m_caUTCTime_string;
   QString m_caLatitude_string;
   QString m_cNSIndicator_string;
   QString m_caLongitude_string;
   QString m_cEWIndicator_string;
   QString m_iPositionFixIndicator_string;
   QString m_caSatellitesUsed_string;
   QString m_dHDOP_string;
   QString m_dMSLAltitude_string;
   QString m_cUnits1_string;
   QString m_dGeoidSeparation_string;
   QString m_cUnits2_string;
   QString m_iAgeofDiffCorr_string;
   QString m_caDiffREfStationID_string;
   QString m_caChecksum_string;
 };

class   TabGLL : public QWidget, TabsCommon
{
    Q_OBJECT
public:
  TabGLL(QWidget *parent = 0);
  
  void Update(Controller *r);
private:

	QLabel *m_caMessageID_label;
	QLabel *m_caLatitude_label;
	QLabel *m_cNSIndicator_label;
	QLabel *m_caLongitude_label;
	QLabel *m_cEWIndicator_label;
	QLabel *m_caUtcTime_label;
	QLabel *m_cStatus_label;
	QLabel *m_cMode_label;
	QLabel *m_caChecksum_label;

	QString m_caMessageID_string;
	QString m_caLatitude_string;
	QString m_cNSIndicator_string;
	QString m_caLongitude_string;
	QString m_cEWIndicator_string;
	QString m_caUtcTime_string;
	QString m_cStatus_string;
	QString m_cMode_string;
	QString m_caChecksum_string;

};

class 	TabGSA : public QWidget, TabsCommon
{
   Q_OBJECT
public:
  TabGSA(QWidget *parent = 0);
  void Update(Controller *r);

private:
  QLabel *m_caMessageID_label;
  QLabel *m_cMode1_label;
  QLabel *m_cMode2_label;
  QLabel *m_caIDofSatelliteUsed_label[12];
  QLabel *m_dPDOP_label;
  QLabel *m_dHDOP_label;
  QLabel *m_dVDOP_label;
  QLabel *m_caChecksum_label;

  QString m_caMessageID_string;
  QString m_cMode1_string;
  QString m_cMode2_string;
  QString m_caIDofSatelliteUsed_string[12];
  QString m_dPDOP_string;
  QString m_dHDOP_string;
  QString m_dVDOP_string;
  QString m_caChecksum_string;


};

class 	TabGSV : public QWidget, TabsCommon
{
    Q_OBJECT
public:
  TabGSV(QWidget *parent = 0);  
  void Update(Controller *r);

private:

    QLabel *m_caMessageID_label; 		
    QLabel *m_iTotalNumberOfMessages_label; 	
    QLabel *m_iMessageNumber_label; 	
    QLabel *m_iSatellitesInView_label; 		 
    QLabel *m_caSatelliteID1_label; 		
    QLabel *m_iaElevation1_label; 		
    QLabel *m_iaAzimuth1_label;			
    QLabel *m_iaSNR1_label; 			
    QLabel *m_caSatelliteID2_label; 		
    QLabel *m_iaElevation2_label; 		
    QLabel *m_iaAzimuth2_label;			
    QLabel *m_iaSNR2_label; 			
    QLabel *m_caSatelliteID3_label; 		
    QLabel *m_iaElevation3_label; 		
    QLabel *m_iaAzimuth3_label; 		
    QLabel *m_iaSNR3_label; 		
    QLabel *m_caSatelliteID4_label; 		
    QLabel *m_iaElevation4_label; 			
    QLabel *m_iaAzimuth4_label; 		
    QLabel *m_iaSNR4_label; 			
    QLabel *m_caChecksum_label; 

    QString m_caMessageID_string; 		
    QString m_iTotalNumberOfMessages_string; 	
    QString m_iMessageNumber_string; 	
    QString m_iSatellitesInView_string; 		 
    QString m_caSatelliteID1_string; 		
    QString m_iaElevation1_string; 		
    QString m_iaAzimuth1_string;			
    QString m_iaSNR1_string; 			
    QString m_caSatelliteID2_string; 		
    QString m_iaElevation2_string; 		
    QString m_iaAzimuth2_string;			
    QString m_iaSNR2_string; 			
    QString m_caSatelliteID3_string; 		
    QString m_iaElevation3_string; 		
    QString m_iaAzimuth3_string; 		
    QString m_iaSNR3_string; 		
    QString m_caSatelliteID4_string; 		
    QString m_iaElevation4_string; 			
    QString m_iaAzimuth4_string; 		
    QString m_iaSNR4_string; 			
    QString m_caChecksum_string; 		

};

class 	TabRMC : public QWidget, TabsCommon
{
     Q_OBJECT
public:
  TabRMC(QWidget *parent = 0); 
  void Update(Controller *r);

private:

    QLabel *m_caMessageID_label; 	
    QLabel *m_caUTCTime_label; 		
    QLabel *m_cStatus_label; 		
    QLabel *m_caLatitude_label; 	
    QLabel *m_cNSIndicator_label; 	 
    QLabel *m_caLongitude_label; 	
    QLabel *m_cEWIndicator_label; 	
    QLabel *m_dSpeedOverGround_label; 	 
    QLabel *m_dCourseOverGround_label; 	
    QLabel *m_caDate_label; 		
    QLabel *m_iMagneticVariation_label;
    QLabel *m_cVariationSense_label; 	
    QLabel *m_cMode_label; 	 
    QLabel *m_caChecksum_label; 

    QString m_caMessageID_string; 	
    QString m_caUTCTime_string; 		
    QString m_cStatus_string; 		
    QString m_caLatitude_string; 	
    QString m_cNSIndicator_string; 	 
    QString m_caLongitude_string; 	
    QString m_cEWIndicator_string; 	
    QString m_dSpeedOverGround_string; 	 
    QString m_dCourseOverGround_string; 	
    QString m_caDate_string; 		
    QString m_iMagneticVariation_string;
    QString m_cVariationSense_string; 	
    QString m_cMode_string; 	 
    QString m_caChecksum_string; 	
};

class 	TabVTG : public QWidget, TabsCommon
{
     Q_OBJECT
public:
  TabVTG(QWidget *pareTabGGAnt = 0); 
  void Update(Controller *r);
private:
    QLabel *m_caMessageID_label; 	
    QLabel *m_dCourseOverGround1_label; 
    QLabel *m_cReference1_label; 		
    QLabel *m_dCourseOverGround2_label; 
    QLabel *m_cReference2_label; 	
    QLabel *m_dSpeedOverGround1_label; 	
    QLabel *m_cUnits1_label; 		
    QLabel *m_dSpeedOverGround2_label; 	
    QLabel *m_cUnits2_label; 		
    QLabel *m_cMode_label; 		
    QLabel *m_caChecksum_label; 

    QString m_caMessageID_string; 	
    QString m_dCourseOverGround1_string; 
    QString m_cReference1_string; 		
    QString m_dCourseOverGround2_string; 
    QString m_cReference2_string; 	
    QString m_dSpeedOverGround1_string; 	
    QString m_cUnits1_string; 		
    QString m_dSpeedOverGround2_string; 	
    QString m_cUnits2_string; 		
    QString m_cMode_string; 		
    QString m_caChecksum_string; 	
};


class 	Tabs : public QDialog, TabsCommon
{
	Q_OBJECT
public:
  	Tabs(Controller *pC, QWidget *parent=0);
	void Update(Controller *r);

protected:
	void timerEvent(QTimerEvent *e);

private:
	TabMAIN	*m_pTabMAIN;	
	TabGGA	*m_pTabGGA;
	TabGLL	*m_pTabGGL;
	TabGSA	*m_pTabGSA;
	TabGSV	*m_bTabGSV;
	TabRMC	*m_bTabRMC;
	TabVTG	*m_bTabVTG;
  
  	Controller *pController;
	QTabWidget *tabWidget;
	QDialogButtonBox *buttonBox;
};


#endif

