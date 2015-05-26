#include "stdafx.h"
#include "ChangeBgWnd.h"

CChangeBackgroudWnd::CChangeBackgroudWnd()
{

}
CChangeBackgroudWnd::~CChangeBackgroudWnd()
{
}

CDuiString CChangeBackgroudWnd::GetSkinFolder()
{
	return  _T("skin\\");
}
CDuiString CChangeBackgroudWnd::GetSkinFile()
{
	return _T("ChangeBg.xml");
}
LPCTSTR CChangeBackgroudWnd::GetWindowClassName(void) const
{
	return _T("CChangeBackgroud");
}

void CChangeBackgroudWnd::OnFinalMessage(HWND hWnd)
{
	WindowImplBase::OnFinalMessage(hWnd);
	delete this;
}

void CChangeBackgroudWnd::Init()
{
	
}

LRESULT CChangeBackgroudWnd::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/)
{
	if (uMsg == WM_KEYDOWN)
	{
		switch (wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return ResponseDefaultKeyEvent(wParam);
		default:
			break;
		}
	}
	return FALSE;
}

LRESULT CChangeBackgroudWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		return FALSE;
	}
	else if (wParam == VK_ESCAPE)
	{
		ShowWindow(false);
		return TRUE;
	}

	return FALSE;
}



LRESULT CChangeBackgroudWnd::OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	ShowWindow(false);
	return 0;
}

void CChangeBackgroudWnd::InitWindow()
{
	SIZE size = m_PaintManager.GetInitSize();
	//MoveWindow(m_hWnd, parent_window_rect_.right - size.cx, parent_window_rect_.top, size.cx, size.cy, FALSE);
}