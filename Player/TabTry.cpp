#include "StdAfx.h"
#include "TabTry.h"

CTabTryContainerUI::CTabTryContainerUI()
{
	CContainerUI *  pCtrl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create(_T("MusicTry.xml"), (UINT)0, NULL,m_pManager));
	} 
	else
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create((UINT)0, m_pManager));
	}
	if (pCtrl != NULL)
	{
		this->Add(pCtrl);
	}
}

BOOL CTabTryContainerUI::AddListNode()
{
	m_pList = static_cast<CListUI*>(m_pManager->FindSubControlByName(this,_T("try_music_list")));
	CListContainerElementUI* pCtrl = NULL;
	if( !m_builderItem.GetMarkup()->IsValid() ) 
	{
		pCtrl = static_cast<CListContainerElementUI*>(m_builderItem.Create(_T("list_item_music.xml"), (UINT)0, NULL, m_pManager));
	} 
	else
	{
		pCtrl = static_cast<CListContainerElementUI*>(m_builderItem.Create((UINT)0,m_pManager));
	}
	if (pCtrl != NULL)
	{
		m_pList->Add(pCtrl);
		return TRUE;
	}
	return FALSE;
}