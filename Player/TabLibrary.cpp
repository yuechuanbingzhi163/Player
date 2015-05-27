#include "StdAfx.h"
#include "TabLibrary.h"


CTabLibraryUI::CTabLibraryUI()
{
	InitUI();
}

BOOL CTabLibraryUI::InitUI()
{
	CContainerUI *  pCtrl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create(_T("MusicLib.xml"), (UINT)0, NULL, m_pManager));
	} 
	else
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create((UINT)0, m_pManager));
	}
	if (pCtrl != NULL)
	{
		this->Add(pCtrl);
		return TRUE;
	}
	return FALSE;
}