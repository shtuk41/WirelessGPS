#include "tabs.h"


TabGSA::TabGSA(QWidget *parent) : QWidget(parent)
{
  	QLabel *caMessageID_label 		= new QLabel(tr("Message ID:"),parent);
  	QLabel *cMode1_label 			= new QLabel(tr("Mode 1:"),parent);
  	QLabel *cMode2_label 			= new QLabel(tr("Mode 2:"),parent);
  	QLabel *caIDofSatelliteUsed_label[12] 	= {new QLabel(tr("ID Of Satellite Used 1:"),parent),
						new QLabel(tr("ID Of Satellite Used 2:"),parent),
						new QLabel(tr("ID Of Satellite Used 3:"),parent),
						new QLabel(tr("ID Of Satellite Used 4:"),parent),
						new QLabel(tr("ID Of Satellite Used 5:"),parent),
						new QLabel(tr("ID Of Satellite Used 6:"),parent),
						new QLabel(tr("ID Of Satellite Used 7:"),parent),
						new QLabel(tr("ID Of Satellite Used 8:"),parent),
						new QLabel(tr("ID Of Satellite Used 9:"),parent),
						new QLabel(tr("ID Of Satellite Used 10:"),parent),
						new QLabel(tr("ID Of Satellite Used 11:"),parent),
						new QLabel(tr("ID Of Satellite Used 12:"),parent)};
  	QLabel *dPDOP_label 			= new QLabel(tr("PDOP:"),parent);
  	QLabel *dHDOP_label 			= new QLabel(tr("HDOP:"),parent);
  	QLabel *dVDOP_label 			= new QLabel(tr("VDOP:"),parent);
  	QLabel *caChecksum_label 		= new QLabel(tr("Checksum:"),parent);

  	m_caMessageID_label 			= new QLabel(tr("uninit"),parent);
  	m_cMode1_label 				= new QLabel(tr("uninit"),parent);
  	m_cMode2_label 				= new QLabel(tr("uninit"),parent);
  	m_caIDofSatelliteUsed_label[0]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[1]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[2]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[3]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[4]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[5]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[6]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[7]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[8]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[9]		=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[10] 	=	new QLabel(tr("uninit"),parent);
	m_caIDofSatelliteUsed_label[11] 	=	new QLabel(tr("uninit"),parent);
  	m_dPDOP_label 				= new QLabel(tr("uninit"),parent);
  	m_dHDOP_label 				= new QLabel(tr("uninit"),parent);
  	m_dVDOP_label 				= new QLabel(tr("uninit"),parent);
  	m_caChecksum_label 			= new QLabel(tr("uninit"),parent);
	
  	QGridLayout	*mainLayout = new QGridLayout();

  	mainLayout->addWidget(caMessageID_label,		0,	0);
	mainLayout->addWidget(m_caMessageID_label,		0,	1);
  	mainLayout->addWidget(cMode1_label,			1,	0);
	mainLayout->addWidget(m_cMode1_label,			1,	1);
  	mainLayout->addWidget(cMode2_label,			2,	0);
	mainLayout->addWidget(m_cMode2_label,			2,	1);
  	mainLayout->addWidget(caIDofSatelliteUsed_label[0],	3,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[0],	3,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[1],	4,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[1],	4,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[2],	5,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[2],	5,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[3],	6,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[3],	6,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[4],	7,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[4],	7,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[5],	8,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[5],	8,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[6],	9,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[6],	9,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[7],	10,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[7],	10,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[8],	11,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[8],	11,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[9],	12,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[9],	12,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[10],	13,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[10],	13,	1);
	mainLayout->addWidget(caIDofSatelliteUsed_label[11],	14,	0);
	mainLayout->addWidget(m_caIDofSatelliteUsed_label[11],	14,	1);
  	mainLayout->addWidget(dPDOP_label,			15,	0);
	mainLayout->addWidget(m_dPDOP_label,			15,	1);
  	mainLayout->addWidget(dHDOP_label,			16,	0);
	mainLayout->addWidget(m_dHDOP_label,			16,	1);
  	mainLayout->addWidget(dVDOP_label,			17,	0);
	mainLayout->addWidget(m_dVDOP_label,			17,	1);
  	mainLayout->addWidget(caChecksum_label,			18,	0);
	mainLayout->addWidget(m_caChecksum_label,		18,	1);
  
 	setLayout(mainLayout);
}

