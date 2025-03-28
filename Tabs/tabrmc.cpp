#include "tabs.h"


TabRMC::TabRMC(QWidget *parent) : QWidget(parent)
{
     QLabel *caMessageID_label 		= new QLabel(tr("Message ID:"),parent); 
     QLabel *caUTCTime_label 		= new QLabel(tr("UTC Time:")); 
     QLabel *cStatus_label 		= new QLabel(tr("Status:")); 
     QLabel *caLatitude_label 		= new QLabel(tr("Latitude:")); 
     QLabel *cNSIndicator_label 	= new QLabel(tr("NS Indicator:")); 
     QLabel *caLongitude_label 		= new QLabel(tr("Longitude:")); 
     QLabel *cEWIndicator_label 	= new QLabel(tr("EW Indicator:")); 
     QLabel *dSpeedOverGround_label 	= new QLabel(tr("Speed Over Ground:")); 
     QLabel *dCourseOverGround_label 	= new QLabel(tr("Course Over Ground:")); 
     QLabel *caDate_label 		= new QLabel(tr("Date:")); 
     QLabel *iMagneticVariation_label 	= new QLabel(tr("Magnetic Variation:")); 
     QLabel *cVariationSense_label 	= new QLabel(tr("Variation Sense:")); 
     QLabel *cMode_label 		= new QLabel(tr("Mode:")); 
     QLabel *caChecksum_label 		= new QLabel(tr("Checksum:")); 

    m_caMessageID_label		= new QLabel(tr("uninit"),parent); 	
    m_caUTCTime_label		= new QLabel(tr("uninit"),parent); 		
    m_cStatus_label		= new QLabel(tr("uninit"),parent); 		
    m_caLatitude_label		= new QLabel(tr("uninit"),parent); 	
    m_cNSIndicator_label	= new QLabel(tr("uninit"),parent); 	 
    m_caLongitude_label		= new QLabel(tr("uninit"),parent); 	
    m_cEWIndicator_label	= new QLabel(tr("uninit"),parent);	 	
    m_dSpeedOverGround_label	= new QLabel(tr("uninit"),parent); 	 
    m_dCourseOverGround_label	= new QLabel(tr("uninit"),parent); 	
    m_caDate_label		= new QLabel(tr("uninit"),parent); 		
    m_iMagneticVariation_label	= new QLabel(tr("uninit"),parent);
    m_cVariationSense_label	= new QLabel(tr("uninit"),parent); 	
    m_cMode_label		= new QLabel(tr("uninit"),parent); 	 
    m_caChecksum_label		= new QLabel(tr("uninit"),parent); 
  

	
    QGridLayout	*mainLayout = new QGridLayout();	
  
    mainLayout->addWidget(caMessageID_label	 	,0,0);
    mainLayout->addWidget(caUTCTime_label 		,1,0);
    mainLayout->addWidget(cStatus_label			,2,0);
    mainLayout->addWidget(caLatitude_label		,3,0);
    mainLayout->addWidget(cNSIndicator_label		,4,0);
    mainLayout->addWidget(caLongitude_label		,5,0);
    mainLayout->addWidget(cEWIndicator_label		,6,0);
    mainLayout->addWidget(dSpeedOverGround_label	,7,0);
    mainLayout->addWidget(dCourseOverGround_label	,8,0);
    mainLayout->addWidget(caDate_label			,9,0);
    mainLayout->addWidget(iMagneticVariation_label	,10,0);
    mainLayout->addWidget(cVariationSense_label		,11,0);
    mainLayout->addWidget(cMode_label			,12,0);
    mainLayout->addWidget(caChecksum_label		,13,0);

    mainLayout->addWidget(m_caMessageID_label	 	,0,1);
    mainLayout->addWidget(m_caUTCTime_label 		,1,1);
    mainLayout->addWidget(m_cStatus_label		,2,1);
    mainLayout->addWidget(m_caLatitude_label		,3,1);
    mainLayout->addWidget(m_cNSIndicator_label		,4,1);
    mainLayout->addWidget(m_caLongitude_label		,5,1);
    mainLayout->addWidget(m_cEWIndicator_label		,6,1);
    mainLayout->addWidget(m_dSpeedOverGround_label	,7,1);
    mainLayout->addWidget(m_dCourseOverGround_label	,8,1);
    mainLayout->addWidget(m_caDate_label		,9,1);
    mainLayout->addWidget(m_iMagneticVariation_label	,10,1);
    mainLayout->addWidget(m_cVariationSense_label	,11,1);
    mainLayout->addWidget(m_cMode_label			,12,1);
    mainLayout->addWidget(m_caChecksum_label		,13,1);
  
 
  setLayout(mainLayout);	
}

void TabRMC::Update(Controller *r)
{
	RMC *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cRMC))))
		return;

    m_caMessageID_string = ConvertMessageID(g->caMessageID); 	
    m_caUTCTime_string = ConvertUTC(g->caUTCTime); 		
    m_cStatus_string = ConvertStatus(g->cStatus); 		
    m_caLatitude_string = ConvertLatitude(g->caLatitude); 	
    m_cNSIndicator_string = ConvertNSIndicator(g->cNSIndicator); 	 
    m_caLongitude_string = ConvertLongitude(g->caLongitude); 	
    m_cEWIndicator_string = ConvertEWIndicator(g->cEWIndicator); 	
    m_dSpeedOverGround_string.sprintf("%f",g->dSpeedOverGround); 	 
    m_dCourseOverGround_string.sprintf("%f",g->dCourseOverGround); 	
    m_caDate_string = ConvertDate(g->caDate); 		
    m_iMagneticVariation_string = ConvertMagneticVariation(g->iMagneticVariation);
    m_cVariationSense_string = ConvertVariationSence(g->cVariationSense); 	
    m_cMode_string = ConvertMode(g->cMode); 	 
    m_caChecksum_string.sprintf("%.2s",g->caChecksum); 

    m_caMessageID_label->setText(m_caMessageID_string); 	
    m_caUTCTime_label->setText(m_caUTCTime_string); 		
    m_cStatus_label->setText(m_cStatus_string); 		
    m_caLatitude_label->setText(m_caLatitude_string); 	
    m_cNSIndicator_label->setText(m_cNSIndicator_string); 	 
    m_caLongitude_label->setText(m_caLongitude_string); 	
    m_cEWIndicator_label->setText(m_cEWIndicator_string); 	
    m_dSpeedOverGround_label->setText(m_dSpeedOverGround_string); 	 
    m_dCourseOverGround_label->setText(m_dCourseOverGround_string); 	
    m_caDate_label->setText(m_caDate_string); 		
    m_iMagneticVariation_label->setText(m_iMagneticVariation_string);
    m_cVariationSense_label->setText(m_cVariationSense_string); 	
    m_cMode_label->setText(m_cMode_string); 	 
    m_caChecksum_label->setText(m_caChecksum_string); 
}
