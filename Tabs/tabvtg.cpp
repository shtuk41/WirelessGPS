#include "tabs.h"


TabVTG::TabVTG(QWidget *parent) : QWidget(parent)
{
    QLabel *caMessageID_label 		= new QLabel(tr("Message ID:"),parent);
    QLabel *dCourseOverGround1_label 	= new QLabel(tr("Course Over Ground 1:"),parent);
    QLabel *cReference1_label 		= new QLabel(tr("Reference 1:"),parent);
    QLabel *dCourseOverGround2_label 	= new QLabel(tr("Course Over Ground 2:"),parent);
    QLabel *cReference2_label 		= new QLabel(tr("Reference 2:"),parent);
    QLabel *dSpeedOverGround1_label 	= new QLabel(tr("Speed Over Ground 1:"),parent);
    QLabel *cUnits1_label 		= new QLabel(tr("Units 1:"),parent);
    QLabel *dSpeedOverGround2_label 	= new QLabel(tr("Speed Over Ground 2:"),parent);
    QLabel *cUnits2_label 		= new QLabel(tr("Units 2:"),parent);
    QLabel *cMode_label 		= new QLabel(tr("Mode:"),parent);
    QLabel *caChecksum_label 		= new QLabel(tr("Checksum:"),parent);

    m_caMessageID_label			= new QLabel(tr("uninit"),parent); 	
    m_dCourseOverGround1_label		= new QLabel(tr("uninit"),parent); 
    m_cReference1_label			= new QLabel(tr("uninit"),parent); 		
    m_dCourseOverGround2_label		= new QLabel(tr("uninit"),parent); 
    m_cReference2_label			= new QLabel(tr("uninit"),parent); 	
    m_dSpeedOverGround1_label		= new QLabel(tr("uninit"),parent); 	
    m_cUnits1_label			= new QLabel(tr("uninit"),parent); 		
    m_dSpeedOverGround2_label		= new QLabel(tr("uninit"),parent); 	
    m_cUnits2_label			= new QLabel(tr("uninit"),parent); 		
    m_cMode_label			= new QLabel(tr("uninit"),parent); 		
    m_caChecksum_label			= new QLabel(tr("uninit"),parent); 
    
    QGridLayout	*mainLayout = new QGridLayout();	
    
    mainLayout->addWidget(caMessageID_label		,0,0);
    mainLayout->addWidget(dCourseOverGround1_label	,1,0);
    mainLayout->addWidget(cReference1_label		,2,0);
    mainLayout->addWidget(dCourseOverGround2_label	,3,0);
    mainLayout->addWidget(cReference2_label		,4,0);
    mainLayout->addWidget(dSpeedOverGround1_label	,5,0);
    mainLayout->addWidget(cUnits1_label			,6,0);
    mainLayout->addWidget(dSpeedOverGround2_label	,7,0);
    mainLayout->addWidget(cUnits2_label			,8,0);
    mainLayout->addWidget(cMode_label			,9,0);
    mainLayout->addWidget(caChecksum_label		,10,0);

   mainLayout->addWidget(m_caMessageID_label		,0,1);
    mainLayout->addWidget(m_dCourseOverGround1_label	,1,1);
    mainLayout->addWidget(m_cReference1_label		,2,1);
    mainLayout->addWidget(m_dCourseOverGround2_label	,3,1);
    mainLayout->addWidget(m_cReference2_label		,4,1);
    mainLayout->addWidget(m_dSpeedOverGround1_label	,5,1);
    mainLayout->addWidget(m_cUnits1_label		,6,1);
    mainLayout->addWidget(m_dSpeedOverGround2_label	,7,1);
    mainLayout->addWidget(m_cUnits2_label		,8,1);
    mainLayout->addWidget(m_cMode_label			,9,1);
    mainLayout->addWidget(m_caChecksum_label		,10,1);
        
    setLayout(mainLayout);
}

void TabVTG::Update(Controller *r)
{
	VTG *g;

	if (!(r && r->GetIO() && (g = &(r->GetIO()->cVTG))))
		return;

    m_caMessageID_string = ConvertMessageID(g->caMessageID); 	
    m_dCourseOverGround1_string.sprintf("%f",g->dCourseOverGround1); 
    m_cReference1_string.sprintf("%c",g->cReference1); 		
    m_dCourseOverGround2_string.sprintf("%f",g->dCourseOverGround2); 
    m_cReference2_string.sprintf("%c",g->cReference2); 	
    m_dSpeedOverGround1_string.sprintf("%f",g->dSpeedOverGround1); 	
    m_cUnits1_string = ConvertUnits(g->cUnits1); 		
    m_dSpeedOverGround2_string.sprintf("%f",g->dSpeedOverGround2); 	
    m_cUnits2_string = ConvertUnits(g->cUnits2); 		
    m_cMode_string = ConvertMode(g->cMode); 		
    m_caChecksum_string.sprintf("%.2s",g->caChecksum); 

    m_caMessageID_label->setText(m_caMessageID_string); 	
    m_dCourseOverGround1_label->setText(m_dCourseOverGround1_string); 
    m_cReference1_label->setText(m_cReference1_string); 		
    m_dCourseOverGround2_label->setText(m_dCourseOverGround2_string); 
    m_cReference2_label->setText(m_cReference2_string); 	
    m_dSpeedOverGround1_label->setText(m_dSpeedOverGround1_string); 	
    m_cUnits1_label->setText(m_cUnits1_string); 		
    m_dSpeedOverGround2_label->setText(m_dSpeedOverGround2_string); 	
    m_cUnits2_label->setText(m_cUnits2_string); 		
    m_cMode_label->setText(m_cMode_string); 		
    m_caChecksum_label->setText(m_caChecksum_string); 
}
