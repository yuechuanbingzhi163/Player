#include "StdAfx.h"
#include "TryListUI.h"



static bool  OnButtonPlayEvent(void* event)
{
	 if( ((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN ) {
        CControlUI* pButton = ((TEventUI*)event)->pSender;
        if( pButton != NULL ) {
			::PostMessage(CMain::get_instance()->GetPlayerHWnd(),WM_PLAY_MUSIC,pButton->GetTag(),0);
        }
    }
    return true;
}

static bool OnButtonDownEvent(void* event)
{
	 if( ((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN ) {
        CControlUI* pButton = ((TEventUI*)event)->pSender;
        if( pButton != NULL ) {
			::PostMessage(CMain::get_instance()->GetPlayerHWnd(),WM_DOWN_MUSIC,pButton->GetTag(),0);
        }
    }
    return true;
}

CTryListUI::CTryListUI()
	: delay_deltaY_(0)
	, delay_number_(0)
	, delay_left_(0)
{
}

CTryListUI::~CTryListUI()
{
}

bool CTryListUI::SelectItem(int index, bool bTakeFocus)
{
	if (index == m_iCurSel)
	{
		return true;
	}

	// We should first unselect the currently selected item
	if( m_iCurSel >= 0 ) {
        CControlUI* pControl = GetItemAt(m_iCurSel);
        if( pControl != NULL) {  
			CListContainerElementUI* pFriendListItem = static_cast<CListContainerElementUI*>(pControl);
			if ((pFriendListItem != NULL) )
			{
				CContainerUI* pOperatorPannel = static_cast<CContainerUI*>(m_pManager->FindSubControlByName(pFriendListItem, _T("Operator")));
				if (pOperatorPannel != NULL)
				{
					pOperatorPannel->SetVisible(false);
				}
			}
        }
    }

	if (!CListUI::SelectItem(index))
		return false;

	CControlUI* pControl = GetItemAt(m_iCurSel);
	if( pControl != NULL) {
		CListContainerElementUI* pFriendListItem = static_cast<CListContainerElementUI*>(pControl);
		if ((pFriendListItem != NULL) )
		{
			CControlUI* pOperatorPannel = static_cast<CControlUI*>(m_pManager->FindSubControlByName(pFriendListItem, _T("Operator")));
			if (pOperatorPannel != NULL)
			{
				pOperatorPannel->SetVisible(true);
			}
		}
	}
	return true;
}

BOOL CTryListUI::AddListNode(int musicId,LPCTSTR lpName,LPCTSTR lpSinger, LPCTSTR lpAlbtm, LPCTSTR lpTimer)
{
	CListContainerElementUI* pControl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pControl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder.Create(_T("list_item_try.xml"), (UINT)0, NULL, m_pManager));
	} 
	else
	{
		pControl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder.Create((UINT)0,m_pManager));
	}
	if (pControl != NULL)
	{

		CLabelUI* labName = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("music_name")));
		CLabelUI* labSinger = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("music_singer")));
		CLabelUI* labAlbum = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("music_album")));
		CLabelUI* labTimer = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("music_timer")));

		labName->SetText(lpName);
		labSinger->SetText(lpSinger);
		labAlbum->SetText(lpAlbtm);
		labTimer->SetText(lpTimer);


		CButtonUI* btnPlay = static_cast<CButtonUI*>(m_pManager->FindSubControlByName(pControl,_T("btn_play")));
		if (btnPlay != NULL)
		{
			btnPlay->SetTag(UINT_PTR(musicId));
			btnPlay->OnEvent += MakeDelegate(&OnButtonPlayEvent);
		}
		CButtonUI* btnDown = static_cast<CButtonUI*>(m_pManager->FindSubControlByName(pControl,_T("btn_down")));
		if (btnDown != NULL)
		{
			btnDown->SetTag(UINT_PTR(musicId));
			btnDown->OnEvent += MakeDelegate(&OnButtonDownEvent);
		}

		CListUI::Add(pControl);

		return TRUE;
	}
	return FALSE;
}


void CTryListUI::DoEvent(TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND)
	{
		if (m_pParent != NULL)
			m_pParent->DoEvent(event);
		else
			CContainerUI::DoEvent(event);
		return;
	}

	if (event.Type == UIEVENT_TIMER && event.wParam == SCROLL_TIMERID)
	{
		if (delay_left_ > 0)
		{
			--delay_left_;
			SIZE sz = GetScrollPos();
			LONG lDeltaY =  (LONG)(CalculateDelay((double)delay_left_ / delay_number_) * delay_deltaY_);
			if ((lDeltaY > 0 && sz.cy != 0)  || (lDeltaY < 0 && sz.cy != GetScrollRange().cy ))
			{
				sz.cy -= lDeltaY;
				SetScrollPos(sz);
				return;
			}
		}
		delay_deltaY_ = 0;
		delay_number_ = 0;
		delay_left_ = 0;
		m_pManager->KillTimer(this, SCROLL_TIMERID);
		return;
	}
	if (event.Type == UIEVENT_SCROLLWHEEL)
	{
		LONG lDeltaY = 0;
		if (delay_number_ > 0)
			lDeltaY =  (LONG)(CalculateDelay((double)delay_left_ / delay_number_) * delay_deltaY_);
		switch (LOWORD(event.wParam))
		{
		case SB_LINEUP:
			if (delay_deltaY_ >= 0)
				delay_deltaY_ = lDeltaY + 8;
			else
				delay_deltaY_ = lDeltaY + 12;
			break;
		case SB_LINEDOWN:
			if (delay_deltaY_ <= 0)
				delay_deltaY_ = lDeltaY - 8;
			else
				delay_deltaY_ = lDeltaY - 12;
			break;
		}
		if
			(delay_deltaY_ > 100) delay_deltaY_ = 100;
		else if
			(delay_deltaY_ < -100) delay_deltaY_ = -100;

		delay_number_ = (DWORD)sqrt((double)abs(delay_deltaY_)) * 5;
		delay_left_ = delay_number_;
		m_pManager->SetTimer(this, SCROLL_TIMERID, 50U);
		return;
	}

	CListUI::DoEvent(event);
}