#pragma once

#define  SOCK_BUFF_MAX   48 * 1024
#define  SOCK_TIMEROUT    3 * 1000

 
class i_sock_dispatcher;

class c_winsock
{
public:
	c_winsock(void);
	~c_winsock(void);

public:
	//��ʼ������
	static int init();   
	//�ͷ�
	static void release();  
	//��������
	static c_winsock * create_connect(i_sock_dispatcher * conn);
	int _connect(const char * ipaddr, int16 port, bool asyn = false);
	int _disconnect();
	int _send(const char * data, int size);
	int _recv(char ** data, int size);
	int _get_recv_size();
	void _clear_recv(int size);
	void _settimer(int msec);  //����
	void _setrectimer(int msec);  //����
	int _setsockopt(int level, int optname,const void *optval, socklen_t optlen);

private:
	static unsigned long __stdcall ThreadProc(void* lParam);
	virtual void Execute();
	void setdispatcher(i_sock_dispatcher * dispatcher);
	int  onconnect();
	int  create_thead();
	void close_thead();


	int  onread(int count);
	int  onwrite();
public:
	static WSADATA  s_wsadata;
private:
	SOCKET  m_sock;
	struct sockaddr_in m_addr;
	fd_set m_fdset;
	i_sock_dispatcher *m_pDispatch;

	DWORD m_msectime;
	DWORD m_dwtick;

	//�߳�
	thread_t m_utheadid;
	HANDLE  m_hthead;
	HANDLE  m_henvet;

	string m_addrip;
	int16 m_port;
	bool  m_asyn;

	bool  m_bTheadExit;
	bool  m_bconnect;
	bool  m_bdisconnect;

	int   m_nconnetnum; //��������
	int   m_nrecmsec;  //�������ʱ��(����)
	
	//���ܶ���
	CRingQueue<SOCK_BUFF_MAX>	m_sendbuff;
	//���ܶ���
	CRingQueue<SOCK_BUFF_MAX>	m_recvbuff;
 };

