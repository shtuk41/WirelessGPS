#include "tabs.h"


TabGSV::TabGSV(QWidget *parent) : QWidget(parent)
{
    QLabel *caMessageID_label 			= new QLabel(tr("Message ID:"),parent);
    QLabel *iTotalNumberOfMessages_label 	= new QLabel(tr("Total Number of Messages:"),parent);
    QLabel *iMessageNumber_label 		= new QLabel(tr("Message Number:"),parent);
    QLabel *iSatellitesInView_label 		= new QLabel(tr("Satellites in View:"),parent);
    
    QLabel *caSatelliteID1_label 		= new QLabel(tr("Satellites ID CH 1:"),parent);
    QLabel *iaElevation1_label 			= new QLabel(tr("Elevation CH 1:"),parent);
    QLabel *iaAzimuth1_label 			= new QLabel(tr("Azimuth CH 1:"),parent);
    QLabel *iaSNR1_label 			= new QLabel(tr("SNR CH 1:"),parent);
    
    QLabel *caSatelliteID2_label 		= new QLabel(tr("Satellites ID CH 2:"),parent);
    QLabel *iaElevation2_label 			= new QLabel(tr("Elevation CH 2:"),parent);
    QLabel *iaAzimuth2_label 			= new QLabel(tr("Azimuth CH 2:"),parent);
    QLabel *iaSNR2_label 			= new QLabel(tr("SNR CH 2:"),parent); 
    
    QLabel *caSatelliteID3_label 		= new QLabel(tr("Satellites ID CH 3:"),parent);
    QLabel *iaElevation3_label 			= new QLabel(tr("Elevation CH 3:"),parent);
    QLabel *iaAzimuth3_label 			= new QLabel(tr("Azimuth CH 3:"),parent);
    QLabel *iaSNR3_label 			= new QLabel(tr("SNR CH 3:"),parent); 
    
    QLabel *caSatelliteID4_label 		= new QLabel(tr("Satellites ID CH 4:"),parent);
    QLabel *iaElevation4_label 			= new QLabel(tr("Elevation CH 4:"),parent);
    QLabel *iaAzimuth4_label 			= new QLabel(tr("Azimuth CH 4:"),parent);
    QLabel *iaSNR4_label 			= new QLabel(tr("SNR CH 4:"),parent);     
   
    QLabel *caChecksum_label 			= new QLabel(tr("Checksum:"),parent);

    m_caMessageID_label			= new QLabel(tr("uninit"),parent); 		
    m_iTotalNumberOfMessages_label	= new QLabel(tr("uninit"),parent);  	
    m_iMessageNumber_label		= new QLabel(tr("uninit"),parent); 	
    m_iSatellitesInView_label		= new QLabel(tr("uninit"),parent); 		 
    m_caSatelliteID1_label		= new QLabel(tr("uninit"),parent); 		
    m_iaElevation1_label		= new QLabel(tr("uninit"),parent); 		
    m_iaAzimuth1_label			= new QLabel(tr("uninit"),parent);			
    m_iaSNR1_label			= new QLabel(tr("uninit"),parent); 			
    m_caSatelliteID2_label		= new QLabel(tr("uninit"),parent); 		
    m_iaElevation2_label		= new QLabel(tr("uninit"),parent); 		
    m_iaAzimuth2_label			= new QLabel(tr("uninit"),parent);			
    m_iaSNR2_label			= new QLabel(tr("uninit"),parent); 			
    m_caSatelliteID3_label		= new QLabel(tr("uninit"),parent); 		
    m_iaElevation3_label		= new QLabel(tr("uninit"),parent); 		
    m_iaAzimuth3_label			= new QLabel(tr("uninit"),parent); 		
    m_iaSNR3_label			= new QLabel(tr("uninit"),parent); 		
    m_caSatelliteID4_label		= new QLabel(tr("uninit"),parent); 		
    m_iaElevation4_label		= new QLabel(tr("uninit"),parent); 			
    m_iaAzimuth4_label			= new QLabel(tr("uninit"),parent); 		
    m_iaSNR4_label			= new QLabel(tr("uninit"),parent); 			
    m_caChecksum_label			= new QLabel(tr("uninit"),parent); 
  

	QGridLayout	*mainLayout = new QGridLayout();

    mainLayout->addWidget(caMessageID_label,		0,0);
    mainLayout->addWidget(iTotalNumberOfMessages_label, 1,0);
    mainLayout->addWidget(iMessageNumber_label,		2,0);
    mainLayout->addWidget(iSatellitesInView_label,	3,0);
    mainLayout->addWidget(caSatelliteID1_label,		4,0);
    mainLayout->addWidget(iaElevation1_label,		5,0);
    mainLayout->addWidget(iaAzimuth1_label,		6,0);
    mainLayout->addWidget(iaSNR1_label,			7,0);
    mainLayout->addWidget(caSatelliteID2_label,		8,0);
    mainLayout->addWidget(iaElevation2_label,		9,0);
    mainLayout->addWidget(iaAzimuth2_label,		10,0);
    mainLayout->addWidget(iaSNR2_label,			11,0);
    mainLayout->addWidget(caSatelliteID3_label,		12,0);
    mainLayout->addWidget(iaElevation3_label,		13,0);
    mainLayout->addWidget(iaAzimuth3_label,		14,0);
    mainLayout->addWidget(iaSNR3_label,			15,0);
    mainLayout->addWidget(caSatelliteID4_label,		16,0);
    mainLayout->addWidget(iaElevation4_label,		17,0);
    mainLayout->addWidget(iaAzimuth4_label,		18,0);
    mainLayout->addWidget(iaSNR4_label,			19,0);
    mainLayout->addWidget(caChecksum_label,		20,0);

    mainLayout->addWidget(m_caMessageID_label,			0,1);
    mainLayout->addWidget(m_iTotalNumberOfMessages_label, 	1,1);
    mainLayout->addWidget(m_iMessageNumber_label,		2,1);
    mainLayout->addWidget(m_iSatellitesInView_label,		3,1);
    mainLayout->addWidget(m_caSatelliteID1_label,		4,1);
    mainLayout->addWidget(m_iaElevation1_label,			5,1);
    mainLayout->addWidget(m_iaAzimuth1_label,			6,1);
    mainLayout->addWidget(m_iaSNR1_label,			7,1);
    mainLayout->addWidget(m_caSatelliteID2_label,		8,1);
    mainLayout->addWidget(m_iaElevation2_label,			9,1);
    mainLayout->addWidget(m_iaAzimuth2_label,			10,1);
    mainLayout->addWidget(m_iaSNR2_label,			11,1);
    mainLayout->addWidget(m_caSatelliteID3_label,		12,1);
    mainLayout->addWidget(m_iaElevation3_label,			13,1);
    mainLayout->addWidget(m_iaAzimuth3_label,			14,1);
    mainLayout->addWidget(m_iaSNR3_label,			15,1);
    mainLayout->addWidget(m_caSatelliteID4_label,		16,1);
    mainLayout->addWidget(m_iaElevation4_label,			17,1);
    mainLayout->addWidget(m_iaAzimuth4_label,			18,1);
    mainLayout->addWidget(m_iaSNR4_label,			19,1);
    mainLayout->addWidget(m_caChecksum_label,			20,1);
	

 setLayout(mainLayout);	
}

