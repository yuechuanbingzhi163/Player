
#ifndef df_macro_h
#define df_macro_h

#ifndef _MSC_VER
#ifdef __x86_64__
#include "atomic64.h"
#else
#include "atomic32.h"
#endif
#endif

//��ȡ�߳�ID
#ifdef _MSC_VER
#define _tid() ::GetCurrentThreadId() 
#else
#define _tid() pthread_self()
#endif

//��ȡ�ڴ��С
#ifdef _MSC_VER
#define _mem_size(x)  _msize(x)
#else
#define _mem_size(x)  malloc_usable_size(x)
#endif

#ifdef _MSC_VER
#define _atom long
#else
#define _atom atomic_t
#endif

//��ʼ��
#ifdef _MSC_VER
#define _atom_init(x) 	(x=0)
#else
#define _atom_init(x) 	atomic_set(&x, 0)
#endif


//ԭ�Ӷ�ȡ
#ifdef _MSC_VER
#define _atom_read(x) (*x)
#else
#define _atom_read(x) atomic_read(x)
#endif

//ԭ�Ӽ�һ
#ifdef _MSC_VER
#define _atom_add_one(x) InterlockedIncrement(x)
#else
#define _atom_add_one(x) atomic_add_return(1, x)
#endif

//ԭ�Ӽ�N
#ifdef _MSC_VER
	#define _atom_add(x, n)	InterlockedExchangeAdd(x, n)
#else
	#define _atom_add(x, n)	atomic_add_return(n, x)
#endif

#ifdef _MSC_VER
#define _atom_sub(x, n)	InterlockedExchangeAdd(x, -n)
#else
#define _atom_sub(x, n)	atomic_add_return(-n, x)
#endif

//ԭ���Լ�һ
#ifdef _MSC_VER
#define _atom_sub_one(x) InterlockedDecrement(x)
#else
#define _atom_sub_one(x) atomic_sub_return(1, x)
#endif


//ԭ�ӱȽ�
#ifdef _MSC_VER
#define _atom_compare(x,y) (InterlockedCompareExchange(x, y, y) == y)
#else
#define _atom_compare(x,y) (atomic_read(x) == y)
#endif


//�л��̺߳���
#ifdef _MSC_VER
#define switch_thread()		SwitchToThread()
#else
#define switch_thread()		sched_yield()
#endif

//��Ϣ����
#ifdef _MSC_VER
#ifndef _sleep
#define _sleep(x)			Sleep(x)
#endif
#else
#define _sleep(x)			usleep(x * 1000)
#endif

#ifdef _MSC_VER
#define S_ISREG(m) (((m) & 0170000) == (0100000))
#define S_ISDIR(m) (((m) & 0170000) == (0040000))
#endif

#ifdef WIN32
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define strdup _strdup
#endif

static int urlcasecmp(const char* url, const char* sub, int len)
{
	if (strncasecmp(url, sub, len) == 0)
	{
		if (url[len] == 0 || url[len] == '\\' || url[len] == '/' || url[len] == '?')
			return 0;
	}

	return -1;
}

#if defined(_MSC_VER) && _MSC_VER < 1300
#define __func__ "??"
#else
#define __func__ __FUNCTION__
#endif

//��Ϣ����
#ifdef _MSC_VER
#define thread_t			unsigned long		
#else
#define thread_t			pthread_t
#endif

#ifdef _MSC_VER
#undef socklen_t
#define socklen_t	int
#endif

#ifdef _MSC_VER
#define 	z_atoi				_atoi64
#else
#define         z_atoi          atoll
#endif

#define		$64					"%I64u"

#ifndef _MSC_VER
#define		Z_MEMINFO			"/proc/meminfo"
#define		Z_CPUINFO			"/proc/cpuinfo"
#define		Z_STAT				"/proc/stat"
#else
#define		Z_MEMINFO			"e:/meminfo"
#define		Z_CPUINFO			"e:/cpuinfo"
#define		Z_STAT				"e:/stat"
#endif

#ifndef _LARGEFILE_SOURCE
#define _LARGEFILE_SOURCE
#define _FILE_OFFSET_BITS	64
#endif

#endif   //df_mac
