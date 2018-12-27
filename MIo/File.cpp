#include "stdafx.h"
#include "File.h"
#include <Shlwapi.h>
namespace File
{
	StackState Readfile()
	{
	
		StackState value =GetParam(1);
		ifstream t(value.str->string);  
		string str((istreambuf_iterator<char>(t)),istreambuf_iterator<char>()); 
		StackState st=String_CreateString(const_cast<char*>(str.c_str()));
		return st;
	}


	StackState Writefile()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		ofstream OutFile(value1.str->string);
		OutFile << value2.str << endl;
		OutFile.close();
		StackState st;
		st.b=true;
		st.v = M_BOOL;
		return st;
	}

	StackState Copy()
	{
		StackState value1 =GetParam(1);
		StackState value2 =GetParam(2);
		StackState value3 =GetParam(2);
		CopyFile(value1.str->string,value2.str->string,value2.d);  
		return Null_CreateNull();
	}
	StackState Create()
	{
		ofstream OutFile(GetParam(1).str->string);
		OutFile.close();
		return Null_CreateNull();
	}

	StackState Delete()
	{
		StackState value1 =GetParam(1);
		DeleteFile(value1.str->string);  
		return Null_CreateNull();
	}
	StackState Exists()
	{
		return Bool_CreateBool(PathFileExists(GetParam(1).str->string));
	}

	StackState Move()
	{
		MoveFile(GetParam(1).str->string,GetParam(2).str->string);
		return Null_CreateNull();
	}
	
	static StackState castTime(SYSTEMTIME st)
	{
		StackState info = Dict_CreateDict();
		Dict_Push("Year",info.pdict,Number_CreateNumber(st.wYear));
		Dict_Push("Month",info.pdict,Number_CreateNumber(st.wMonth));
		Dict_Push("Day",info.pdict,Number_CreateNumber(st.wDay));
		Dict_Push("Hour",info.pdict,Number_CreateNumber(st.wHour));
		Dict_Push("Minute",info.pdict,Number_CreateNumber(st.wMinute));
		Dict_Push("Second",info.pdict,Number_CreateNumber(st.wSecond));
		return info;
	}

	StackState GetCreationTime()
	{
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		if (!GetFileAttributesEx(GetParam(1).str->string, GetFileExInfoStandard, &wfad))
		{
			return Null_CreateNull();
		}
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(&(wfad.ftCreationTime), &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);	
		return castTime(st);
	}
	StackState GetLastAccessTime()
	{
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		if (!GetFileAttributesEx(GetParam(1).str->string, GetFileExInfoStandard, &wfad))
		{
			return Null_CreateNull();
		}
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(&(wfad.ftLastAccessTime), &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);	
		return castTime(st);
	}

	StackState GetLastWriteTime()
	{
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		if (!GetFileAttributesEx(GetParam(1).str->string, GetFileExInfoStandard, &wfad))
		{
			return Null_CreateNull();
		}
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(&(wfad.ftLastWriteTime), &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);	
		return castTime(st);
	}
}