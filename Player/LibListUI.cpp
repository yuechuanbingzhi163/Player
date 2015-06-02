#include "StdAfx.h"
#include "LibListUI.h"

CLibListUI::CLibListUI()
{
	SetItemSize(CSize(130,170));
}

CLibListUI::~CLibListUI()
{

}

bool CLibListUI::AddListNode(LPCTSTR lpPic,LPCTSTR lpName,LPCTSTR lpSinger)
{
	CVerticalLayoutUI* pControl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create(_T("list_item_lib.xml"), (UINT)0, NULL, m_pManager));
	} 
	else
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create((UINT)0,m_pManager));
	}
	if (pControl != NULL)
	{

		CButtonUI* pic = static_cast<CButtonUI*>(m_pManager->FindSubControlByName(pControl,_T("btn_enter")));
		CButtonUI* name = static_cast<CButtonUI*>(m_pManager->FindSubControlByName(pControl,_T("btn_album_name")));
		CButtonUI* singer = static_cast<CButtonUI*>(m_pManager->FindSubControlByName(pControl,_T("btn_ablum_singer")));

		pic->SetBkImage(lpPic);
		name->SetText(lpName);
		singer->SetText(lpSinger);

		CTileLayoutUI::Add(pControl);

		return TRUE;
	}
	return FALSE;
}