#include<afxwin.h>
#include"Drawing.h"

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMyWindow : public CFrameWnd
{
public:
	CMyWindow();
	afx_msg void OnLButtonDown(UINT Flags,CPoint pos);
	afx_msg void OnRButtonDown(UINT Flags,CPoint pos);
	afx_msg void OnMButtonDown(UINT Flags,CPoint pos);
	DECLARE_MESSAGE_MAP();
private:
	graphics::Drawing objects;
};
BEGIN_MESSAGE_MAP(CMyWindow,CFrameWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
END_MESSAGE_MAP();
BOOL CMyApp::InitInstance()
{
	m_pMainWnd=new CMyWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

CMyApp app;

CMyWindow::CMyWindow()
{
	Create(NULL,_T("Drawing"),WS_OVERLAPPEDWINDOW,CRect(0,0,400,400));
	graphics::Circle *circle=new graphics::Circle(100,100,50);
	objects.AddShape(circle);
	graphics::Rectangle *rect=new graphics::Rectangle(300,300,100,100);
	objects.AddShape(rect);
}

void CMyWindow::OnLButtonDown(UINT Flags,CPoint pos)
{
	CClientDC *pDC=new CClientDC(this);
	objects.Draw(pDC);
	delete pDC;
}

void CMyWindow::OnRButtonDown(UINT Flags,CPoint pos)
{
	objects.Clear();
	std::ifstream ifs;
	ifs.open("drawing.save",std::ios::binary);
	objects.Load(ifs);
	ifs.close();
}

void CMyWindow::OnMButtonDown(UINT Flags,CPoint pos)
{
	std::ofstream ofs;
	ofs.open("drawing.save",std::ios::binary);
	objects.Save(ofs);
	ofs.close();
}