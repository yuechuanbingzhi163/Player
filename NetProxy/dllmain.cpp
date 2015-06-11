// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void net_proxy_init()
{

}

void net_proxy_release()
{

}



//sock
void initsocket()
{
	c_winsock::init();
}

void uninitsocket()
{
	c_winsock::release();
}


i_file_server* file_server_init()
{
	c_file_server* pServer = new c_file_server();
	if (!pServer)
		return NULL;
	return pServer;
		
}

void file_server_release(i_file_server* pServer)
{
	if (pServer)
		delete pServer;
}
