#include "stdafx.h"
#include "Drives.h"

namespace Drives
{
	StackState GetDrives(VmState* vmstate)
	{
		int iCounter = 0;
		int iASCIILetter = (int)'a';

		DWORD dwDrivesMask = GetLogicalDrives();

		if (dwDrivesMask == 0){
			return Null_CreateNull();
		} 
		StackState ar = Array_CreateArray(vmstate);
		while (iCounter < 24){
			if (dwDrivesMask & (1 << iCounter)){
				char buf[64] = {0};
				sprintf_s(buf,sizeof(buf),"%c",iASCIILetter + iCounter);
				Array_Push(ar.parray,String_CreateString(buf,vmstate));
			}
			iCounter++;
		}
		return ar;
	}
	StackState AvailableFreeSpace(VmState* vmstate){
		DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
		bool bResult = GetDiskFreeSpaceEx(GetParam(1,vmstate).str->string, 
		(PULARGE_INTEGER)&qwFreeBytesToCaller, 
		(PULARGE_INTEGER)&qwTotalBytes, 
		(PULARGE_INTEGER)&qwFreeBytes);

		return Number_CreateNumber(qwFreeBytes);

	}
	StackState DriveType(VmState* vmstate)
	{
		return Number_CreateNumber(GetDriveType(GetParam(1,vmstate).str->string));
	}
	StackState TotalFreeSpace(VmState* vmstate)
	{
		DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
		bool bResult = GetDiskFreeSpaceEx(GetParam(1,vmstate).str->string,
		(PULARGE_INTEGER)&qwFreeBytesToCaller, 
		(PULARGE_INTEGER)&qwTotalBytes, 
		(PULARGE_INTEGER)&qwFreeBytes);

		return Number_CreateNumber(qwFreeBytesToCaller);
	}
	StackState TotalSize(VmState* vmstate)
	{
		DWORD64 qwFreeBytes, qwFreeBytesToCaller, qwTotalBytes;
		bool bResult = GetDiskFreeSpaceEx(GetParam(1,vmstate).str->string, 
		(PULARGE_INTEGER)&qwFreeBytesToCaller, 
		(PULARGE_INTEGER)&qwTotalBytes, 
		(PULARGE_INTEGER)&qwFreeBytes);

		return Number_CreateNumber(qwTotalBytes);
	}
}
