#include "StdAfx.h"
#include "LibListListUI.h"

CLibListListUI::CLibListListUI()
{
	SetItemSize(CSize(130,200));
}

CLibListListUI::~CLibListListUI()
{

}

bool CLibListListUI::AddListNode(LPCTSTR lpPic,LPCTSTR lpName,LPCTSTR lpSinger,double dCount)
{
	CVerticalLayoutUI* pControl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create(_T("item_lib_list.xml"), (UINT)0, NULL, m_pManager));
	} 
	else
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create((UINT)0,m_pManager));
	}
	if (pControl != NULL)
	{
		TCHAR  szChar[128]= {0};
		CLabelUI* pic = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("btn_enter")));
		CLabelUI* name = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("list_name")));
		CLabelUI* singer = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("creator_name")));
		CLabelUI* count = static_cast<CLabelUI*>(m_pManager->FindSubControlByName(pControl,_T("listener_count")));
		swprintf(szChar,_T("%4.1f%s"),dCount,_T("ÍòÈËÌý"));
		pic->SetBkImage(lpPic);
		name->SetText(lpName);
		singer->SetText(lpSinger);
		count->SetText(szChar);

		CTileLayoutUI::Add(pControl);

		return TRUE;
	}
	return FALSE;
}