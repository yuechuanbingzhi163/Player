#ifndef _TAB_TRY_H
#define _TAB_TRY_H


class CTabTryContainerUI : public CContainerUI
{
public:
	CTabTryContainerUI();
	BOOL	AddListNode();
private:
	CDialogBuilder  m_dlgItemBuilder;
	CDialogBuilder  m_builderItem;
	CListUI*		m_pList;
};

#endif