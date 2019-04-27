#include "stdafx.h"
#include "Environment.h"
#include <windows.h>
#include <Objbase.h>
#include <process.h>
#include <time.h>
namespace Environment
{
	StackState Version(VmState* vmstate)
	{
		return String_CreateString("Menthol 1.2,2018/12/20,@2018 ltplayer.com",vmstate);

	}
	StackState Sleep(VmState* vmstate)
	{
		StackState inst =GetParam(1,vmstate);
		::Sleep(inst.d);
		return inst;
	}


	StackState SystemInfo(VmState* vmstate)
	{
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		StackState info = Dict_CreateDict(vmstate);
		Dict_Push("ActiveProcessorMas",info.pdict,Number_CreateNumber(systemInfo.dwActiveProcessorMask));
		Dict_Push("NumberOfPkrocessors",info.pdict,Number_CreateNumber(systemInfo.dwNumberOfProcessors));
		Dict_Push("PageSize",info.pdict,Number_CreateNumber(systemInfo.dwPageSize));
		Dict_Push("ProcessorLevel",info.pdict,Number_CreateNumber(systemInfo.wProcessorLevel));
		Dict_Push("ProcessorRevision",info.pdict,Number_CreateNumber(systemInfo.wProcessorRevision));
		return info;
	}

	StackState CpuInfo(VmState* vmstate)
	{
		int CPUInfo[4] = {-1};
		unsigned   nExIds, i =  0;
		char CPUBrandString[0x40];
		// Get the information associated with each extended ID.
		__cpuid(CPUInfo, 0x80000000);
		nExIds = CPUInfo[0];
		for (i=0x80000000; i<=nExIds; ++i)
		{
			__cpuid(CPUInfo, i);
			// Interpret CPU brand string
			if  (i == 0x80000002)
				memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
			else if  (i == 0x80000003)
				memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
			else if  (i == 0x80000004)
				memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
		}
		return String_CreateString(CPUBrandString,vmstate);
	}


	StackState SystemMemory(VmState* vmstate)
	{
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof (statex);
		GlobalMemoryStatusEx(&statex);
		return Number_CreateNumber((statex.ullTotalPhys/1024)/1024);
	}


	StackState OsInfo(VmState* vmstate)
	{
		// get os name according to version number
		OSVERSIONINFO osver = { sizeof(OSVERSIONINFO) };
		GetVersionEx(&osver);
		std::string os_name;
		if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 0)
			os_name = "Windows 2000";
		else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 1)
			os_name = "Windows XP";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 0)
			os_name = "Windows 2003";
		else if (osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2)
			os_name = "windows vista";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1)
			os_name = "windows 7";
		else if (osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2)
			os_name = "windows 10";
		return String_CreateString(const_cast<char*>(os_name.c_str()),vmstate);

	}







	StackState Getpid(VmState* vmstate)
	{
		return Number_CreateNumber(_getpid());
	}







	StackState Exit(VmState* vmstate)
	{
		exit(GetParam(1,vmstate).d);
		return Null_CreateNull();
	}

	StackState System(VmState* vmstate)
	{
		 StackState inst =GetParam(1,vmstate);
		 if(!system(inst.str->string))
		 {
			 return Number_CreateNumber(0);
		 }
		 return Number_CreateNumber(-1);
	}



	StackState MachineName(VmState* vmstate)
	{
		TCHAR  infoBuf[32767];
		memset(infoBuf,0,32767);
		if(GetComputerName(infoBuf,0)){
			return String_CreateString(infoBuf,vmstate);
		}
		return Null_CreateNull();
	}


	StackState UserName(VmState* vmstate)
	{
		TCHAR  infoBuf[32767];
		if(GetUserName(infoBuf,0)){
			return String_CreateString(infoBuf,vmstate);
		}
		return Null_CreateNull();
	}

	StackState TickCount(VmState* vmstate)
	{
		return   Number_CreateNumber(GetTickCount());
	}


	StackState NewGuid(VmState* vmstate)
	{
		GUID guid;
		CoCreateGuid(&guid);
		char buf[64] = {0};
		sprintf_s(buf,sizeof(buf),"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1],
			guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		return String_CreateString(buf,vmstate);
	}

};