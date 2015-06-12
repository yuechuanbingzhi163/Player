#include "StdAfx.h"
#include "c_winsock.h"
#include "c_file_server.h"


c_file_server::c_file_server()
{
}

c_file_server::~c_file_server()
{

}



int	c_file_server::on_connect(c_winsock * con)
{
	return 0;
}

int	c_file_server::on_fail(c_winsock * con, int flag)
{
	return 0;
}

int	c_file_server::on_disconnect(c_winsock * con, int flag)
{
	return 0;
}

int	c_file_server::on_release(c_winsock * con)
{
	return 0;
}

int	c_file_server::on_read(c_winsock * con, int count)
{
	return 0;
}

int	c_file_server::on_write(c_winsock * con, int count)
{
	return 0;
}

void c_file_server::on_timer(c_winsock * con)
{

}

void c_file_server::on_error(c_winsock * con, int error)
{

}

int c_file_server::_connect(const char* server, uint16 port)
{
	m_conn._connect(server,port,true);
	m_conn.setdispatcher(this);
	return 0;
}

int c_file_server::_disconnect()
{
	m_conn._disconnect();
	return -1;
}

int c_file_server::_send()
{
	return 0;
}

int c_file_server::_recv()
{
	return 0;
}
