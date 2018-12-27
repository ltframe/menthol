#include "stdafx.h"
#include "Drives.h"

namespace Drives
{
	StackState GetDrives()
	{
		int iCounter = 0;
		int iASCIILetter = (int)'a';

		DWORD dwDrivesMask = GetLogicalDrives();

		if (dwDrivesMask == 0){
			return Null_CreateNull();
		} 
		StackState ar = Array_CreateArray();
		while (iCounter < 24){
			if (dwDrivesMask & (1 << iCounter)){
				char buf[64] = {0};
				sprintf_s(buf,sizeof(buf),"%c",iASCIILetter + iCounter);
				Array_Push(ar.parray,String_CreateString(buf));
			}
			iCounter++;
		}
		return ar;
	}
	StackState AvailableFreeSpace(){
		DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
		bool bResult = GetDiskFreeSpaceEx(GetParam(1).str->string, 
		(PULARGE_INTEGER)&qwFreeBytesToCaller, 
		(PULARGE_INTEGER)&qwTotalBytes, 
		(PULARGE_INTEGER)&qwFreeBytes);

		return Number_CreateNumber(qwFreeBytes);

	}
	StackState DriveType()
	{
		return Number_CreateNumber(GetDriveType(GetParam(1).str->string));
	}
	StackState TotalFreeSpace()
	{
		DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
		bool bResult = GetDiskFreeSpaceEx(GetParam(1).str->string,
		(PULARGE_INTEGER)&qwFreeBytesToCaller, 
		(PULARGE_INTEGER)&qwTotalBytes, 
		(PULARGE_INTEGER)&qwFreeBytes);

		return Number_CreateNumber(qwFreeBytesToCaller);
	}
	StackState TotalSize()
	{
		DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
		bool bResult = GetDiskFreeSpaceEx(GetParam(1).str->string, 
		(PULARGE_INTEGER)&qwFreeBytesToCaller, 
		(PULARGE_INTEGER)&qwTotalBytes, 
		(PULARGE_INTEGER)&qwFreeBytes);

		return Number_CreateNumber(qwTotalBytes);
	}
}
