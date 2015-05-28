#include "stdafx.h"
#include "ColorListUI.h"
#include "PlayerWnd.h"
#include "ChangeBgWnd.h"


#define Caption_Btn_Bottom_Pos 37
const TCHAR* const kAdjustColorSliderRControlName = _T("AdjustColorSliderR");
const TCHAR* const kAdjustColorSliderGControlName = _T("AdjustColorSliderG");
const TCHAR* const kAdjustColorSliderBControlName = _T("AdjustColorSliderB");

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

CControlUI* CChangeBackgroudWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass,_T("")) == 0)
	{
		return NULL;
	}
	return NULL;
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
	m_pTab		 = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("color_tabs")));
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
		if (msg.pSender == m_PaintManager.FindControl(_T("bnt_bgimage")))
		{
			m_pTab->SelectItem(0);
		}
		else if (msg.pSender == m_PaintManager.FindControl(_T("btn_color")))
		{
			m_pTab->SelectItem(1);
		}
		else if (_tcsstr(msg.pSender->GetName(), _T("colour_")) != 0)
		{
			CSliderUI* AdjustColorSliderR = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderRControlName));
			CSliderUI* AdjustColorSliderG = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderGControlName));
			CSliderUI* AdjustColorSliderB = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderBControlName));
			if ((AdjustColorSliderR != NULL) && (AdjustColorSliderG != NULL) && (AdjustColorSliderB != NULL))
			{
				DWORD dwColor = msg.pSender->GetBkColor();
				AdjustColorSliderR->SetValue(static_cast<BYTE>(GetRValue(dwColor)));
				AdjustColorSliderG->SetValue(static_cast<BYTE>(GetGValue(dwColor)));
				AdjustColorSliderB->SetValue(static_cast<BYTE>(GetBValue(dwColor)));

				static_cast<CPlayerWnd*>(m_pParent)->SetBkColor(dwColor);
			}
		}
	}
	else if (msg.sType == _T("valuechanged"))
	{
		CSliderUI* AdjustColorSliderR = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderRControlName));
		CSliderUI* AdjustColorSliderG = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderGControlName));
		CSliderUI* AdjustColorSliderB = static_cast<CSliderUI*>(m_PaintManager.FindControl(kAdjustColorSliderBControlName));
		if ((AdjustColorSliderR != NULL) && (AdjustColorSliderG != NULL) && (AdjustColorSliderB != NULL))
		{
			BYTE red = AdjustColorSliderR->GetValue();
			BYTE green = AdjustColorSliderG->GetValue();
			BYTE blue = AdjustColorSliderB->GetValue();
			COLORREF crColor = RGB(red, green, blue);
			TCHAR szBuf[MAX_PATH] = {0};
#if defined(UNDER_CE)
			_stprintf(szBuf, _T("FF%02X%02X%02X"), GetRValue(crColor), GetGValue(crColor), GetBValue(crColor));
#else
			_stprintf_s(szBuf, MAX_PATH - 1, _T("FF%02X%02X%02X"), GetRValue(crColor), GetGValue(crColor), GetBValue(crColor));
#endif
			LPTSTR pstr = NULL;
			DWORD dwColor = _tcstoul(szBuf, &pstr, 16);
			m_pParent->SetBkColor(dwColor);

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
