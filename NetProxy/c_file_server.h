#ifndef _C_FILE_SERVER_H
#define _C_FILE_SERVER_H



class c_file_server : public i_sock_dispatcher ,public i_file_server
{
public:
	c_file_server();
	~c_file_server();

	//dll 向外发数据
	virtual int on_connect(c_winsock * con);
	virtual int on_fail(c_winsock * con, int flag);
	virtual int on_disconnect(c_winsock * con, int flag);
	virtual int on_release(c_winsock * con);
	virtual int on_read(c_winsock * con, int count);
	virtual int on_write(c_winsock * con, int count);
	virtual void on_timer(c_winsock * con);
	virtual void on_error(c_winsock * con, int error);

	//dll 接收数据
	int	_connect(const char* server, uint16 port);
	int	_disconnect();
	int _recv();
	int _send();

private:
	c_winsock* m_pConn;
};


#endif