void TabGSV::Update(Controller *r)
{
  
	GSV *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cGSV))))
		return;

    m_caMessageID_string = ConvertMessageID(g->caMessageID); 		
    m_iTotalNumberOfMessages_string.sprintf("%i",g->iTotalNumberOfMessages); 	
    m_iMessageNumber_string.sprintf("%i",g->iMessageNumber); 	
    m_iSatellitesInView_string.sprintf("%i",g->iSatellitesInView); 		 
    m_caSatelliteID1_string = ConvertSatelliteID(g->caSatelliteID[0]); 		
    m_iaElevation1_string.sprintf("%i",g->iaElevation[0]); 		
    m_iaAzimuth1_string.sprintf("%i",g->iaAzimuth[0]);			
    m_iaSNR1_string.sprintf("%i",g->iaSNR[0]); 			
    m_caSatelliteID2_string = ConvertSatelliteID(g->caSatelliteID[1]); 		
    m_iaElevation2_string.sprintf("%i",g->iaElevation[1]); 		
    m_iaAzimuth2_string.sprintf("%i",g->iaAzimuth[1]);			
    m_iaSNR2_string.sprintf("%i",g->iaSNR[1]); 			
    m_caSatelliteID3_string =  ConvertSatelliteID(g->caSatelliteID[2]); 		
    m_iaElevation3_string.sprintf("%i",g->iaElevation[2]); 		
    m_iaAzimuth3_string.sprintf("%i",g->iaAzimuth[2]); 		
    m_iaSNR3_string.sprintf("%i",g->iaSNR[2]); 		
    m_caSatelliteID4_string =  ConvertSatelliteID(g->caSatelliteID[3]); 		
    m_iaElevation4_string.sprintf("%i",g->iaElevation[3]); 			
    m_iaAzimuth4_string.sprintf("%i",g->iaAzimuth[3]); 		
    m_iaSNR4_string.sprintf("%i",g->iaSNR[3]); 			
    m_caChecksum_string.sprintf("%.2s",g->caChecksum); 


    m_caMessageID_label->setText(m_caMessageID_string); 		
    m_iTotalNumberOfMessages_label->setText(m_iTotalNumberOfMessages_string); 	
    m_iMessageNumber_label->setText(m_iMessageNumber_string); 	
    m_iSatellitesInView_label->setText(m_iSatellitesInView_string); 		 
    m_caSatelliteID1_label->setText(m_caSatelliteID1_string); 		
    m_iaElevation1_label->setText(m_iaElevation1_string); 		
    m_iaAzimuth1_label->setText(m_iaAzimuth1_string);			
    m_iaSNR1_label->setText(m_iaSNR1_string); 			
    m_caSatelliteID2_label->setText(m_caSatelliteID2_string); 		
    m_iaElevation2_label->setText(m_iaElevation2_string); 		
    m_iaAzimuth2_label->setText(m_iaAzimuth2_string);			
    m_iaSNR2_label->setText(m_iaSNR2_string); 			
    m_caSatelliteID3_label->setText(m_caSatelliteID3_string); 		
    m_iaElevation3_label->setText(m_iaElevation3_string); 		
    m_iaAzimuth3_label->setText(m_iaAzimuth3_string); 		
    m_iaSNR3_label->setText(m_iaSNR3_string); 		
    m_caSatelliteID4_label->setText(m_caSatelliteID4_string); 		
    m_iaElevation4_label->setText(m_iaElevation4_string); 			
    m_iaAzimuth4_label->setText(m_iaAzimuth4_string); 		
    m_iaSNR4_label->setText(m_iaSNR4_string); 			
    m_caChecksum_label->setText(m_caChecksum_string); 
}
