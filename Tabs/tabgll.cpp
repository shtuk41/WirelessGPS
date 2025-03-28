#include "tabs.h"


TabGLL::TabGLL(QWidget *parent) : QWidget(parent)
{
  
	QLabel *caMessageID_label 	= new QLabel(tr("Message ID:"),parent);
	QLabel *caLatitude_label 	= new QLabel(tr("Latitude:"),parent);
	QLabel *cNSIndicator_label 	= new QLabel(tr("NS Indicator:"),parent);
	QLabel *caLongitude_label 	= new QLabel(tr("Longitude:"),parent);
	QLabel *cEWIndicator_label 	= new QLabel(tr("EW Indicator:"),parent);
	QLabel *caUtcTime_label 	= new QLabel(tr("UTC Time:"),parent);
	QLabel *cStatus_label 		= new QLabel(tr("Status:"),parent);
	QLabel *cMode_label 		= new QLabel(tr("Mode:"),parent);
	QLabel *caChecksum_label 	= new QLabel(tr("Checksum:"),parent);

	m_caMessageID_label	= new QLabel(tr("uninit"),parent);
	m_caLatitude_label	= new QLabel(tr("uninit"),parent);
	m_cNSIndicator_label	= new QLabel(tr("uninit"),parent);
	m_caLongitude_label	= new QLabel(tr("uninit"),parent);
	m_cEWIndicator_label	= new QLabel(tr("uninit"),parent);
	m_caUtcTime_label	= new QLabel(tr("uninit"),parent);
	m_cStatus_label		= new QLabel(tr("uninit"),parent);
	m_cMode_label		= new QLabel(tr("uninit"),parent);
	m_caChecksum_label	= new QLabel(tr("uninit"),parent);
  
	QGridLayout	*mainLayout = new QGridLayout;

	mainLayout->addWidget(caMessageID_label,	0,0);
	mainLayout->addWidget(m_caMessageID_label,	0,1);
	mainLayout->addWidget(caLatitude_label,		1,0);
	mainLayout->addWidget(m_caLatitude_label,	1,1);
	mainLayout->addWidget(cNSIndicator_label,	2,0);
	mainLayout->addWidget(m_cNSIndicator_label,	2,1);
	mainLayout->addWidget(caLongitude_label,	3,0);
	mainLayout->addWidget(m_caLongitude_label,	3,1);
	mainLayout->addWidget(cEWIndicator_label,	4,0);
	mainLayout->addWidget(m_cEWIndicator_label,	4,1);
	mainLayout->addWidget(caUtcTime_label,		5,0);
	mainLayout->addWidget(m_caUtcTime_label,	5,1);
	mainLayout->addWidget(cStatus_label,		6,0);
	mainLayout->addWidget(m_cStatus_label,		6,1);
	mainLayout->addWidget(cMode_label,		7,0);
	mainLayout->addWidget(m_cMode_label,		7,1);
	mainLayout->addWidget(caChecksum_label,		8,0);
	mainLayout->addWidget(m_caChecksum_label,	8,1);

	setLayout(mainLayout);
}

void TabGLL::Update(Controller *r)
{
	GLL *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cGLL))))
		return;

	m_caMessageID_string = ConvertMessageID(g->caMessageID);
	m_caLatitude_string = ConvertLatitude(g->caLatitude);
	m_cNSIndicator_string = ConvertNSIndicator(g->cNSIndicator);
	m_caLongitude_string = ConvertLongitude(g->caLongitude);
	m_cEWIndicator_string = ConvertEWIndicator(g->cEWIndicator);
	m_caUtcTime_string = ConvertUTC(g->caUtcTime);
	m_cStatus_string = ConvertStatus(g->cStatus);
	m_cMode_string = ConvertMode(g->cMode);
	m_caChecksum_string.sprintf("%.2s",g->caChecksum);


	m_caMessageID_label->setText(m_caMessageID_string);
	m_caLatitude_label->setText(m_caLatitude_string);
	m_cNSIndicator_label->setText(m_cNSIndicator_string);
	m_caLongitude_label->setText(m_caLongitude_string);
	m_cEWIndicator_label->setText(m_cEWIndicator_string);
	m_caUtcTime_label->setText(m_caUtcTime_string);
	m_cStatus_label->setText(m_cStatus_string);
	m_cMode_label->setText(m_cMode_string);
	m_caChecksum_label->setText(m_caChecksum_string);

}
