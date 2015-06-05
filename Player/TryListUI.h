#ifndef _TRY_LISTUI_H
#define _TRY_LISTUI_H


static double CalculateDelay(double state)
{
	return pow(state, 2);
}

class CTryListUI : public CListUI
{
	enum 
	{
		SCROLL_TIMERID = 11,
	};
public:
	CTryListUI();
	~CTryListUI();
	BOOL	AddListNode(int musicId,LPCTSTR lpName,LPCTSTR lpSinger, LPCTSTR lpAlbtm, LPCTSTR lpTimer);
	bool	SelectItem(int index,bool bTakeFocus = false);
	void	DoEvent(TEventUI& event);
private:
	CDialogBuilder  m_dlgItemBuilder;
	int		delay_deltaY_;
	int		delay_number_;
	int		delay_left_;
};

#endif