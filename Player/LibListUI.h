#ifndef _LIB_LISTUI_H
#define _LIB_LISTUI_H


class CLibListUI : public CTileLayoutUI
{
public:
	CLibListUI();
	~CLibListUI();
	bool AddListNode(LPCTSTR lpPic,LPCTSTR lpName,LPCTSTR lpSinger);

private:
	CDialogBuilder  m_dlgItemBuilder;
};
#endif