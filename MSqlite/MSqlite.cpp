// MSqlite.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sqlite3.h"
#include "Menthol.h"
#pragma comment(lib,"sqlite3.lib")
#pragma comment(lib,"Menthol.lib")

/*
SQLITE3_INTEGER

SQLITE3_FLOAT

SQLITE3_TEXT

SQLITE3_NULL*/

StackState prepare(VmState* vmstate)
{
	const char *statement = GetParam(2,vmstate).str->string;
	int rc;
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1,vmstate).p);
	sqlite3_stmt *stmt;  
	rc = sqlite3_prepare_v2(conn, statement, strlen(statement), &stmt, NULL);   
	
	return Object_CreateObject(stmt);
}



StackState execute(VmState* vmstate)
{
	sqlite3_stmt *stmt = static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p);	
	StackState result = Array_CreateArray(vmstate);

	while (sqlite3_step(stmt) == SQLITE_ROW) 
	{
		StackState _s = Array_CreateArray(vmstate);
		for(int i=0;i<sqlite3_data_count(stmt);i++)
		{
			StackState value;
			switch (sqlite3_column_type(stmt, i)){
					case SQLITE_INTEGER:
						value = Number_CreateNumber(sqlite3_column_int(stmt, i));
						break;
					case SQLITE_FLOAT:
						value = Number_CreateNumber(sqlite3_column_double(stmt, i));
						break;

					case SQLITE_NULL:
						value =Null_CreateNull();
						break;

					case SQLITE3_TEXT:
						value = String_CreateString((char*)sqlite3_column_text(stmt, i),vmstate);
						break;
					case SQLITE_BLOB:
					default:
						break;
			}
			Array_Push(_s.parray,value);
		}
		Array_Push(result.parray,_s);
	}	
	return result;
}



StackState close(VmState* vmstate)
{
	sqlite3_close(static_cast<sqlite3*>(GetParam(1,vmstate).p));
	return Null_CreateNull();
}


StackState connect(VmState* vmstate)
{
  const char *sourcename;
  sqlite3 *conn;
  const char *errmsg;
  int res;

  sourcename = GetParam(1,vmstate).str->string;

#if SQLITE_VERSION_NUMBER > 3006013
  if (strstr(sourcename, ":memory:")) /* TODO: rework this and get/add param 'flag' for sqlite3_open_v2 - see TODO below */
  {
	  res = sqlite3_open_v2(sourcename, &conn, SQLITE_OPEN_READWRITE | SQLITE_OPEN_MEMORY, NULL);
  }
  else
  {
	  res = sqlite3_open_v2(sourcename, &conn, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
  }
#else
  res = sqlite3_open(sourcename, &conn);
#endif
  if (res != SQLITE_OK)
  {
      sqlite3_close(conn);
      return Number_CreateNumber(res);
  }

  return Object_CreateObject(conn);
}

StackState busytimeout(VmState* vmstate)
{
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1,vmstate).p);
	if(!sqlite3_busy_timeout(conn,GetParam(2,vmstate).d))
	{
		return Bool_CreateBool(true);
	}
	return Bool_CreateBool(false);
}

StackState changes(VmState* vmstate)
{
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1,vmstate).p);
	return Number_CreateNumber(sqlite3_changes(conn));
}

StackState errcode(VmState* vmstate)
{
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1,vmstate).p);
	return Number_CreateNumber(sqlite3_errcode(conn));
}

StackState errmsg(VmState* vmstate)
{
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1,vmstate).p);
	return String_CreateString(const_cast<char*>(sqlite3_errmsg(conn)), vmstate);
}

StackState lastinsertrowid(VmState* vmstate)
{
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1,vmstate).p);
	return Number_CreateNumber(sqlite3_last_insert_rowid(conn));
}

StackState version(VmState* vmstate)
{

	StackState ver = Dict_CreateDict(vmstate);
	Dict_Push("versionNumber",ver.pdict,Number_CreateNumber(sqlite3_libversion_number()));
	Dict_Push("versionString", ver.pdict, String_CreateString((char*)sqlite3_libversion(), vmstate));
	return ver;
}




StackState columnname(VmState* vmstate)
{
	sqlite3_stmt *conn = static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p);	
	return String_CreateString((char*)sqlite3_column_name(conn, GetParam(2, vmstate).d), vmstate);
}


StackState bindtext(VmState* vmstate)
{
	return Number_CreateNumber(sqlite3_bind_text(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p),GetParam(2,vmstate).d, GetParam(3,vmstate).str->string,-1,NULL));
}


StackState bindnumber(VmState* vmstate)
{
	return Number_CreateNumber(	sqlite3_bind_double(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p),GetParam(2,vmstate).d, GetParam(3,vmstate).d));
}

StackState bindnull(VmState* vmstate)
{
	return Number_CreateNumber(sqlite3_bind_null(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p),GetParam(2,vmstate).d));
}

StackState columncount(VmState* vmstate)
{
	return Number_CreateNumber(sqlite3_column_count(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p)));
}

StackState columntype(VmState* vmstate)
{
	return Number_CreateNumber(sqlite3_column_type(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p),GetParam(1,vmstate).d));
}

StackState finalize(VmState* vmstate)
{
	return Number_CreateNumber(sqlite3_finalize(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p)));
}

StackState Reset(VmState* vmstate)
{
	return Number_CreateNumber(sqlite3_reset(static_cast<sqlite3_stmt*>(GetParam(1,vmstate).p)));
}

StackState ExecuteNonQuery(VmState* vmstate)
{
	sqlite3 *conn = static_cast<sqlite3*>(GetParam(1, vmstate).p);
	sqlite3_exec(conn, GetParam(2, vmstate).str->string, 0, 0,0);
	return Null_CreateNull();
}


UserFunctionAtter List[] = {
	{"Connect",connect,1},
	{"Close",close,1},
	{"Execute",execute,1},
	{"Busytimeout",busytimeout,2},
	{"Changes",changes,1},
	{"Errcode",errcode,1},
	{"Errmsg",errmsg,1},
	{"Lastinsertrowid",lastinsertrowid,1},
	{"Version",version,0},
	{"Columnname",columnname,2},
	{"Bindtext",bindtext,3},
	{"Bindnumber",bindnumber,3},
	{"Bindnull",bindnull,3},
	{"Prepare",prepare,2},
	{"Columncount",columncount,1},
	{"Columntype",columntype,2},
	{"Finalize",finalize,1},
	{"Reset",Reset,1},
	{ "ExecuteNonQuery", ExecuteNonQuery, 2 },
	{NULL,NULL,0}
}; 


MentholModuleMethod void MP_Init(VmState* vmstate)
{
	RunTimeState* aesprt = CreateModuleRunTime("CSqlite", vmstate);
	RegisterModuleFunciton(aesprt,List);

}
