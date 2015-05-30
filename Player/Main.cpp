// Player.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PlayerWnd.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;

	CPlayerWnd* pFrame = new CPlayerWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	if (pFrame != NULL)
	{
		CMessagePorxy::get_instance()->SetPlayerHWnd(pFrame->GetHWND());
	}
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return 0;
}
