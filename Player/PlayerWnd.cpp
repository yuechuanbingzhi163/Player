#include "StdAfx.h"
#include "PlayerWnd.h"


CPlayerWnd::CPlayerWnd()
	: m_nIncWidth(5)
	, m_nSearchWidth(200)
	, TimerId(10)
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
	if (_tcsicmp(pstrClass, _T("FriendList")) == 0)
	{
		//return new CFriendsUI(m_PaintManager);
	}
	else if (_tcsicmp(pstrClass, _T("GroupList")) == 0)
	{
		//return new CGroupsUI(m_PaintManager);
	}
	else if (_tcsicmp(pstrClass, _T("MicroBlog")) == 0)
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
	m_pBtnTry = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_try")));
	m_pBtnLocal = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_local")));
	m_pBtnDown = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_down")));


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
			{
				m_pChangBgWnd = new CChangeBackgroudWnd();
			}
			if (!::IsWindow(m_pChangBgWnd->GetHWND()))
			{
				m_pChangBgWnd->Create(m_hWnd,_T(""),WS_POPUP, WS_EX_TOOLWINDOW);
			}
			m_pChangBgWnd->CenterWindow();
			m_pChangBgWnd->ShowWindow(true);
		}
	}
	else if (_tcsicmp(msg.sType, _T("timer")) == 0)
	{
		return OnTimer(msg);
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