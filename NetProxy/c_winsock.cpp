#include "StdAfx.h"
#include "net_proxy.h"
#include "c_winsock.h"
#include <mstcpip.h>  

WSADATA  c_winsock::s_wsadata = {0};

//初始化网络
int c_winsock::init()
{
	//初始化套接字动态库
	if (WSAStartup(MAKEWORD(2,2), &s_wsadata) != 0)
	{
		printf("初始化套接字动态库失败!\n");
		return -1;
	}
	return 0;
}
//释放
void c_winsock::release()
{
	WSACleanup();        //释放套接字资源
}
//创建连接
c_winsock * c_winsock::create_connect(i_sock_dispatcher * dispatcher)
{
	c_winsock * con = new c_winsock();
	if (con == NULL)
		return NULL;
	con->setdispatcher(dispatcher);
	return con;
}

c_winsock::c_winsock(void)
	:m_pDispatch(NULL)
	,m_sock(NULL)
	,m_hthead(NULL)
	,m_henvet(NULL)
	,m_msectime(100)
	,m_dwtick(GetTickCount())
	,m_bTheadExit(true)
	,m_bconnect(false)
	,m_bdisconnect(false)
	,m_nconnetnum(0)
	,m_nrecmsec(3000)
{
	
}

c_winsock::~c_winsock(void)
{
	_disconnect();
	c_winsock::release();
}


int c_winsock::_connect(const char * ipaddr, int16 port, bool asyn)
{
	int result = 0;
	struct hostent *hp;  
	unsigned int addr;  
	memset( &m_addr, 0, sizeof( sockaddr));

	m_addrip = ipaddr;
	m_port = port;
	m_asyn = asyn;
	if ( m_sock != NULL )
	{
		_disconnect();
		return -1;
		//_disconnect();
	}
	
	/*WSADATA  wsadata = {0};
	result = WSAStartup(MAKEWORD(2,2), &wsadata);
	*/
	m_sock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if( m_sock == INVALID_SOCKET)
	{
		m_sock = NULL;
		return -1;
	}

	//决定服务器地址  
	if(inet_addr(ipaddr)==INADDR_NONE)  
	{  
		hp=gethostbyname(ipaddr);  
		if (hp == NULL)
		{
			create_thead();
			closesocket(m_sock);
			m_sock = NULL;
			return -1;
		}
		m_addr.sin_addr.s_addr =  *((unsigned long*)hp->h_addr); 
	}  
	else  
	{  
		addr = inet_addr(ipaddr);  
		m_addr.sin_addr.s_addr = addr;
		//hp=gethostbyaddr((char*)&addr,sizeof(addr),AF_INET);  
	}  
	

	m_addr.sin_family = AF_INET;
	m_addr.sin_port = htons(port);
	//m_addr.sin_addr.s_addr =  *((unsigned long*)hp->h_addr);  

	/////////////////////////////////////////////////////////////////

	//1.设置非阻塞模式
	if (asyn)
	{
		unsigned long ulFlag = 1;
		if ( ioctlsocket(m_sock, FIONBIO, &ulFlag) != 0 )  
		{ 
			closesocket(m_sock); 
			m_sock = NULL;
			return -1; 
		} 
	}

	//2.连接服务器
	result = connect(m_sock, ( SOCKADDR*)&m_addr, sizeof(m_addr));
	if (result == SOCKET_ERROR)
	{
		if (!asyn)
		{
			result = WSAGetLastError();
			closesocket(m_sock); 
			m_sock = NULL;
			return -1;
		}

	}

	FD_ZERO(&m_fdset);
	FD_SET( m_sock, &m_fdset );
	m_dwtick = GetTickCount();

	if (create_thead() != 0)
	{
		m_sock = NULL;
		return -1; 
	}

	//3.等待连接
	//if (!asyn)  //同步
	//{
	//	if ( !WaitForSingleObject(m_henvet, INFINITE) )
	//	{
	//		closesocket(m_sock); 
	//		m_sock = NULL;
	//		close_thead();
	//		return -1;
	//	}
	//
	//}
	
	return 0;
}


int c_winsock::_disconnect()
{
	m_bdisconnect = true;
	m_bconnect = false;
	close_thead();
	if (m_sock != NULL)
	{
		closesocket(m_sock);
		m_sock = NULL;
	}
	m_recvbuff.clear();
	m_sendbuff.clear();
	return 0;
}

int c_winsock::_send(const char * data, int size)
{
	int result = 0;
	if (!m_bconnect)
	{
		return -1;
	}
    if (m_sendbuff.Count() >= SOCK_BUFF_MAX)
	{
		result = 2;
	}
	else
	{
		m_sendbuff.Append((unsigned char *)data, size);
	}
	//onwrite();
	return result;
}

