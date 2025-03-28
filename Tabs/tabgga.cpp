
#include "tabs.h"


TabGGA::TabGGA(QWidget *parent) : QWidget(parent)
{
   QLabel *caMessageID_label 		= 	new QLabel(tr("Message ID:"),parent);
   QLabel *caUTCTime_label 		= 	new QLabel(tr("UTC Time:"),parent);
   QLabel *caLatitude_label 		= 	new QLabel(tr("Latitude:"),parent);
   QLabel *cNSIndicator_label 		= 	new QLabel(tr("NS Indicator:"),parent);
   QLabel *caLongitude_label 		= 	new QLabel(tr("Longitude:"),parent);
   QLabel *cEWIndicator_label 		= 	new QLabel(tr("EW Indicator:"),parent);
   QLabel *iPositionFixIndicator_label 	= 	new QLabel(tr("Position Fix Indicator:"),parent);
   QLabel *caSatellitesUsed_label 	= 	new QLabel(tr("Satellites Used:"),parent);
   QLabel *dHDOP_label 			= 	new QLabel(tr("HDOP:"),parent);
   QLabel *dMSLAltitude_label 		= 	new QLabel(tr("MSL Altitude:"),parent);
   QLabel *cUnits1_label 		= 	new QLabel(tr("Units 1:"),parent);
   QLabel *dGeoidSeparation_label 	= 	new QLabel(tr("Geoid Separtion:"),parent);
   QLabel *cUnits2_label 		= 	new QLabel(tr("Units 2:"),parent);
   QLabel *iAgeofDiffCorr_label 	= 	new QLabel(tr("Age of Diff Corr:"),parent);
   QLabel *caDiffREfStationID_label 	= 	new QLabel(tr("Diff Ref Station ID:"),parent);
   QLabel *caChecksum_label 		= 	new QLabel(tr("Checksum:"),parent);
   
   m_caMessageID_label 			= 	new QLabel(m_caMessageID_string,parent);
   m_caUTCTime_label			= 	new QLabel(m_caUTCTime_string,parent);
   m_caLatitude_label			= 	new QLabel(m_caLatitude_string,parent);
   m_cNSIndicator_label			= 	new QLabel(m_cNSIndicator_string,parent);
   m_caLongitude_label			= 	new QLabel(m_caLongitude_string,parent);
   m_cEWIndicator_label			= 	new QLabel(m_cEWIndicator_string,parent);
   m_iPositionFixIndicator_label	= 	new QLabel(m_iPositionFixIndicator_string,parent);
   m_caSatellitesUsed_label		= 	new QLabel(m_caSatellitesUsed_string,parent);
   m_dHDOP_label			= 	new QLabel(m_dHDOP_string,parent);
   m_dMSLAltitude_label			= 	new QLabel(m_dMSLAltitude_string,parent);
   m_cUnits1_label			= 	new QLabel(m_cUnits1_string,parent);
   m_dGeoidSeparation_label		= 	new QLabel(m_dGeoidSeparation_string,parent);
   m_cUnits2_label			= 	new QLabel(m_cUnits2_string,parent);
   m_iAgeofDiffCorr_label		= 	new QLabel(m_iAgeofDiffCorr_string,parent);
   m_caDiffREfStationID_label		= 	new QLabel(m_caDiffREfStationID_string,parent);
   m_caChecksum_label			= 	new QLabel(m_caChecksum_string,parent);

   QGridLayout	*mainLayout = new QGridLayout();
   
   mainLayout->addWidget(caMessageID_label,			0,	0);
   mainLayout->addWidget(m_caMessageID_label, 			0, 	1);
   mainLayout->addWidget(caUTCTime_label,			1,	0);
   mainLayout->addWidget(m_caUTCTime_label, 			1, 	1);
   mainLayout->addWidget(caLatitude_label,			2,	0);
   mainLayout->addWidget(m_caLatitude_label, 			2, 	1);
   mainLayout->addWidget(cNSIndicator_label,			3,	0);
   mainLayout->addWidget(m_cNSIndicator_label, 			3, 	1);
   mainLayout->addWidget(caLongitude_label,			4,	0);
   mainLayout->addWidget(m_caLongitude_label, 			4, 	1);
   mainLayout->addWidget(cEWIndicator_label,			5,	0);
   mainLayout->addWidget(m_cEWIndicator_label, 			5, 	1);
   mainLayout->addWidget(iPositionFixIndicator_label,		6,	0);
   mainLayout->addWidget(m_iPositionFixIndicator_label, 	6, 	1);
   mainLayout->addWidget(caSatellitesUsed_label,		7,	0);
   mainLayout->addWidget(m_caSatellitesUsed_label, 		7, 	1);
   mainLayout->addWidget(dHDOP_label,				8,	0);
   mainLayout->addWidget(m_dHDOP_label, 			8, 	1);
   mainLayout->addWidget(dMSLAltitude_label,			9,	0);
   mainLayout->addWidget(m_dMSLAltitude_label, 			9, 	1);
   mainLayout->addWidget(cUnits1_label,				10,	0);
   mainLayout->addWidget(m_cUnits1_label, 	  		10, 	1);
   mainLayout->addWidget(dGeoidSeparation_label,		11,	0);
   mainLayout->addWidget(m_dGeoidSeparation_label, 		11, 	1);
   mainLayout->addWidget(cUnits2_label,				12,	0);
   mainLayout->addWidget(m_cUnits2_label, 			12, 	1);
   mainLayout->addWidget(iAgeofDiffCorr_label,			13,	0);
   mainLayout->addWidget(m_iAgeofDiffCorr_label, 		13, 	1);
   mainLayout->addWidget(caDiffREfStationID_label,		14,	0);
   mainLayout->addWidget(m_caDiffREfStationID_label, 		14, 	1);
   mainLayout->addWidget(caChecksum_label,			15,	0);
   mainLayout->addWidget(m_caChecksum_label, 			15, 	1);
   
   setLayout(mainLayout);
}

