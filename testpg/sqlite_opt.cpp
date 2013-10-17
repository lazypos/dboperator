#include "StdAfx.h"
#include "sqlite_opt.h"

sqlite_opt::sqlite_opt(const string& dbpath)
: _isconnected(false), _pconn(NULL), _dbpath(dbpath)
{
}

sqlite_opt::~sqlite_opt(void)
{
	db_close();
}

bool sqlite_opt::db_open()
{
	db_close();

	if (sqlite3_open(_dbpath.c_str(), &_pconn) != SQLITE_OK)
		return false;

	_isconnected = true;
	return true;
}

void sqlite_opt::db_close()
{
	if (_pconn)
	{
		sqlite3_close(_pconn);
		_pconn = NULL;
	}
	_isconnected = false;
}

bool sqlite_opt::is_connected()
{
	return _isconnected;
}

bool sqlite_opt::db_exec( const string& sql, string& errmsg )
{
	bool isok = false;
	if (_pconn)
	{
		char* err = NULL;
		if (sqlite3_exec(_pconn, sql.c_str(), 0,0,&err) == SQLITE_OK)
			isok = true;
		else
		{
			err ? errmsg = err : errmsg = ""; 
			isok = false;
		}
	}
	return isok;
}

bool sqlite_opt::db_query( const string& sql, sqliterecode_set& recode_set, string& errmsg )
{
	bool isok = false;
	if (_pconn)
	{
		char *err = NULL;
		char **rst = NULL;
		int rows = 0, cols = 0;
		if (sqlite3_get_table(_pconn, sql.c_str(), &rst, &rows, &cols, &err) == SQLITE_OK)
		{
			recode_set.set_result(rst, rows, cols);
			isok = true;
		}
		else
		{
			if (rst)
				sqlite3_free_table(rst);

			err ? errmsg = err : errmsg = ""; 
			isok = false;
		}
	}
	return isok;
}
