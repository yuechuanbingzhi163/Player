#include "StdAfx.h"
#include "TryListUI.h"
#include "LibListUI.h"
#include "LibListListUI.h"
#include "ChangeBgWnd.h"
#include "LibContainer.h"
#include "TryContainer.h"
#include "PlayerWnd.h"

CPlayerWnd::CPlayerWnd()
	: m_nIncWidth(5)
	, m_nSearchWidth(200)
	, TimerId(10)
	, m_nScrollIndex(0)
{}

CPlayerWnd::~CPlayerWnd()
{
	PostQuitMessage(0);
}

LPCTSTR CPlayerWnd::GetWindowClassName() const
{
	return _T("CPlayerWnd");
}

CControlUI* CPlayerWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, _T("MusicTry")) == 0)
	{
		return new CTryContainer(m_PaintManager);
	}
	else if (_tcsicmp(pstrClass, _T("MusicLib")) == 0)
	{
		return new CLibContainer(m_PaintManager);
	}
	else if (_tcsicmp(pstrClass, _T("")) == 0)
	{
		//return new CMicroBlogUI(m_PaintManager);
	}

	return NULL;
}

void CPlayerWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

CDuiString CPlayerWnd::GetSkinFile()
{
	return _T("main_player.xml");
}

CDuiString CPlayerWnd::GetSkinFolder()
{
	return  _T("skin\\");
}

LRESULT CPlayerWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CPlayerWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if defined(WIN32) && !defined(UNDER_CE)
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(m_hWnd) != bZoomed)
	{
		if (!bZoomed)
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("")));
			if( pControl ) pControl->SetVisible(false);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("")));
			if( pControl ) pControl->SetVisible(true);
		}
		else 
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("")));
			if( pControl ) pControl->SetVisible(true);
			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("")));
			if( pControl ) pControl->SetVisible(false);
		}
	}
#else
	return __super::OnSysCommand(uMsg, wParam, lParam, bHandled);
#endif

	return 0;
}

LRESULT CPlayerWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	return FALSE;
}

void CPlayerWnd::InitWindow()
{
	m_pBtnMin = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_min")));
	m_pBtnMax = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_max")));
	m_pBtnClose = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_close")));
	m_pBtnRestore = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_restore")));
	m_pSearchEdit = static_cast<CRichEditUI*>(m_PaintManager.FindControl(_T("search_edit")));
	m_pBtnLib = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("music_lib")));
	m_pBtnRep = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("music_rep")));
	m_pBtnTry = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("music_try")));
	m_pBtnLocal = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("music_local")));
	m_pBtnDown = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("music_down")));

	m_tabs	=  static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabs")));
	m_tabslib = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabs_lib")));
	UpdateTryList();
	UpdateLibList();
	m_pChangBgWnd = NULL;
}

LRESULT CPlayerWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (uMsg == WM_NCLBUTTONDOWN)
	{
		RECT rect = m_pSearchEdit->GetPos();
		POINT point;
		point.x = GET_X_LPARAM(lParam); 
		point.y = GET_Y_LPARAM(lParam);
		ScreenToClient(m_hWnd,&point);
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom )
		{
			if (rect.right - rect.left == 390)
				return 0;
			m_pSearchEdit->SetFocus();
			bHandled = true;
			m_PaintManager.SetTimer(m_pSearchEdit,TimerId,1);
		}
		else
		{
			m_pSearchEdit->SetFixedWidth(200);
		}
		return 0;
	}
	else if(uMsg == WM_NCLBUTTONDBLCLK)
	{
		RECT rect = m_pSearchEdit->GetPos();
		POINT point;
		point.x = GET_X_LPARAM(lParam); 
		point.y = GET_Y_LPARAM(lParam);
		ScreenToClient(m_hWnd,&point);
		if (point.x > rect.left && point.x < rect.right && point.y > rect.top && point.y < rect.bottom )
		{
			bHandled = true;
		}
		return 0;
	}
	else if(uMsg == WM_PLAY_MUSIC)
	{

	}
	else if(uMsg == WM_DOWN_MUSIC)
	{

	}

	return 0;
}

void CPlayerWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pBtnMin)
		{
			SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
		}
		else if (msg.pSender == m_pBtnMax)
		{
			SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
			m_pBtnMax->SetVisible(false);
			m_pBtnRestore->SetVisible(true);
		}
		else if (msg.pSender == m_pBtnClose)
		{
			Close();
		}
		else if(msg.pSender == m_pBtnRestore)
		{
			SendMessage(WM_SYSCOMMAND,SC_RESTORE,0);
			m_pBtnMax->SetVisible(true);
			m_pBtnRestore->SetVisible(false);
		}
		else if(msg.pSender->GetName() == _T("btn_change_skin"))
		{
			if (m_pChangBgWnd == NULL)
				m_pChangBgWnd = new CChangeBackgroudWnd(this);

			if (!::IsWindow(m_pChangBgWnd->GetHWND()))
				m_pChangBgWnd->Create(m_hWnd,_T(""),WS_POPUP, WS_EX_TOOLWINDOW);
			
			RECT rect;
			::GetWindowRect(this->GetHWND(),&rect);
			m_pChangBgWnd->Init(rect);
			m_pChangBgWnd->MoveWindow();
		
			m_pChangBgWnd->ShowWindow(true);
		}
		else if (msg.pSender->GetName() == _T("btn_pre_pic"))
		{
			CHorizontalLayoutUI* pControl = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("pic_hor")));
			TCHAR szPath[256] = {0};
			m_nScrollIndex = (m_nScrollIndex - 1) % 4;
			if (m_nScrollIndex < 0)
				m_nScrollIndex = 3;
			swprintf(szPath,256,_T("picture\\scroll%d.jpg"),m_nScrollIndex);
			pControl->SetBkImage(szPath);
		}
		else if (msg.pSender->GetName() == _T("btn_next_pic"))
		{
			CHorizontalLayoutUI* pControl = static_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("pic_hor")));
			TCHAR szPath[256] = {0};
			m_nScrollIndex = (m_nScrollIndex + 1) % 4;
			swprintf(szPath,256,_T("picture\\scroll%d.jpg"),m_nScrollIndex);
			pControl->SetBkImage(szPath);
		}
	}
	else if (_tcsicmp(msg.sType, _T("timer")) == 0)
	{
		return OnTimer(msg);
	}
	else if (_tcsicmp(msg.sType, _T("selectchanged")) == 0)
	{
		//music
		if (msg.pSender == m_PaintManager.FindControl(_T("music_lib")))
		{
			m_tabs->SelectItem(0);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("music_rep")))
		{
			m_tabs->SelectItem(1);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("music_try")))
		{
			m_tabs->SelectItem(2);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("music_local")))
		{
			m_tabs->SelectItem(3);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("music_down")))
		{
			m_tabs->SelectItem(4);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("")))
		{
			m_tabs->SelectItem(5);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("")))
		{
			m_tabs->SelectItem(6);
		}

		//lib
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_recommend")))
		{
			m_tabslib->SelectItem(0);
		}
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_rank")))
		{
			m_tabslib->SelectItem(1);
		}
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_list")))
		{
			m_tabslib->SelectItem(2);
			CVerticalLayoutUI *pVertical = static_cast<CVerticalLayoutUI*>(m_tabslib->GetItemAt(2));
			pVertical->SetScrollInc(0,30);
		}
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_radio")))
		{
			m_tabslib->SelectItem(3);
		}
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_class")))
		{
			m_tabslib->SelectItem(4);
		}
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_mv")))
		{
			m_tabslib->SelectItem(5);
		}
		else if(msg.pSender == m_PaintManager.FindControl(_T("opt_find")))
		{
			m_tabslib->SelectItem(6);
		}
	}
	else if (_tcsicmp(msg.sType, _T("itemactivate")) == 0)
	{
		int i = 0;
	}
}

void CPlayerWnd::OnTimer(TNotifyUI& msg)
{
	if ( TimerId == msg.wParam)
	{
		m_nSearchWidth += m_nIncWidth;
		m_pSearchEdit->SetFixedWidth(m_nSearchWidth);
		if (m_nSearchWidth == 390)
		{
			m_nSearchWidth = 200;
			m_PaintManager.KillTimer(m_pSearchEdit);
		}
	}
}

void CPlayerWnd::SetBkColor(DWORD dwBackColor)
{
	CControlUI* pBk = m_PaintManager.FindControl(_T("bk"));
	pBk->SetBkColor(dwBackColor);
}

void CPlayerWnd::UpdateTryList()
{
	CTryListUI* pList = static_cast<CTryListUI*>(m_PaintManager.FindControl(_T("try_music_list")));
	for (int i = 0; i < 20; i++)
	{
		pList->AddListNode(i,_T("默上花开"),_T("古力娜扎"),_T("默"),_T("03:23"));
	}
	
}

void CPlayerWnd::UpdateLibList()
{
	CLibListUI* pList = static_cast<CLibListUI*>(m_PaintManager.FindControl(_T("lib_list_rec")));
	for (int i = 0; i < 20; i++)
	{
		pList->AddListNode(_T("picture\\scroll1.jpg"),_T("古力娜扎"),_T("默上花开"));
	}

	CLibListListUI* pList1 = static_cast<CLibListListUI*>(m_PaintManager.FindControl(_T("lib_list_list")));
	for (int i = 0; i < 30; i++)
	{
		pList1->AddListNode(_T("picture\\scroll1.jpg"),_T("古力娜扎"),_T("默上花开"),255.6);
	}
}
