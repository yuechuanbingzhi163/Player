#ifndef _MESSAGE_PROXY_H
#define _MESSAGE_PROXY_H


class CMessagePorxy : public c_singleton<CMessagePorxy>
{

public:
	CMessagePorxy();
	~CMessagePorxy();
	void SetPlayerHWnd(HWND hWnd);
	HWND GetPlayerHWnd();

private:
	HWND m_hPlayerWnd;
};


#endif