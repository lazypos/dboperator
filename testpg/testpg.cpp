// testpg.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <libpq-fe.h>
#include <string>
#include "postgresql_opt.h"
#include "sqlite_opt.h"
using namespace std;

void testpg()
{
	string	err;
	dbopt_pg mypg("127.0.0.1","5432","postgres","zcw","123");
	if (mypg.db_open())
	{
		if (!mypg.db_exec("create table ccc (id int, name varchar(100))",err))
			printf(err.c_str());
		pgrecode_set recode_set;
		if (mypg.is_connected() && mypg.db_query("select * from aaa", recode_set, err))
		{
			for (int i=0; i<recode_set.get_cols_counts(); i++)
				printf("%-15s", recode_set.get_filed_name(i).c_str());
			printf("\r\n");
			while (!recode_set.is_eof())
			{
				for (int i=0; i<recode_set.get_cols_counts(); i++)
					printf("%-15s", recode_set.get_value(i).c_str());
				printf("\r\n");

				recode_set.move_next();
			}
		}
		else
			printf(err.c_str());
	}
}


void testsqlite()
{
	string	err;
	dbopt_sqlite mypg(":memory:");
	if (mypg.db_open())
	{
		if (!mypg.db_exec("create table ccc (id int, name varchar(100))",err))
			printf(err.c_str());
		if (!mypg.db_exec("insert into ccc values(123, 'zzz')",err))
			printf(err.c_str());
		if (!mypg.db_exec("insert into ccc (id)values(123)",err))
			printf(err.c_str());
		printf("\r\n");
		sqliterecode_set recode_set;
		if (mypg.is_connected() && mypg.db_query("select * from ccc", recode_set, err))
		{
			for (int i=0; i<recode_set.get_cols_counts(); i++)
				printf("%-15s", recode_set.get_filed_name(i).c_str());
			printf("\r\n");
			while (!recode_set.is_eof())
			{
				for (int i=0; i<recode_set.get_cols_counts(); i++)
					printf("%-15s", recode_set.get_value(i).c_str());
				printf("\r\n");

				recode_set.move_next();
			}
		}
		else
			printf(err.c_str());
	}
}

int main(int argc, char* argv[])
{
	testsqlite();

	return 0;
}

