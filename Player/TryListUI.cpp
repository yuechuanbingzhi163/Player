#include "StdAfx.h"
#include "TryListUI.h"



static bool  OnButtonPlayEvent(void* event)
{
	 if( ((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN ) {
        CControlUI* pButton = ((TEventUI*)event)->pSender;
        if( pButton != NULL ) {
			::PostMessage(CMessagePorxy::get_instance()->GetPlayerHWnd(),WM_PLAY_MUSIC,pButton->GetTag(),0);
        }
    }
    return true;
}

static bool OnButtonDownEvent(void* event)
{
	 if( ((TEventUI*)event)->Type == UIEVENT_BUTTONDOWN ) {
        CControlUI* pButton = ((TEventUI*)event)->pSender;
        if( pButton != NULL ) {
			::PostMessage(CMessagePorxy::get_instance()->GetPlayerHWnd(),WM_DOWN_MUSIC,pButton->GetTag(),0);
        }
    }
    return true;
}

CTryListUI::CTryListUI()
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
		pControl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder.Create(_T("list_item_music.xml"), (UINT)0, NULL, m_pManager));
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