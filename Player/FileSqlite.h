#pragma once
#include "SqlCommon.h"
#include "SqlField.h"
#include "SqlDatabase.h"
#include "SqlTable.h"
#include "SqlRecord.h"

class CFileSQLite
	: public c_singleton<CFileSQLite>
{
public:
	CFileSQLite(void);
	~CFileSQLite(void);

	bool open(string & filename);
	void close();
	bool isopen();

	void push(LPCTSTR lpFile, LPCTSTR lpUrl);
	tstring get_file(LPCTSTR lpUrl);
	bool  get_file(LPCTSTR lpUrl, LPCTSTR lpFile);
private:
	sql::Database m_db;
	sql::Table  * m_pTable;
	rw_lock	   m_lock;
};