void TabGGA::Update(Controller *r)
{
	GGA *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cGGA))))
		return;

	m_caMessageID_string = ConvertMessageID(g->caMessageID);
	m_caUTCTime_string = ConvertUTC(g->caUtcTime);
   	m_caLatitude_string = ConvertLatitude(g->caLatitude);
   	m_cNSIndicator_string = ConvertNSIndicator(g->cNSIndicator);
   	m_caLongitude_string = ConvertLongitude(g->caLongitude);
   	m_cEWIndicator_string = ConvertEWIndicator(g->cEWIndicator);
   	m_iPositionFixIndicator_string = ConvertPositionFixIndicator(g->iPositionFixIndicator);
   	m_caSatellitesUsed_string = ConvertSatellitesUsed(g->caSatellitesUsed);
   	m_dHDOP_string = ConvertHDOP(g->dHDOP);
   	m_dMSLAltitude_string = ConvertMSLAltitude(g->dMSLAltitude);
   	m_cUnits1_string = ConvertUnits(g->cUnits1);
   	m_dGeoidSeparation_string = ConvertGeoidSeparation(g->dGeoidSeparation);
   	m_cUnits2_string = ConvertUnits(g->cUnits2);
   	m_iAgeofDiffCorr_string = ConvertAgeofDiffCorr(g->iAgeofDiffCorr);
   	m_caDiffREfStationID_string = ConvertDiffRefStationID(g->caDiffREfStationID);
   	m_caChecksum_string.sprintf("%.2s",g->caChecksum);

   m_caMessageID_label->setText(m_caMessageID_string);
   m_caUTCTime_label->setText(m_caUTCTime_string);
   m_caLatitude_label->setText(m_caLatitude_string);
   m_cNSIndicator_label->setText(m_cNSIndicator_string);
   m_caLongitude_label->setText(m_caLongitude_string);
   m_cEWIndicator_label->setText(m_cEWIndicator_string);
   m_iPositionFixIndicator_label->setText(m_iPositionFixIndicator_string);
   m_caSatellitesUsed_label->setText(m_caSatellitesUsed_string);
   m_dHDOP_label->setText(m_dHDOP_string);
   m_dMSLAltitude_label->setText(m_dMSLAltitude_string);
   m_cUnits1_label->setText(m_cUnits1_string);
   m_dGeoidSeparation_label->setText(m_dGeoidSeparation_string);
   m_cUnits2_label->setText(m_cUnits2_string);
   m_iAgeofDiffCorr_label->setText(m_iAgeofDiffCorr_string);
   m_caDiffREfStationID_label->setText(m_caDiffREfStationID_string);
   m_caChecksum_label->setText(m_caChecksum_string);

}


