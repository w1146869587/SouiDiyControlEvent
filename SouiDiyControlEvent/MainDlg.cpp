// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
#include "TestControl.h"
	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;

	// 绑定自定义消息
	SOUI::STestControl* pTestControl = 
		FindChildByName2<SOUI::STestControl>(L"test_control");
	assert(pTestControl != NULL);
	pTestControl->GetEventSet()->subscribeEvent(EVT_TEST_CONTROL,
		Subscriber(&CMainDlg::OnTestControl, this));
	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

// 响应 TestControl 的事件信息
bool CMainDlg::OnTestControl(SOUI::EventArgs* pEvt)
{
	SOUI::EventTestControl* pTestControlEvent =
		SOUI::sobj_cast<SOUI::EventTestControl>(pEvt);
	assert(pTestControlEvent != NULL);
	INT nIndex = 0;
	SOUI::SStringW strIndex;
	strIndex.Format(L"我们点击了第 %d 个按钮", pTestControlEvent->nIndex);
	SOUI::SMessageBox(NULL, strIndex, L"TestControl 被点击", MB_OK);
	return true;
}

