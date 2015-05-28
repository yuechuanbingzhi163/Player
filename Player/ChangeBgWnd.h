#ifndef _CHANAGE_BAKCGROUD_H
#define _CHANAGE_BAKCGROUD_H

class CPlayerWnd;
class CChangeBackgroudWnd : public WindowImplBase
{
public:
	CChangeBackgroudWnd();
	CChangeBackgroudWnd(CPlayerWnd* pWnd){ m_pParent = pWnd;}
	~CChangeBackgroudWnd();

	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
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
	CTabLayoutUI *m_pTab;
	CPlayerWnd    *m_pParent;
};

#endif 