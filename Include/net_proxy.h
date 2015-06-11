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

	//可读  int count 为可读字节数 
	virtual	int on_read(i_proxy_connect* con, int32_t count) = 0;

	//可写 int count 为还需要发送的字节数
	virtual int on_write(i_proxy_connect* con, int32_t count) = 0;

	//关闭连接
	virtual int on_disconnect(int32_t reason, i_proxy_connect* con)	= 0;

	//连接释放
	virtual int on_release(i_proxy_connect* con) = 0;

	//可以收到本线程所有连接信号
	virtual void on_signal(i_proxy_connect* con) = 0;

	//连接线程被重先绑定
	virtual void on_rebind(i_proxy_connect* con) {}
};

class i_proxy_connect
{
public:
	//设置回调器
	virtual void _set_sink(i_proxy_callback* pSub) = 0;	

	//客户端连接，默认为异步连接
	virtual int _connect(const char* addr, uint16_t port, int asyn = 1) = 0;

	//发送数据
	virtual int _send(unsigned char* date, int32_t size) = 0;

	//设置套接字参数
	virtual int _set_opt(int32_t type, void* arg, int32_t size) = 0;

	//获取套接字参数
	virtual int _get_opt(int32_t type, void* arg, int32_t size) = 0;

	//断开连接
	virtual int _disconnect(void) = 0;

	//是否连接 0断开 1连接
	virtual int _isconnect(void) = 0;

	//析构连接对像
	virtual int _release(void) = 0;

	//多线程异步发送信息
	virtual int _signal(void) = 0;

	//重先绑定线程
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