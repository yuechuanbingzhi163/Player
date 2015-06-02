#ifndef _PLAYER_WND_H
#define _PLAYER_WND_H


class CChangeBackgroudWnd;
class CPlayerWnd : public WindowImplBase
{
public:
	CPlayerWnd();
	~CPlayerWnd();
	static HWND GetPlayerHWnd();
public:

	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void	Notify(TNotifyUI& msg);
	void	OnTimer(TNotifyUI& msg);
	void	SetBkColor(DWORD dwBackColor);


public:
	void	UpdateTryList();
	void	UpdateLibList();

private:
	CButtonUI *m_pBtnMin;
	CButtonUI *m_pBtnMax;
	CButtonUI *m_pBtnClose;
	CButtonUI *m_pBtnRestore;
	CRichEditUI *m_pSearchEdit;
	int			m_nIncWidth;
	int			m_nSearchWidth;
	int			TimerId;
	bool		m_bExpande;

	COptionUI* m_pBtnLib;
	COptionUI* m_pBtnRep;
	COptionUI* m_pBtnTry;
	COptionUI* m_pBtnLocal;
	COptionUI* m_pBtnDown;
	CChangeBackgroudWnd *m_pChangBgWnd;

	CTabLayoutUI* m_tabs;
	CTabLayoutUI* m_tabslib;

	int m_nScrollIndex;
};


#endif