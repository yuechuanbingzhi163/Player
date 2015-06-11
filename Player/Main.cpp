// Player.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "PlayerWnd.h"
#include "FileSqlite.h"
#include "Main.h"



int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT Hr = ::CoInitialize(NULL);
	if( FAILED(Hr) ) return 0;

	TCHAR szPath[MAX_PATH] = {0};
	tstring strAppPath = GetAppPath();
	swprintf(szPath,MAX_PATH,_T("%s%s"),strAppPath.c_str(),_T("\\DB\\file.db"));


	if (!CFileSQLite::get_instance()->open(UnicodeToUtf8(szPath)))
			CFileSQLite::get_instance()->close();

	CMain::get_instance()->InitSock();

	CPlayerWnd* pFrame = new CPlayerWnd();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	if (pFrame != NULL)
	{
		CMain::get_instance()->SetPlayerHWnd(pFrame->GetHWND());
	}
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	CPaintManagerUI::MessageLoop();
	
	CMain::get_instance()->UninitSock();
	CFileSQLite::get_instance()->close();
	::CoUninitialize();
	return 0;
}


