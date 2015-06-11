#pragma  once


class CMain : public c_singleton<CMain>
{
public:
	int InitSock()
	{
		initsocket();    //³õÊ¼»¯ÍøÂç¿â
		m_pFileServer = static_cast<c_file_server*>(file_server_init());
		if (!m_pFileServer)
			return m_pFileServer->_connect("127.0.0.1",6000);
		return TRUE;
	}

	int UninitSock()
	{
		file_server_release(m_pFileServer);
		uninitsocket();
		return TRUE;
	}

	c_file_server* GetFileServer()
	{
		return m_pFileServer;
	}

	void SetPlayerHWnd(HWND hWnd)
	{
		m_hPlayerWnd = hWnd;
	}

	HWND GetPlayerHWnd()
	{
		return m_hPlayerWnd;
	}

private:
	c_file_server* m_pFileServer;
	HWND m_hPlayerWnd;
};
