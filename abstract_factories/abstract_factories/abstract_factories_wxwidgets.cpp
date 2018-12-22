#include"wx/wx.h"
#include "EasyEnemyFactory.h"
#include "HardEnemyFactory.h"
#include "GenericEnemyFactories.h"
#include <vector>

//definitions for menu and window objects
#define ID_WINDOW	1000
#define IDM_EASY	1001
#define IDM_HARD	1002
//class for main application
class CMyApp : public wxApp
{
public:
	virtual bool OnInit();
};

//class for main window
class CMyWindow : public wxFrame
{
public:
	CMyWindow();
	~CMyWindow();
	void OnEasy(wxCommandEvent& event);
	void OnHard(wxCommandEvent& event);
	void OnRButtonDown(wxMouseEvent& event);
	void OnLButtonDown(wxMouseEvent& event);
	void OnMButtonDown(wxMouseEvent& event);
	DECLARE_EVENT_TABLE();
private:
	void ClearEnemies(void);
	void DrawEnemies(void);
	void PopulateEnemies(void);
	wxMenu *m_pPopupMenu;
	ConcreteEnemyFactory::AbstractEnemyFactory* m_pFactory;
	std::vector<Game::Enemy*> m_vEnemies;
	GenericEnemyFactory::AbstractEnemyFactory* m_pNewFactory;
	GenericEnemyFactory::EnemyFactory *m_pProtoFactory;
};

BEGIN_EVENT_TABLE(CMyWindow,wxFrame)
	EVT_MENU(IDM_EASY,CMyWindow::OnEasy)
	EVT_MENU(IDM_HARD,CMyWindow::OnHard)
	EVT_RIGHT_DOWN(CMyWindow::OnRButtonDown)
	EVT_LEFT_DOWN(CMyWindow::OnLButtonDown)
	EVT_MIDDLE_DOWN(CMyWindow::OnMButtonDown)
END_EVENT_TABLE();

bool CMyApp::OnInit()
{
	wxApp::OnInit();
	CMyWindow *frame=new CMyWindow();
	frame->Show(true);
	return true;
}

IMPLEMENT_APP(CMyApp);

CMyWindow::~CMyWindow()
{
	delete m_pPopupMenu;
	if(m_pFactory!=nullptr)
		delete m_pFactory;
	if(m_pNewFactory!=nullptr)
		delete m_pNewFactory;
	if(m_pProtoFactory!=nullptr)
		delete m_pProtoFactory;
}

CMyWindow::CMyWindow()
{
	Create(NULL,ID_WINDOW,"abstract factories",wxPoint(100,100),wxSize(400,400));
	m_pPopupMenu=new wxMenu("Level Dificulty");
	m_pPopupMenu->AppendCheckItem(IDM_EASY,"easy");
	m_pPopupMenu->AppendCheckItem(IDM_HARD,"hard");
	m_pFactory=nullptr;
	m_pNewFactory=nullptr;
	m_pProtoFactory=nullptr;
}

void CMyWindow::OnEasy(wxCommandEvent& event)
{
	m_pPopupMenu->Check(IDM_EASY,true);
	m_pPopupMenu->Check(IDM_HARD,false);
	ClearEnemies();
/*
	if(m_pFactory!=nullptr)
		delete m_pFactory;
	m_pFactory=new ConcreteEnemyFactory::EasyEnemyFactory;
*/
/*
	if(m_pNewFactory!=nullptr)
		delete m_pNewFactory;
	m_pNewFactory=new GenericEnemyFactory::EasyLevelEnemyFactory;
*/
	if(m_pProtoFactory!=nullptr)
		delete m_pProtoFactory;
	m_pProtoFactory=new GenericEnemyFactory::EnemyFactory;
	m_pProtoFactory->SetPrototype(new Game::EasySoldier(wxPoint(100,100),wxSize(50,50)));
	m_pProtoFactory->SetPrototype(new Game::EasyMonster(wxPoint(100,100),wxSize(50,50)));
}

void CMyWindow::OnHard(wxCommandEvent& event)
{
	m_pPopupMenu->Check(IDM_EASY,false);
	m_pPopupMenu->Check(IDM_HARD,true);
	ClearEnemies();
/*
	if(m_pFactory!=nullptr)
		delete m_pFactory;
	m_pFactory=new ConcreteEnemyFactory::HardEnemyFactory;
*/
/*
	if(m_pNewFactory!=nullptr)
		delete m_pNewFactory;
	m_pNewFactory=new GenericEnemyFactory::HardLevelEnemyFactory;
*/
	if(m_pProtoFactory!=nullptr)
		delete m_pProtoFactory;
	m_pProtoFactory=new GenericEnemyFactory::EnemyFactory;
	m_pProtoFactory->SetPrototype(new Game::HardSoldier(wxPoint(100,100),wxSize(50,50)));
	m_pProtoFactory->SetPrototype(new Game::HardMonster(wxPoint(100,100),wxSize(50,50)));
}

void CMyWindow::OnRButtonDown(wxMouseEvent& event)
{
	PopupMenu(m_pPopupMenu);
}

void CMyWindow::OnLButtonDown(wxMouseEvent& event)
{
	DrawEnemies();
}

void CMyWindow::OnMButtonDown(wxMouseEvent& event)
{
	ClearEnemies(); //for test purpose
	PopulateEnemies();
}

void CMyWindow::ClearEnemies(void)
{
	wxClientDC dc(this);
	wxPen pen(dc.GetPen());
	pen.SetColour(dc.GetBackground().GetColour());
	wxBrush brush(dc.GetBackground());
	
	std::vector<Game::Enemy*>::const_reverse_iterator it;
	for(it=m_vEnemies.rbegin();it!=m_vEnemies.rend();++it)
	{
		(*it)->SetPen(&pen);
		(*it)->SetBrush(&brush);
		(*it)->Draw(&dc);
		delete(*it);
	}
	m_vEnemies.clear();
}

void CMyWindow::DrawEnemies(void)
{
	wxClientDC dc(this);
	std::vector<Game::Enemy*>::const_iterator it;
	for(it=m_vEnemies.begin();it!=m_vEnemies.end();++it)
		(*it)->Draw(&dc);
}

void CMyWindow::PopulateEnemies(void)
{
	if(m_pFactory!=nullptr)
	{
		m_vEnemies.push_back(m_pFactory->MakeSoldier(wxPoint(100,100),wxSize(100,100)));
		m_vEnemies.push_back(m_pFactory->MakeMonster(wxPoint(200,200),wxSize(100,100)));
	}
	else if(m_pNewFactory!=nullptr)
	{
		Game::Enemy* enemy;
		enemy=(*m_pNewFactory).Create<Game::Soldier>();
		enemy->SetPosition(wxPoint(100,100));
		enemy->SetSize(wxSize(100,100));
		m_vEnemies.push_back(enemy);
		enemy=m_pNewFactory->Create<Game::Monster>();
		enemy->SetPosition(wxPoint(200,200));
		enemy->SetSize(wxSize(100,100));
		m_vEnemies.push_back(enemy);
	} else if(m_pProtoFactory!=nullptr)
	{
		Game::Enemy* enemy;
		enemy=(*m_pProtoFactory).Create<Game::Soldier>();
		enemy->SetPosition(wxPoint(100,100));
		enemy->SetSize(wxSize(100,100));
		m_vEnemies.push_back(enemy);
		enemy=m_pProtoFactory->Create<Game::Monster>();
		enemy->SetPosition(wxPoint(200,200));
		enemy->SetSize(wxSize(100,100));
		m_vEnemies.push_back(enemy);
	}
}