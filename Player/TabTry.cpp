#include "StdAfx.h"
#include "TryListUI.h"
#include "TabTry.h"


CTabTryContainerUI::CTabTryContainerUI()
{
	CContainerUI *  pCtrl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create(_T("MusicTry.xml"), (UINT)0, this,m_pManager));
	} 
	else
	{
		pCtrl = static_cast<CContainerUI*>(m_dlgItemBuilder.Create(this, m_pManager));
	}
	if (pCtrl != NULL)
	{
		this->Add(pCtrl);
	}
}

CControlUI* CTabTryContainerUI::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass,_T("TryListUI")) == 0)
	{
		return new CTryListUI();
	}
	return NULL;
}