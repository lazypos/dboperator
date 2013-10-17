#ifndef RECODE_SET_BASE_H
#define RECODE_SET_BASE_H
#include <string>
using namespace std;

class recode_set_base
{
public:
	recode_set_base(void):_rowiter(0),_rows(0),_cols(0){}
	virtual	~recode_set_base(void){}

	
	int			get_rows_counts(){return _rows;}
	int			get_cols_counts(){return _cols;}

	bool		is_eof(){return (_rowiter >= _rows);}
	void		move_first(){_rowiter = 0;}
	void		move_next(){_rowiter++;}

	int			get_value_int(int index){return atoi(get_value(index).c_str());}
	int			get_value_int(const char* filedname){return atoi(get_value(filedname).c_str());}

	// 子类只需实现这三个函数
	virtual string		get_filed_name(int index) = 0;
	virtual string		get_value(int index) = 0;
	virtual string		get_value(const char* filedname) = 0;

protected:
	int			_rowiter;
	int			_rows;
	int			_cols;
};

#endif