int c_winsock::_recv(char ** data, int size)
{
	m_recvbuff.Attach((unsigned char **)data, size);
	if (data == NULL)
	{
		return -1;
	}
	return 0;
}
int c_winsock::_get_recv_size()
{
	return m_recvbuff.Count();
}
void c_winsock::_clear_recv(int size)
{
	m_recvbuff.Advance(size);
}

void c_winsock::_settimer(int msec)
{
	m_msectime = msec;
}

void c_winsock::_setrectimer(int msec)
{
	m_nrecmsec = msec;
}

int c_winsock::_setsockopt(int level, int optname,const void *optval, socklen_t optlen)
{
	return setsockopt( m_sock, level, optname, (const char *)optval, optlen );
}

void c_winsock::setdispatcher(i_sock_dispatcher * dispatcher)
{
	m_pDispatch = dispatcher;
}

int c_winsock::create_thead()
{
	if (m_hthead != NULL)
	{
		return 0;
	}
	m_bTheadExit = false;
	m_hthead = CreateThread(NULL, 0, ThreadProc, this, CREATE_SUSPENDED, &m_utheadid);
	//m_hthead = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, this, 0, &m_utheadid);
	if (m_hthead == NULL)
		return -1;

	m_henvet = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (m_henvet == NULL)
	{
		::CloseHandle(m_hthead);
		m_hthead = NULL;
		return -1;
	}
	//提升线程等级
	SetThreadPriority(m_hthead, THREAD_PRIORITY_HIGHEST);
	ResumeThread(m_hthead);
	return 0;
}

void c_winsock::close_thead()
{
	m_bTheadExit = true;
	if (m_henvet != NULL)
	{
		::CloseHandle(m_henvet);
		m_henvet = NULL;
	}
	if (m_hthead != NULL)
	{
		::CloseHandle(m_hthead);
		WaitForSingleObject(m_hthead, 100);
		m_hthead = NULL;
	}

}

unsigned long __stdcall c_winsock::ThreadProc(void* lParam)
{
	c_winsock * pthis = (c_winsock *)lParam;
	if (pthis != NULL)
	{
		pthis->Execute();
	}
	return 0;
}

void c_winsock::Execute()
{
	int iret;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
	while(!m_bTheadExit)
	{

		fd_set fdsetRead;  
		fdsetRead = m_fdset;  

		fd_set fdsetwrite;  
		fdsetwrite = m_fdset;  

		fd_set fdsetexceptds;  
		fdsetexceptds = m_fdset;  

		if (m_sock)
		{
			iret = select( 0, &fdsetRead, &fdsetwrite, &fdsetexceptds, &timeout );
			switch( iret )
			{
				//错误
			case SOCKET_ERROR:
				{
					if (m_pDispatch)
					{
						m_pDispatch->on_error(this, WSAGetLastError());
						_disconnect();
					}
				}
				break;
				//超时
			case 0:
				{

				}
				break;
				//default
			default:
				{
					if(FD_ISSET(m_sock, &fdsetwrite))    //发现可写  
					{
						if (!m_bconnect)
						{
							SetEvent(m_henvet);
							if (onconnect() == 0)
							{
								if (m_pDispatch)
								{
									m_pDispatch->on_connect(this);
								}
							}
							else
							{
								if (m_pDispatch)
								{
									m_pDispatch->on_fail(this, WSAGetLastError());
								}
								_disconnect();
							}
							continue;
						}
						onwrite();
					}
					if (FD_ISSET(m_sock, &fdsetRead ))
					{
						unsigned long ulReadLen = 0;
						ioctlsocket(m_sock, FIONREAD, &ulReadLen);
						if ( ulReadLen > 0 )
						{
							onread(ulReadLen);
						}
						else //缓存区没有数据, 判断是否断开
						{
							if (m_bconnect)
							{
								if (ulReadLen == 0) //正常断开
								{
									if (m_pDispatch)
									{
										m_pDispatch->on_disconnect(this, 0);
									}
									_disconnect();
									continue;
								}
								else if (ulReadLen == -1 && 
									WSAGetLastError() == EINTR) //socket正常状态
								{
									//.....
								}
								else  //异常断开
								{
									if (m_pDispatch)
									{
										m_pDispatch->on_fail(this, ulReadLen);
									}
									_disconnect();
									continue;
								}
							}
							else
							{

							}
						}
					}
					if (FD_ISSET(m_sock, &fdsetexceptds))  //错误
					{
						if (m_bconnect)
						{
							if (m_pDispatch)
							{
								m_pDispatch->on_error(this, WSAGetLastError());
							}
							_disconnect();
						}
						else
						{
							SetEvent(m_henvet);
							if (m_pDispatch)
							{
								m_pDispatch->on_fail(this, WSAGetLastError());
							}
							_disconnect();
						}
					}
				}
			}
		}
		else
		{
			if (!m_bdisconnect)  //启动重连
			{
				m_nconnetnum++;
				if (m_nconnetnum > 3)
				{
					Sleep(m_nrecmsec);
				}
				printf("av res connect m_nconnetnum=%d\n", m_nconnetnum);
				_connect(m_addrip.c_str(), m_port, m_asyn);
			}
			else
			{
				break;
			}
		}
		if (GetTickCount() - m_dwtick >= m_msectime)
		{
			if (m_pDispatch)
			{
				m_pDispatch->on_timer(this);
			}
			m_dwtick = GetTickCount();
		}
		_sleep(10);
	}
	if (m_pDispatch)
	{
		m_pDispatch->on_release(this);
		delete this;
	}
}

