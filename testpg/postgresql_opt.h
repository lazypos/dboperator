#ifndef POSTGRESQL_OPT_H
#define POSTGRESQL_OPT_H
#include "pgrecode_set.h"

class postgresql_opt
{
public:
	explicit postgresql_opt(const string& hostname, const string& port, 
		const string& dbname, const string& user, const string& passwd);
	~postgresql_opt(void);

	bool		db_open();
	void		db_close();
	bool		is_connected();

	bool		db_exec(const string& sql, string& errmsg);
	bool		db_query(const string& sql, pgrecode_set& recode_set, string& errmsg);

private:
	string		_host;
	string		_port;
	string		_dbname;
	string		_user;
	string		_passwd;

	PGconn		*_pconn;
	bool		_isconnected;
};

typedef postgresql_opt	dbopt_pg;

#endif