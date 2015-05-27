#ifndef _CHANAGE_BAKCGROUD_H
#define _CHANAGE_BAKCGROUD_H


class CChangeBackgroudWnd : public WindowImplBase
{
public:
	CChangeBackgroudWnd();
	~CChangeBackgroudWnd();

	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual LPCTSTR GetWindowClassName(void) const;
	void	OnFinalMessage(HWND hWnd);
	LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, bool& /*bHandled*/);
	LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

	void	Init(RECT rect);
	void	InitWindow();
	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	void	MoveWindow();
	void	Notify(TNotifyUI& msg);
	bool    OnSliderTransparent(void *param);
private:
	RECT	m_rectParent;
	COptionUI *m_pOptSwitch;
	CSliderUI *m_pSlider;
};

#endif 