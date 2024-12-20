#include "stdafx.h"
#include "File.h"
#include <Shlwapi.h>
namespace File
{

	StackState Open(VmState* vmstate)
	{
		char* filename =GetParam(1,vmstate).str->string;
		char* mod =GetParam(2,vmstate).str->string;
		FILE *pFile=fopen(filename,mod);
		StackState value;
		value.p = pFile;
		value.v = M_OBJECT;
		return value;
	}

	StackState Readfile(VmState* vmstate)
	{
		FILE* file =(FILE*)GetParam(1,vmstate).p;
		fseek(file,0,SEEK_END); 
		int len=ftell(file); 
		char *pBuf;
		pBuf=new char[len+1]; 
		rewind(file); 
		fread(pBuf,1,len,file); 
		pBuf[len]=0; 

		StackState str = String_CreateString(pBuf,vmstate);
		delete [] pBuf;
		return str;
	}

	StackState Close(VmState* vmstate)
	{
		FILE* file =(FILE*)GetParam(1,vmstate).p;
		fclose(file); 
		return Null_CreateNull();
	}


	StackState Writefile(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		ofstream OutFile(value1.str->string);
		OutFile << value2.str->string << endl;
		OutFile.close();
		StackState st;
		st.b=true;
		st.v = M_BOOL;
		return st;
	}

	StackState Copy(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		StackState value2 =GetParam(2,vmstate);
		CopyFile(value1.str->string,value2.str->string,value2.d);  
		return Null_CreateNull();
	}
	StackState Create(VmState* vmstate)
	{
		ofstream OutFile(GetParam(1,vmstate).str->string);
		OutFile.close();
		return Null_CreateNull();
	}

	StackState Delete(VmState* vmstate)
	{
		StackState value1 =GetParam(1,vmstate);
		DeleteFile(value1.str->string);  
		return Null_CreateNull();
	}
	StackState Exists(VmState* vmstate)
	{
		return Bool_CreateBool(PathFileExists(GetParam(1,vmstate).str->string));
	}

	StackState Move(VmState* vmstate)
	{
		MoveFile(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string);
		return Null_CreateNull();
	}
	
	static StackState castTime(SYSTEMTIME st,VmState* vmstate)
	{
		StackState info = Dict_CreateDict(vmstate);
		Dict_Push("Year",info.pdict,Number_CreateNumber(st.wYear));
		Dict_Push("Month",info.pdict,Number_CreateNumber(st.wMonth));
		Dict_Push("Day",info.pdict,Number_CreateNumber(st.wDay));
		Dict_Push("Hour",info.pdict,Number_CreateNumber(st.wHour));
		Dict_Push("Minute",info.pdict,Number_CreateNumber(st.wMinute));
		Dict_Push("Second",info.pdict,Number_CreateNumber(st.wSecond));
		return info;
	}

	StackState GetCreationTime(VmState* vmstate)
	{
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		if (!GetFileAttributesEx(GetParam(1,vmstate).str->string, GetFileExInfoStandard, &wfad))
		{
			return Null_CreateNull();
		}
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(&(wfad.ftCreationTime), &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);	
		return castTime(st,vmstate);
	}
	StackState GetLastAccessTime(VmState* vmstate)
	{
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		if (!GetFileAttributesEx(GetParam(1,vmstate).str->string, GetFileExInfoStandard, &wfad))
		{
			return Null_CreateNull();
		}
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(&(wfad.ftLastAccessTime), &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);	
		return castTime(st,vmstate);
	}

	StackState GetLastWriteTime(VmState* vmstate)
	{
		WIN32_FILE_ATTRIBUTE_DATA wfad;
		if (!GetFileAttributesEx(GetParam(1,vmstate).str->string, GetFileExInfoStandard, &wfad))
		{
			return Null_CreateNull();
		}
		FILETIME ftLocal;
		SYSTEMTIME st;
		FileTimeToLocalFileTime(&(wfad.ftLastWriteTime), &ftLocal);
		FileTimeToSystemTime(&ftLocal, &st);	
		return castTime(st,vmstate);
	}

	StackState IsFile(VmState* vmstate)
	{
		char szFilePath[MAX_PATH];
		WIN32_FIND_DATA findFileData;
		strcpy_s(szFilePath, GetParam(1,vmstate).str->string);
		strcat_s(szFilePath, "\\*.*");
		HANDLE hFind = ::FindFirstFile(szFilePath, &findFileData);
		if (INVALID_HANDLE_VALUE == hFind)
		{
			return Bool_CreateBool(false);
		}
		if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			return Bool_CreateBool(false);
		}
		return Bool_CreateBool(true);
	}	

	static void FileList(char lpPath[],StackState& arr,VmState* vmstate)
	{
		char szFileName[MAX_PATH];
		char szFilePath[MAX_PATH];
		WIN32_FIND_DATA findFileData;
		strcpy_s(szFilePath, lpPath);
		strcat_s(szFilePath, "\\*.*");
		HANDLE hFind = ::FindFirstFile(szFilePath, &findFileData);
		if (INVALID_HANDLE_VALUE == hFind)
		{
			return;
		}

		do
		{
			if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				Array_Push(arr.parray,String_CreateString(findFileData.cFileName,vmstate));
			}
		} while (FindNextFile(hFind, &findFileData));

		FindClose(hFind);
	}
	StackState GetFileList(VmState* vmstate)
	{
		StackState arr =Array_CreateArray(vmstate);
		//FileList("E:/BaiduYunDownload",arr,vmstate);
		return arr;
	}	

	StackState GetExtension(VmState* vmstate)
	{
		return StackState();
	}
}