#include "StdAfx.h"
#include "LocalContainer.h"



CLocalContainer::CLocalContainer(CPaintManagerUI& paint_manager)
	: m_paint_manager(paint_manager)
{
	CVerticalLayoutUI* pControl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create(_T("MusicLocal.xml"), (UINT)0, this, &m_paint_manager));
	} 
	else
	{
		pControl = static_cast<CVerticalLayoutUI*>(m_dlgItemBuilder.Create(this,&m_paint_manager));
	}
	this->Add(pControl);
}

CLocalContainer::~CLocalContainer()
{
	
}

CControlUI* CLocalContainer::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}