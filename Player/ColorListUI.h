#ifndef _COLOR_LISTUI_H
#define _COLOR_LISTUI_H



class CColorListUI : public CTabLayoutUI
{
public:
	CColorListUI();
	~CColorListUI();
	
	void Init();
private:
	CDialogBuilder m_dlgBuilder;
};


#endif

