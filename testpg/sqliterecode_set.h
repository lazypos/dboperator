#ifndef SQLITERECODE_SET_H
#define SQLITERECODE_SET_H
#include <sqlite3.h>
#include "recode_set_base.hpp"

class sqliterecode_set
	: public recode_set_base
{
public:
	sqliterecode_set(void);
	~sqliterecode_set(void);

	string		get_value(int index);
	string		get_value(const char* filedname);
	string		get_filed_name(int index);


	void	set_result(char** rst, int rows, int cols);

private:
	char**	_rst;
};

#endif