#ifndef  pgrecode_set_H
#define pgrecode_set_H
#include <libpq-fe.h>
#include "recode_set_base.hpp"

class pgrecode_set
	: public recode_set_base
{
public:
	pgrecode_set(void);
	~pgrecode_set(void);

	string		get_value(int index);
	string		get_value(const char* filedname);
	string		get_filed_name(int index);
	
	// 设置结果集
	void		set_result(PGresult* rst);

private:
	PGresult	*_rst;
};

#endif