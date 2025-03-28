#include "tabs.h"
#include <iostream>
#include <math.h>


using namespace std;


TabMAIN::TabMAIN(QWidget *parent) : QWidget(parent)
{
	m_dFixedLatitude_deg		= 0.0;
	m_dFixedLongitude_deg		= 0.0;
	
	m_dCurrentObjectLatitude_deg	= 0.0;
	m_dCurrentObjectLongitude_deg	= 0.0;	
	
	m_bConnected			= false;


	QLabel *caSetLimits_label = new QLabel(tr("SET LIMIT"),parent);
	QFont caSetLimits_label_font = caSetLimits_label->font();
	caSetLimits_label_font.setPointSize(20);
	caSetLimits_label->setFont(caSetLimits_label_font);
	
	
	m_cDistanceLim_spinbox	 = new QSpinBox(this);
	m_cDistanceLim_spinbox->setRange (1, 25);
	m_cDistanceLim_spinbox->setSingleStep(1);
	QFont m_cDistanceLim_spinbox_font = m_cDistanceLim_spinbox->font();
	m_cDistanceLim_spinbox_font.setPointSize(20);
	m_cDistanceLim_spinbox->setFont(m_cDistanceLim_spinbox_font);	
	
	m_dDistanceLimit_meters = 1;
	connect(m_cDistanceLim_spinbox,SIGNAL(valueChanged(int)),this,SLOT(SetLimit(int)));


	QLabel *caDistance_label = new QLabel(tr("DISTANCE"),parent);
	
	QFont caDistanceLabel_font = caDistance_label->font();
	caDistanceLabel_font.setPointSize(20);
	caDistance_label->setFont(caDistanceLabel_font);	
	
	m_caDistance_label 	= new QLabel(tr("0 meters"),parent);
	
	QFont cDistanceLabel_font = m_caDistance_label->font();
	cDistanceLabel_font.setPointSize(36);
	m_caDistance_label->setFont(cDistanceLabel_font);
	
	QPalette cDistanceLabel_palette = m_caDistance_label->palette();
	cDistanceLabel_palette.setColor(m_caDistance_label->foregroundRole(), Qt::gray);
	m_caDistance_label->setPalette(cDistanceLabel_palette);		
	
	m_cSync_pb	= new QPushButton("SYNC", this);
	QFont cSync_pb_font = m_cSync_pb->font();
	cSync_pb_font.setPointSize(15);
	m_cSync_pb->setFont(cSync_pb_font);	
	
	connect(m_cSync_pb, SIGNAL(clicked()), this, SLOT(Sync()));
	
	QVBoxLayout *vbox = new QVBoxLayout(this);
	
	vbox->addWidget(caSetLimits_label,0,Qt::AlignCenter);
	vbox->addWidget(m_cDistanceLim_spinbox,0,Qt::AlignCenter);
	vbox->addWidget(caDistance_label,0,Qt::AlignCenter);
	vbox->addWidget(m_caDistance_label,0,Qt::AlignCenter);
	vbox->addWidget(m_cSync_pb,0,Qt::AlignCenter);
	
	setLayout(vbox);
	
	m_bConnected 		= 
	m_bConnected_Last 	= false;
	
}

