#ifndef _C_PROXY_H
#define _C_PROXY_H


class IProxy
{
public:
	virtual bool _send(/*wisdom_zpacket & packet*/) = 0;
	virtual bool _connect(const string& ipaddr, uint16 port, bool syn) = 0;
	virtual bool _disconnect() = 0;
	virtual uint32 _get_send_size() = 0;
	virtual uint32 _get_recv_size() = 0;

};


class c_proxy : public IProxy, public i_proxy_connect
{

};


#endif