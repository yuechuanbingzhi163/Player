#ifndef _public_h_
#define _public_h_

#ifdef _MSC_VER
#include <wtypes.h>
#include <tchar.h>
#include <sys/stat.h>
#include <atlbase.h>
#include <direct.h>
#else
#include <sys/vfs.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <dirent.h>
#include <iconv.h>
#include <arpa/inet.h>
#include <uuid/uuid.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <vector>
#include <string>
#include "df_macro.h"
#include "MyTypes.h"
#define MAX_MSG_LENGTH	1024 * 32


using namespace std;


namespace zn
{
	static string itostr(int i)
	{
		char str[20];
		sprintf_s(str, "%u", i);
		return str;
	}

	static string itostr64(LONGLONG i)
	{
		char str[20];
		sprintf_s(str, "%I64d", i);
		return str;
	}

	static string replace_str(const char *src, const char *sMatchStr, const char *sReplaceStr)
	{

		int  StringLen;

		char cresult[MAX_MSG_LENGTH];
		char caNewString[MAX_MSG_LENGTH];

		strcpy_s(cresult, src);

		const char *FindPos = strstr(cresult, sMatchStr);

		if( (!FindPos) || (!sMatchStr) )
			return cresult;


		while( FindPos )

		{

			memset(caNewString, 0, sizeof(caNewString));

			StringLen = FindPos - cresult;

			strncpy_s(caNewString, cresult, StringLen);

			strcat_s(caNewString, sReplaceStr);

			strcat_s(caNewString, FindPos + strlen(sMatchStr));

			strcpy_s(cresult, caNewString);

			FindPos = strstr(cresult, sMatchStr);

		}


		return cresult;
	}


	static string str_ltrim(const string& str) 
	{ 
		return str.substr(str.find_first_not_of(" \n\r\t")); 
	} 

	static string str_rtrim(const string& str) 
	{ 
		return str.substr(0,str.find_last_not_of(" \n\r\t")+1); 
	} 

	static string str_trim(const string& str) 
	{ 
		return str_ltrim(str_rtrim(str)); 
	}

	static void nstrcpy(char* dest, const char* sour, int size)
	{
		if (sour != NULL && size > 0)
		{
			strncpy(dest,sour,size);
			dest[size - 1] = 0;
		}
	}

	//转大写
	static string str_toupper(const char* c)
	{
		char* r = strdup(c);
		for (int i = 0; r[i] != 0; i++)
		{
			r[i] = toupper(r[i]);
		}
		string result = r;
		free(r);
		return result;
	}

	//转小写
	static string str_tolower(const char* c)
	{
		char* r = strdup(c);
		for (int i = 0; r[i] != 0; i++)
		{
			r[i] = tolower(r[i]);
		}
		string result = r;
		free(r);
		return result;
	}

	static wstring Utf8ToUnicode(const char* buf)
	{
		int len = ::MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
		if (len == 0) return L"";

		std::vector<wchar_t> unicode(len);
		::MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);

		return &unicode[0];	
	}

	static string UnicodeToUtf8(const wchar_t* buf)
	{
		int len = ::WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
		if (len == 0) return "";

		std::vector<char> utf8(len);
		::WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);

		return &utf8[0];
	}

	static wstring AnsiToUnicode(const char* buf)
	{
		//return Utf8ToUnicode(buf);
		int len = ::MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
		if (len == 0) return L"";

		std::vector<wchar_t> unicode(len);
		::MultiByteToWideChar(CP_ACP, 0, buf, -1, &unicode[0], len);

		return &unicode[0];
	}

	static string UnicodeToAnsi(const wchar_t* buf)
	{
		wstring wstr = buf;
		int len = ::WideCharToMultiByte(CP_ACP, 0, buf, wstr.length(), NULL, 0, NULL, NULL);
		if (len == 0) return "";

		std::vector<char> utf8(len + 1);
		::WideCharToMultiByte(CP_ACP, 0, buf, wstr.length() + 1, &utf8[0], len + 1, NULL, NULL);
		utf8[len] = '\0';
		string str = &utf8[0];
		return &utf8[0];
	}

}

#endif