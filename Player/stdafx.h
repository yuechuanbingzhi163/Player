// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "..\DuiLib\UIlib.h"
#include <string>
using namespace DuiLib;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include "message.h"
#include "c_singleton.h"
#include "MessageProxy.h"
#include "rw_lock.h"
#include "public.h"
#include "c_file.h"
#include "Utils.h"
using namespace zn;



//Lib
#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, "..\\Lib\\DuiLib_u.lib")
#   else
#       pragma comment(lib, "..\\Lib\\DuiLib.lib")
#   endif
#endif




#if defined(UNICODE) || defined(_UNICODE)
typedef std::wstring tstring;
#else
typedef	std::string tstring;
#endif