#include "postgresql_opt.h"
#include <sstream>

postgresql_opt::postgresql_opt(const string& hostname, const string& port, 
							   const string& dbname, const string& user, const string& passwd)
: _pconn(NULL), _isconnected(false), _host(hostname), _port(port)
, _dbname(dbname), _user(user), _passwd(passwd)
{
}

postgresql_opt::~postgresql_opt(void)
{
	db_close();
}

bool postgresql_opt::db_open()
{
	db_close();

	ostringstream os;
	os << "hostaddr=" << _host
		<< " port=" << _port
		<< " dbname=" << _dbname
		<< " user=" << _user
		<< " password=" << _passwd;

	_pconn = PQconnectdb(os.str().c_str());
	if (PQstatus(_pconn) == CONNECTION_OK)
		_isconnected = true;
	else
		return false;

	return true;
}

void postgresql_opt::db_close()
{
	if (_pconn)
	{
		PQfinish(_pconn);
		_pconn = NULL;
	}

	_isconnected = false;
}


bool postgresql_opt::is_connected()
{
	return _isconnected;
}


bool postgresql_opt::db_exec( const string& sql, string& errmsg )
{
	bool	isok = false;
	if (_pconn)
	{
		PGresult *rst = PQexec(_pconn, sql.c_str());
		ExecStatusType status = PQresultStatus(rst);
		if (status == PGRES_COMMAND_OK || status == PGRES_TUPLES_OK)
			isok = true;
		else
		{
			errmsg = PQerrorMessage(_pconn);
			if (status == PGRES_FATAL_ERROR // ¶Ï¿ªÅÐ¶Ï
				&& errmsg.find("server closed") != string::npos)
				_isconnected = false;
		}

		if (rst)
			PQclear(rst);
	}
	return isok;
}

bool postgresql_opt::db_query( const string& sql, pgrecode_set& recode_set, string& errmsg )
{
	bool	isok = false;
	if (_pconn)
	{
		PGresult *rst = PQexec(_pconn, sql.c_str());
		ExecStatusType status = PQresultStatus(rst);
		if (status == PGRES_TUPLES_OK)
		{
			recode_set.set_result(rst);
			isok = true;
		}
		else
		{
			errmsg = PQerrorMessage(_pconn);
			if (status == PGRES_FATAL_ERROR)
				_isconnected = false;
			
			if (rst)
				PQclear(rst);
		}
	}
	return isok;
}
