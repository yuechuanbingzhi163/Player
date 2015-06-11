#ifndef _NET_PROXY_H
#define _NET_PROXY_H



#ifdef NETPROXY_EXPORTS
#define PROXY_API __declspec(dllexport)
#else
#define PROXY_API __declspec(dllimport)
#endif

#ifdef WINSOCK_EXPORTS
#define SOCK_API __declspec(dllexport)
#else
#define SOCK_API __declspec(dllimport)
#endif

#define EXTERN_C	extern "C"


class i_proxy_connect;
class i_proxy_callback
{
	virtual int on_connect(int32_t, i_proxy_connect*) {return 0;}

	//�ɶ�  int count Ϊ�ɶ��ֽ��� 
	virtual	int on_read(i_proxy_connect* con, int32_t count) = 0;

	//��д int count Ϊ����Ҫ���͵��ֽ���
	virtual int on_write(i_proxy_connect* con, int32_t count) = 0;

	//�ر�����
	virtual int on_disconnect(int32_t reason, i_proxy_connect* con)	= 0;

	//�����ͷ�
	virtual int on_release(i_proxy_connect* con) = 0;

	//�����յ����߳����������ź�
	virtual void on_signal(i_proxy_connect* con) = 0;

	//�����̱߳����Ȱ�
	virtual void on_rebind(i_proxy_connect* con) {}
};

class i_proxy_connect
{
public:
	//���ûص���
	virtual void _set_sink(i_proxy_callback* pSub) = 0;	

	//�ͻ������ӣ�Ĭ��Ϊ�첽����
	virtual int _connect(const char* addr, uint16_t port, int asyn = 1) = 0;

	//��������
	virtual int _send(unsigned char* date, int32_t size) = 0;

	//�����׽��ֲ���
	virtual int _set_opt(int32_t type, void* arg, int32_t size) = 0;

	//��ȡ�׽��ֲ���
	virtual int _get_opt(int32_t type, void* arg, int32_t size) = 0;

	//�Ͽ�����
	virtual int _disconnect(void) = 0;

	//�Ƿ����� 0�Ͽ� 1����
	virtual int _isconnect(void) = 0;

	//�������Ӷ���
	virtual int _release(void) = 0;

	//���߳��첽������Ϣ
	virtual int _signal(void) = 0;

	//���Ȱ��߳�
	virtual int _rebind(long bind_tid) = 0;
};


EXTERN_C PROXY_API void net_proxy_init();

EXTERN_C PROXY_API void net_proxy_release();



class c_winsock;
class i_sock_dispatcher
{
public:
	virtual int on_connect(c_winsock * con) = 0;
	virtual int on_fail(c_winsock * con, int flag) = 0;
	virtual int on_disconnect(c_winsock * con, int flag) = 0;
	virtual int on_release(c_winsock * con) = 0;
	virtual int on_read(c_winsock * con, int count) = 0;
	virtual int on_write(c_winsock * con, int count) = 0;
	virtual void on_timer(c_winsock * con) = 0;
	virtual void on_error(c_winsock * con, int error) = 0;
};

class i_file_server
{
	virtual int _connect(const char* server, uint16 port) = 0;
	virtual int _disconnect() = 0;
	virtual int _send() = 0;
	virtual int _recv() = 0;
};



EXTERN_C SOCK_API  void initsocket();

EXTERN_C SOCK_API  void uninitsocket();

EXTERN_C SOCK_API  i_file_server* file_server_init();

EXTERN_C SOCK_API  void file_server_release(i_file_server* pServer);


#endif