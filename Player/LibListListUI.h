#ifndef _LIB_LIST_LISTUI_H
#define _LIB_LIST_LISTUI_H


class CLibListListUI : public CTileLayoutUI
{
public:
	CLibListListUI();
	~CLibListListUI();
	bool AddListNode(LPCTSTR lpPic,LPCTSTR lpName,LPCTSTR lpSinger,double dCount);

private:
	CDialogBuilder  m_dlgItemBuilder;
};
#endif