int  c_winsock::onread(int count)
{
	if (m_sock == NULL)
		return -1;
	char buff[SOCK_BUFF_MAX];
	unsigned long ulReadLen = 0;
	int iRet = 0;
	while( ulReadLen < count )
	{
		iRet = recv(m_sock, buff, count - ulReadLen, 0);
		if ( SOCKET_ERROR == iRet || iRet == 0)
		{
			return -1;
		}
		ulReadLen += iRet;
		m_recvbuff.Append(buff, iRet);
	}
	if (m_pDispatch)
	{
		m_pDispatch->on_read(this, m_recvbuff.Count());
	}
	return 0;
}

int  c_winsock::onwrite()
{
	if (m_sock == NULL)
	 return -1;
	unsigned long ulSendLen = 0;
	unsigned int iRet = 0;
	unsigned char * pbuff = NULL;
	while(m_sendbuff.Count() > 0)
	{
		ulSendLen = min(m_sendbuff.Count(), SOCK_BUFF_MAX);
		m_sendbuff.Attach(&pbuff, ulSendLen);
		iRet = send(m_sock, (char *)pbuff, ulSendLen, 0 );
		if ( SOCKET_ERROR == iRet || 0 == iRet )
		{
			return -1;
		}
		m_sendbuff.Advance(iRet);
		if (iRet < ulSendLen)
		{
			goto at;
		}
	}
at:	if (m_pDispatch)
	{
		m_pDispatch->on_write(this, SOCK_BUFF_MAX - m_sendbuff.Count());
	}
	return 0;
}

int c_winsock::onconnect()
{
	//设置阻塞模式
	unsigned long  ulFlag = 0;
	if ( ioctlsocket(m_sock, FIONBIO, &ulFlag))
	{
		return -1;
	}

	int keepalive = 1;
	tcp_keepalive live,liveout;    
	live.keepaliveinterval=5000; //每次检测的间隔 （单位毫秒）  
	live.keepalivetime=10000;  //第一次开始发送的时间（单位毫秒）  
	live.onoff=TRUE;    
	int iRet = setsockopt( m_sock, SOL_SOCKET, SO_KEEPALIVE, (const char *)&keepalive, sizeof(int) ); 
	if(iRet == 0){    
		DWORD dw;  
		if(WSAIoctl((SOCKET)m_sock,SIO_KEEPALIVE_VALS,&live,sizeof(live),  
			&liveout,sizeof(liveout),&dw,NULL,NULL)== SOCKET_ERROR){  
				//Delete Client    
				return -1;    
		}    
	}   

	//设置超时
	int timeout = SOCK_TIMEROUT;
	if(setsockopt( m_sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&timeout, sizeof(int) ))
	{
		return -1;
	}
	if(setsockopt( m_sock, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(int) ))
	{
		return -1;
	}
	//设置缓冲大小
	int nbuffsize = SOCK_BUFF_MAX;
	if(setsockopt( m_sock, SOL_SOCKET, SO_SNDBUF, (const char *)&nbuffsize, sizeof(int) ))
	{
		return -1;
	}
	if(setsockopt( m_sock, SOL_SOCKET, SO_RCVBUF, (const char *)&nbuffsize, sizeof(int) ))
	{
		return -1;
	}

	int bNodelay = 0; 
	setsockopt(m_sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&bNodelay, sizeof(int));   
	m_bconnect = true; 
	m_nconnetnum = 0;
	return 0;
}