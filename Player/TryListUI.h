#ifndef _TRY_LISTUI_H
#define _TRY_LISTUI_H


class CTryListUI : public CListUI
{
public:
	CTryListUI();
	~CTryListUI();
	BOOL	AddListNode(int musicId,LPCTSTR lpName,LPCTSTR lpSinger, LPCTSTR lpAlbtm, LPCTSTR lpTimer);
	bool	SelectItem(int index,bool bTakeFocus = false);
private:
	CDialogBuilder  m_dlgItemBuilder;
};

#endif