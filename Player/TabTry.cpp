#include "StdAfx.h"
#include "TabTry.h"

CTabTryUI::CTabTryUI(CPaintManagerUI &paintmanager)
	: m_Manager(paintmanager)
{
	InitUI();
}

BOOL CTabTryUI::InitUI()
{
	CContainerUI *  pCtrl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create(_T("MusicTry.xml"), (UINT)0, NULL, &m_Manager));
	} 
	else
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create((UINT)0, &m_Manager));
	}
	if (pCtrl != NULL)
	{
		this->Add(pCtrl);
		return TRUE;
	}
	return FALSE;
}

BOOL CTabTryUI::AddListNode()
{
	m_pList = static_cast<CListUI*>(m_Manager.FindSubControlByName(this,_T("try_music_list")));
	CListContainerElementUI* pCtrl = NULL;
	if( !m_dlgItemBuilder1.GetMarkup()->IsValid() ) 
	{
		pCtrl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder1.Create(_T("list_item_music.xml"), (UINT)0, NULL, &m_Manager));
	} 
	else
	{
		pCtrl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder1.Create((UINT)0, &m_Manager));
	}
	if (pCtrl != NULL)
	{
		m_pList->Add(pCtrl);
		return TRUE;
	}
	return FALSE;
}