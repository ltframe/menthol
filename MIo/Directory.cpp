#include "Directory.h"
#include <Shlwapi.h>
namespace Directory
{
	StackState Getcwd(VmState* vmstate)
	{
		char* buffer;
		if((buffer = _getcwd( NULL, 0 )) == NULL )
			return Null_CreateNull();
		else
		{
			StackState st = String_CreateString(buffer,vmstate);
			free(buffer);
			return st;
		}
	}
	StackState Chdir(VmState* vmstate)
	{
		StackState inst =GetParam(1,vmstate);
		if(_chdir(inst.str->string))
		{
			return Number_CreateNumber(errno);     
		}
		return Null_CreateNull();
	}


	StackState Getenv(VmState* vmstate)
	{
		StackState inst =GetParam(1,vmstate);
		char *libvar;
		libvar = getenv(inst.str->string);   
		if( libvar != NULL ){
			return String_CreateString(libvar,vmstate);
		}
		return Null_CreateNull();
	}

	StackState Remove(VmState* vmstate)
	{
		 StackState inst =GetParam(1,vmstate);
		 if( remove(inst.str->string) == -1 )
		 {
			 return Number_CreateNumber(1);
		 }
		 return Number_CreateNumber(0);
	}


	StackState Rmdir(VmState* vmstate)
	{
		 StackState inst =GetParam(1,vmstate);
		 if(!_rmdir(inst.str->string))
		 {
			 return Number_CreateNumber(0);
		 }
		 return Number_CreateNumber(-1);
	}

	StackState Mkdir(VmState* vmstate)
	{
		 StackState inst =GetParam(1,vmstate);
		 if(!_mkdir(inst.str->string))
		 {
			 return Number_CreateNumber(0);
		 }
		 return Number_CreateNumber(-1);
	}

	StackState Rename(VmState* vmstate)
	{
		StackState oldF =GetParam(1,vmstate);
		StackState newF =GetParam(2,vmstate);
		int  result= rename(oldF.str->string, newF.str->string);
		 if( result != 0 )
			Number_CreateNumber(-1);
		 else
			return Number_CreateNumber(0);

	}
	StackState GetCreationTime(VmState* vmstate)
	{
		return Null_CreateNull();
	}

	StackState Exists(VmState* vmstate)
	{
		StackState inst =GetParam(1,vmstate);
		return Bool_CreateBool(PathIsDirectory(inst.str->string));
	}

	StackState IsDirectory(VmState* vmstate)
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
			return Bool_CreateBool(true);
		}
		return Bool_CreateBool(false);
	}


	static void DirectoryList(char lpPath[],StackState& arr,VmState* vmstate)
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
			if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				Array_Push(arr.parray,String_CreateString(findFileData.cFileName,vmstate));
			}
		} while (FindNextFile(hFind, &findFileData));

		FindClose(hFind);
	}
	StackState GetDirectoryList(VmState* vmstate)
	{
		StackState arr =Array_CreateArray(vmstate);
		DirectoryList("E:/BaiduYunDownload",arr,vmstate);
		return arr;
	}	

}