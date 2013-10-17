#ifndef SQLITE_OPT_H
#define SQLITE_OPT_H
#include "sqliterecode_set.h"

class sqlite_opt
{
public:
	sqlite_opt(const string& dbpath);
	~sqlite_opt(void);

	bool		db_open();
	void		db_close();
	bool		is_connected();

	bool		db_exec(const string& sql, string& errmsg);
	bool		db_query(const string& sql, sqliterecode_set& recode_set, string& errmsg);

private:
	sqlite3		*_pconn;
	bool		_isconnected;
	string		_dbpath;
};

typedef sqlite_opt dbopt_sqlite;

#endif