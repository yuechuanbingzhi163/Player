#include "stdafx.h"
#include "MessageProxy.h"


CMessagePorxy::CMessagePorxy()
{
}

CMessagePorxy::~CMessagePorxy()
{
}

void CMessagePorxy::SetPlayerHWnd(HWND hWnd)
{
	m_hPlayerWnd = hWnd;
}

HWND CMessagePorxy::GetPlayerHWnd()
{
	return m_hPlayerWnd;
}