#include "StdAfx.h"
#include "PlayerWnd.h"


CPlayerWnd::CPlayerWnd()
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
{}

LRESULT CPlayerWnd::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}