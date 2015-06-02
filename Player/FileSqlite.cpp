#include "StdAfx.h"
#include "FileSqlite.h"


#define   file_tag_path          "filepath"
#define   file_tag_url           "fileurl"
#define   file_tag_time          "time"

using namespace sql;
sql::Field definition_sysfile[] = 
{
	sql::Field(sql::FIELD_KEY),
	sql::Field(file_tag_url, sql::type_text, sql::flag_not_null),
	sql::Field(file_tag_path, sql::type_text, sql::flag_not_null),
	sql::Field(file_tag_time, sql::type_time),
	sql::Field(sql::DEFINITION_END),
};

CFileSQLite::CFileSQLite()
	: m_pTable(NULL)
{

}

CFileSQLite::~CFileSQLite()
{
	close();
}

bool CFileSQLite::open(string & filename)
{
	if (isopen())
		return true;
	string tablename = "playerfile";
	if (!m_db.open(filename))
		return false;

	m_pTable = new sql::Table(m_db.getHandle(), tablename, definition_sysfile);
	if (m_pTable == NULL)
		return false;

	if (!m_pTable->exists())
		if (!m_pTable->create())
			return false;
	return true;
}

void CFileSQLite::close()
{
	if (m_db.isOpen())
	{
		m_db.close();
	}
	if (m_pTable != NULL)
	{
		delete m_pTable;
		m_pTable = NULL;
	}
}

bool CFileSQLite::isopen()
{
	if (m_pTable == NULL)
		return false;
	return m_db.isOpen();
}

void CFileSQLite::push(LPCTSTR lpFile, LPCTSTR lpUrl)
{
	if (!isopen())
		return;

	c_wlock lock(&m_lock);
	Record record(m_pTable->fields());
	record.setString(file_tag_path, UnicodeToUtf8(lpFile));
	record.setString(file_tag_url, UnicodeToUtf8(lpUrl));
	record.setTime(file_tag_time, sql::time(0));
	m_pTable->addRecord(&record);
}

tstring CFileSQLite::get_file(LPCTSTR lpUrl)
{
	TCHAR szFile[MAX_PATH] = {0};
	get_file(lpUrl, szFile);
	return szFile;
}

bool CFileSQLite::get_file(LPCTSTR lpUrl, LPCTSTR lpFile)
{
	if (!isopen())
		return false;
	c_wlock lock(&m_lock);
	tstring strRet;
	char szcmd[256] = {0};
	sprintf(szcmd, "%s='%s'", file_tag_url, zn::UnicodeToUtf8(lpUrl).c_str());
	if (!m_pTable->open(szcmd))
		return false;

	if (Record* record = m_pTable->getRecord(0))
	{
		strRet = zn::Utf8ToUnicode(record->getValue(file_tag_path)->asString().c_str());
		if (!c_file::file_exists(UnicodeToAnsi(strRet.c_str()).c_str())) //判断文件是否存在，不存在则删除记录
		{
			m_pTable->deleteRecords(szcmd);
		}
		else
		{
			_tcscpy((wchar_t*)lpFile, strRet.c_str());
			return true;
		}
	}
	return false;
}