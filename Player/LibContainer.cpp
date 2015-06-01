#include "StdAfx.h"
#include "LibContainer.h"



CLibContainer::CLibContainer(CPaintManagerUI &paint_manager)
	: m_paint_manager(paint_manager)
{
	CListContainerElementUI* pControl = NULL;
	if( !m_dlgItemBuilder.GetMarkup()->IsValid() ) 
	{
		pControl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder.Create(_T("MusicLib.xml"), (UINT)0, this, &m_paint_manager));
	} 
	else
	{
		pControl = static_cast<CListContainerElementUI*>(m_dlgItemBuilder.Create(this,&m_paint_manager));
	}
	this->Add(pControl);
}

CLibContainer::~CLibContainer()
{

}

CControlUI* CLibContainer::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass,_T("TryListUI"))==0)
		//return new 	
	return NULL;
}
