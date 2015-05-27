#include "stdafx.h"
#include "ChangeBgWnd.h"


#define Caption_Btn_Bottom_Pos 37

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

void CChangeBackgroudWnd::Init(RECT rect)
{
	m_rectParent = rect;
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
	m_pOptSwitch = static_cast<COptionUI*>(m_PaintManager.FindControl(_T("btn_switch")));
	m_pSlider    = static_cast<CSliderUI*>(m_PaintManager.FindControl(_T("Slider")));
	if (m_pSlider ) 
		m_pSlider->OnNotify += MakeDelegate(this,&CChangeBackgroudWnd::OnSliderTransparent);
}

void CChangeBackgroudWnd::MoveWindow()
{
	SIZE size = m_PaintManager.GetInitSize();
	::MoveWindow(m_hWnd, m_rectParent.right - size.cx - 120, m_rectParent.top + Caption_Btn_Bottom_Pos, size.cx , size.cy, FALSE);
}

void CChangeBackgroudWnd::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender == m_pOptSwitch)
		{
			if ( m_pOptSwitch->IsSelected())
			{
				m_pSlider->SetVisible(false);
			}
			else
			{
				m_pSlider->SetVisible(true);
			}
		}
	}
}

bool CChangeBackgroudWnd::OnSliderTransparent(void* param)
{
	 TNotifyUI* pMsg = (TNotifyUI*)param;
	 if( pMsg->sType == _T("valuechanged") ) {
			m_PaintManager.SetTransparent((static_cast<CSliderUI*>(pMsg->pSender))->GetValue());
        }
        return true;
}
