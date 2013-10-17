#include "StdAfx.h"
#include "sqliterecode_set.h"

sqliterecode_set::sqliterecode_set(void)
: _rst(NULL)
{
}

sqliterecode_set::~sqliterecode_set(void)
{
}

void sqliterecode_set::set_result( char** rst, int rows, int cols )
{
	if (_rst)
		sqlite3_free_table(_rst);

	_rst		= rst;
	_rowiter	= 0;
	_rows		= rows;
	_cols		= cols;
}

std::string sqliterecode_set::get_value( int index )
{
	if (!_rst)
		return "";

	int pos = _cols * (_rowiter + 1) + index;
	return _rst[pos] ? _rst[pos] : "";
}

std::string sqliterecode_set::get_value( const char* filedname )
{
	if (!_rst)
		return "";

	for (int i=0; i<_cols; i++)
	{
		if (_rst[i] && strcmp(_rst[i], filedname) == 0)
			return get_value(i);
	}
	return "";
}

std::string sqliterecode_set::get_filed_name( int index )
{
	if (!_rst || !_rst[index])
		return "";

	return _rst[index];
}
