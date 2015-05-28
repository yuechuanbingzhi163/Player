#ifndef _TAB_TRY_H
#define _TAB_TRY_H


class CTabTryUI : public CContainerUI
{
public:
	CTabTryUI(CPaintManagerUI &paintmanager);
	BOOL	InitUI();
	BOOL	AddListNode();
private:
	CDialogBuilder  m_dlgItemBuilder;
	CDialogBuilder  m_dlgItemBuilder1;
	CListUI*		m_pList;
	CPaintManagerUI &m_Manager;
};

#endif