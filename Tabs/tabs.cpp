
#include <iostream>
#include "tabs.h"

using namespace std;

Tabs::Tabs(Controller *pC, QWidget *parent) : QDialog(parent),pController(pC)
{
    m_pTabMAIN = new TabMAIN(this);
    m_pTabGGA = new TabGGA(this);
    m_pTabGGL = new TabGLL(this);
    m_pTabGSA = new TabGSA(this);
    m_bTabGSV = new TabGSV(this);
    m_bTabRMC = new TabRMC(this);
    m_bTabVTG = new TabVTG(this);
    
    tabWidget = new QTabWidget;
    
    tabWidget->addTab(m_pTabMAIN,tr("Distance"));    
    tabWidget->addTab(m_pTabGGA, tr("GGA"));
    tabWidget->addTab(m_pTabGGL, tr("GLL"));
    tabWidget->addTab(m_pTabGSA, tr("GSA"));
    tabWidget->addTab(m_bTabGSV, tr("GSV"));
    tabWidget->addTab(m_bTabRMC, tr("RMC"));
    tabWidget->addTab(m_bTabVTG, tr("VTG"));
    
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                      | QDialogButtonBox::Cancel);

      connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())); 
    
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
    
    setWindowTitle(tr("SEIS742.  LS20031 GPS Information"));

    startTimer(500);

}

void  Tabs::timerEvent(QTimerEvent *e)
{
	Q_UNUSED(e);
	
	if (tabWidget && pController)
	{
		pController->SetPage((CONTROLLER_PAGE)tabWidget->currentIndex());
		pController->Process();
	}

	Update(pController);
}

void Tabs::Update(Controller *r)
{
      m_pTabMAIN->Update(r);	
      m_pTabGGA->Update(r);
      m_pTabGGL->Update(r);
      m_pTabGSA->Update(r);
      m_bTabGSV->Update(r);
      m_bTabRMC->Update(r);
      m_bTabVTG->Update(r);
}