void TabGSA::Update(Controller *r)
{
	GSA *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cGSA))))
		return; 

/*	char			caMessageID[5];
	char			cMode1;
	char			cMode2;
	char			caIDofSatelliteUsed[12][2];
	double			dPDOP;
	double			dHDOP;
	double			dVDOP;
	char			caChecksum[2];*/

	  m_caMessageID_string = ConvertMessageID(g->caMessageID);
	  m_cMode1_string = ConvertMode1(g->cMode1);
	  m_cMode2_string = ConvertMode2(g->cMode2);
	  m_caIDofSatelliteUsed_string[0] = ConvertSatelliteID(g->caIDofSatelliteUsed[0]);
	  m_caIDofSatelliteUsed_string[1] = ConvertSatelliteID(g->caIDofSatelliteUsed[1]);
	  m_caIDofSatelliteUsed_string[2] = ConvertSatelliteID(g->caIDofSatelliteUsed[2]);
	  m_caIDofSatelliteUsed_string[3] = ConvertSatelliteID(g->caIDofSatelliteUsed[3]);
	  m_caIDofSatelliteUsed_string[4] = ConvertSatelliteID(g->caIDofSatelliteUsed[4]);
	  m_caIDofSatelliteUsed_string[5] = ConvertSatelliteID(g->caIDofSatelliteUsed[5]);
	  m_caIDofSatelliteUsed_string[6] = ConvertSatelliteID(g->caIDofSatelliteUsed[6]);
	  m_caIDofSatelliteUsed_string[7] = ConvertSatelliteID(g->caIDofSatelliteUsed[7]);
	  m_caIDofSatelliteUsed_string[8] = ConvertSatelliteID(g->caIDofSatelliteUsed[8]);
	  m_caIDofSatelliteUsed_string[9] = ConvertSatelliteID(g->caIDofSatelliteUsed[9]);
	  m_caIDofSatelliteUsed_string[10] = ConvertSatelliteID(g->caIDofSatelliteUsed[10]);
	  m_caIDofSatelliteUsed_string[11] = ConvertSatelliteID(g->caIDofSatelliteUsed[11]);
	  m_dPDOP_string = ConvertPDOP(g->dPDOP);
	  m_dHDOP_string = ConvertHDOP(g->dHDOP);
	  m_dVDOP_string = ConvertVDOP(g->dVDOP);
	  m_caChecksum_string.sprintf("%.2s",g->caChecksum);


  	m_caMessageID_label->setText(m_caMessageID_string);
  	m_cMode1_label->setText(m_cMode1_string);
  	m_cMode2_label->setText(m_cMode2_string);
  	m_caIDofSatelliteUsed_label[0]->setText(m_caIDofSatelliteUsed_string[0]);
	m_caIDofSatelliteUsed_label[1]->setText(m_caIDofSatelliteUsed_string[1]);
	m_caIDofSatelliteUsed_label[2]->setText(m_caIDofSatelliteUsed_string[2]);
	m_caIDofSatelliteUsed_label[3]->setText(m_caIDofSatelliteUsed_string[3]);
	m_caIDofSatelliteUsed_label[4]->setText(m_caIDofSatelliteUsed_string[4]);
	m_caIDofSatelliteUsed_label[5]->setText(m_caIDofSatelliteUsed_string[5]);
	m_caIDofSatelliteUsed_label[6]->setText(m_caIDofSatelliteUsed_string[6]);
	m_caIDofSatelliteUsed_label[7]->setText(m_caIDofSatelliteUsed_string[7]);
	m_caIDofSatelliteUsed_label[8]->setText(m_caIDofSatelliteUsed_string[8]);
	m_caIDofSatelliteUsed_label[9]->setText(m_caIDofSatelliteUsed_string[9]);
	m_caIDofSatelliteUsed_label[10]->setText(m_caIDofSatelliteUsed_string[10]);
	m_caIDofSatelliteUsed_label[11]->setText(m_caIDofSatelliteUsed_string[11]);
  	m_dPDOP_label->setText(m_dPDOP_string);
  	m_dHDOP_label->setText(m_dHDOP_string);
  	m_dVDOP_label->setText(m_dVDOP_string);
  	m_caChecksum_label->setText(m_caChecksum_string);

}
