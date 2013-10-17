#include "pgrecode_set.h"

pgrecode_set::pgrecode_set(void)
: _rst(NULL)
{
}

pgrecode_set::~pgrecode_set(void)
{
	if (_rst)
		PQclear(_rst);
}

void pgrecode_set::set_result( PGresult* rst )
{
	if (_rst)
		PQclear(_rst);
	
	_rst		= rst;
	_rowiter	= 0;
	_rows		= PQntuples(_rst);
	_cols		= PQnfields(_rst);
}

string pgrecode_set::get_value( int index )
{
	if (!_rst)
		return "";

	char* p = PQgetvalue(_rst, _rowiter, index);
	if (p)
		return p;
	else
		return "";
}

std::string pgrecode_set::get_value( const char* filedname )
{
	if (!_rst)
		return "";

	for (int i=0; i<_cols; i++)
	{
		if (strcmp(PQfname(_rst, i), filedname) == 0)
			return get_value(i);
	}
	return "";
}

string pgrecode_set::get_filed_name( int index )
{
	if (!_rst)
		return "";

	return PQfname(_rst, index);
}


