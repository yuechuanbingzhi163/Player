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

	void	Init();
	void	InitWindow();
	LRESULT OnKillFocus(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
};

#endif 