void TabMAIN::Update(Controller *r)
{
	GGA *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cGGA))))
		return; 

	m_bConnected = g->iPositionFixIndicator == 1 || 
			g->iPositionFixIndicator == 2 ||
			g->iPositionFixIndicator == 6;
			
	if (m_bConnected)
	{
  
	      m_cSync_pb->setEnabled(true);
	      m_cDistanceLim_spinbox->setEnabled(true);
      
	      m_dCurrentObjectLatitude_deg	= GetLatitudeDegrees(g->caLatitude);	
	      m_dCurrentObjectLongitude_deg	= GetLongitudeDegrees(g->caLongitude);
	      
	      if (!m_bConnected_Last)
	      {
		  Sync();
	      } 
	      
 
	      double      dLatRad1    = ConvertToRadians(m_dCurrentObjectLatitude_deg);
	      double      dLonRad1    = ConvertToRadians(m_dCurrentObjectLongitude_deg);
 
	      double      dLatRad2    = ConvertToRadians(m_dFixedLatitude_deg);
	      double      dLonRad2    = ConvertToRadians(m_dFixedLongitude_deg);
 
 
	      double      dEarthRadiusKm = 6371.0;
	      double      dLat = (dLatRad2-dLatRad1);
	      double  dLon = (dLonRad2-dLonRad1);
 
	      double  dA = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(dLatRad1) * cos(dLatRad2);
	      double dC = 2 * atan2(sqrt(dA), sqrt(1-dA));
	      double dDistance = dEarthRadiusKm * dC * 1000.0;
	      
	      if (dDistance <= m_dDistanceLimit_meters)
	      {
			QPalette cDistanceLabel_palette = m_caDistance_label->palette();
			cDistanceLabel_palette.setColor(m_caDistance_label->foregroundRole(), Qt::green);
			m_caDistance_label->setPalette(cDistanceLabel_palette);	      
	      }
	      else
	      {
	   		QPalette cDistanceLabel_palette = m_caDistance_label->palette();
			cDistanceLabel_palette.setColor(m_caDistance_label->foregroundRole(), Qt::red);
			m_caDistance_label->setPalette(cDistanceLabel_palette);	     
	      }
	      
	      m_dDistance_string.sprintf("%i meters",(int)fabs(dDistance));
 

	}
	else
	{
		m_cSync_pb->setEnabled(false);
		m_cDistanceLim_spinbox->setEnabled(false);
		
		QPalette cDistanceLabel_palette = m_caDistance_label->palette();
		cDistanceLabel_palette.setColor(m_caDistance_label->foregroundRole(), Qt::gray);
		m_caDistance_label->setPalette(cDistanceLabel_palette);
		
		m_dDistance_string = "NO DATA AVAILABLE";

	}
	
	m_bConnected_Last = m_bConnected;
	
	m_caDistance_label->setText(m_dDistance_string);
}

int	TabMAIN::ConvertCharToDigit(char in)
{
	if (in >= 48 && in <=57)
		return (in - 48);
	else
		return 0;
}

double TabMAIN::GetLatitudeDegrees(char *in)
{
	if (!in || !isdigit(in[0]))
		return 0.0;
		
	double dMinutes =	ConvertCharToDigit(in[2]) * 10 + 
				ConvertCharToDigit(in[3]) + 
				double(ConvertCharToDigit(in[5])) / 10.0 + 
				double(ConvertCharToDigit(in[6])) / 100.0 + 
				double(ConvertCharToDigit(in[7])) / 1000.0 + 
				double(ConvertCharToDigit(in[8])) / 10000.0;
		
	double dDegrees =	ConvertCharToDigit(in[0]) * 10 + 
				ConvertCharToDigit(in[1]) + dMinutes / 60.0;
				
	return dDegrees;	 	
}

double TabMAIN::GetLongitudeDegrees(char *in)
{
	if (!in || !isdigit(in[0]))
		return 0.0;
		
	double dMinutes =	ConvertCharToDigit(in[3]) * 10 + 
				ConvertCharToDigit(in[4]) + 
				double(ConvertCharToDigit(in[6])) / 10.0 + 
				double(ConvertCharToDigit(in[7])) / 100.0 + 
				double(ConvertCharToDigit(in[8])) / 1000.0 + 
				double(ConvertCharToDigit(in[9])) / 10000.0;	
		
	double dDegrees =	ConvertCharToDigit(in[0]) * 100 + 
				ConvertCharToDigit(in[1]) * 10 + 
				ConvertCharToDigit(in[2]) + dMinutes / 60.0;
				
	return dDegrees;		
}

double      TabMAIN::ConvertToRadians(double dDeg)
{
      double dRad = dDeg * 3.14159265359 / 180.0;
 
      return dRad;
}

void TabMAIN::Sync()
{
	m_dFixedLatitude_deg	= m_dCurrentObjectLatitude_deg;
	m_dFixedLongitude_deg	= m_dCurrentObjectLongitude_deg;	
}

void TabMAIN::SetLimit(int iValue)
{
	m_dDistanceLimit_meters = iValue;
}
