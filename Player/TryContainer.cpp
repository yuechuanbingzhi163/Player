#include "StdAfx.h"
#include "TryListUI.h"
#include "TryContainer.h"


CTryContainer::CTryContainer(CPaintManagerUI &paint_manager)
	: m_paint_manager(paint_manager)
{
	CVerticalLayoutUI* pControl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create(_T("MusicTry.xml"), (UINT)0, this, &m_paint_manager));
	} 
	else
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create(this,&m_paint_manager));
	}
	this->Add(pControl);
}

CTryContainer::~CTryContainer()
{

}

CControlUI* CTryContainer::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass,_T("TryListUI")) == 0)
		return new CTryListUI();
	return NULL;
}