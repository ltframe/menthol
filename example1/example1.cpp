// example1.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Menthol.h"
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include  <direct.h>  
#include <list>
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include <functional>
#include <math.h>
#include "libzplay.h"
#include "windows.h";
#include <stdio.h>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib,"Wininet.lib")
using namespace std; 


StackState test()
{
	StackState value =GetParam(1);
	StackState st;
	st.v = M_STRING;
	st = String_CreateString("this is a test string");
	return st;
}


StackState CallBack()
{
	StackState value1 =GetParam(1);
	CreateFunctionCall(1);
	StackState arr = Array_CreateArray();
	StackState v;
	v.v = M_NUMBER;
	v.d = 789456;
	Array_Push(arr.parray,v);
	PushArray(arr.parray);
	StackState ret = CallFunction(value1);
	return ret;
}

using namespace libZPlay;


StackState CreatePlay()
{
	ZPlay *player = CreateZPlay();
	StackState t;
	t.p = player;
	t.v = M_OBJECT;
	return t;
}

StackState OpenFile()
{
	StackState inst =GetParam(1);
	StackState file =GetParam(2);
	StackState func =GetParam(3);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	int result = player->OpenFile(file.str->string, sfAutodetect);
	StackState t;
	if(result == 0)
	{
		CreateFunctionCall(1);
		PushString(String_CreateString(player->GetError()).str);
		CallFunction(func);
	}
	t.b= result;
	t.v = M_BOOL;
	return t;
}



StackState Release()
{
	StackState inst =GetParam(1);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	player->Release();
	StackState st;
	st.v=M_NULL;
	return st;
}


StackState GetStreamInfo()
{
	StackState inst =GetParam(1);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	TStreamInfo info;
	player->GetStreamInfo(&info);		
	StackState st = Dict_CreateDict();
	StackState _d;
	_d.v =M_NUMBER;
	_d.d = info.Length.hms.hour;
	Dict_Push("Hour",st.pdict,_d);
	_d.d = info.Length.hms.minute;
	Dict_Push("Minute",st.pdict, _d);
	_d.d = info.Length.hms.second;
	Dict_Push("Second",st.pdict,_d);
	return st;
}


StackState Play()
{
	StackState inst =GetParam(1);
	StackState func =GetParam(2);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	player->Play();
	while(1)
	{
		// check key press
		TStreamStatus status;

		// get current position
		TStreamTime pos;
		player->GetPosition(&pos);
		// display position

		CreateFunctionCall(1);
		StackState st = Dict_CreateDict();
		StackState _d;
		_d.v =M_NUMBER;
		_d.d = pos.hms.hour;
		Dict_Push("Hour",st.pdict,_d);
		_d.d = pos.hms.minute;
		Dict_Push("Minute",st.pdict, _d);
		_d.d = pos.hms.second;
		Dict_Push("Second",st.pdict,_d);
		_d.d = pos.hms.millisecond;
		Dict_Push("Millisecond",st.pdict,_d);
		
		PushDict(st.pdict);

		player->GetStatus(&status);	

		PushNumber(status.fPlay);
		CallFunction(func);
		if(status.fPlay == 0){
			break;
		}
		
	}
	StackState st;
	st.v=M_NULL;
	return st;
}

StackState Play2()
{
	StackState inst =GetParam(1);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	player->Play();
	StackState st;
	st.v=M_NULL;
	return st;
}

StackState GetPosition()
{
	StackState inst =GetParam(1);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	TStreamTime pos;
	player->GetPosition(&pos);

	StackState st = Dict_CreateDict();
	StackState _d;
	_d.v =M_NUMBER;
	_d.d = pos.hms.hour;
	Dict_Push("Hour",st.pdict,_d);
	_d.d = pos.hms.minute;
	Dict_Push("Minute",st.pdict, _d);
	_d.d = pos.hms.second;
	Dict_Push("Second",st.pdict,_d);
	return st;
}


StackState GetStatus()
{
	StackState inst =GetParam(1);
	ZPlay *player = static_cast<ZPlay*>(inst.p);
	TStreamStatus status;
	player->GetStatus(&status);	
	StackState _d;
	_d.v =M_NUMBER;
	_d.d = status.fPlay;
	return _d;
}


StackState HttpGet()
{
	StackState ret;
	string v;
	char* szUrl = GetParam(1).str->string;
    char* szAgent= "";
    HINTERNET hInternet1 = 
        InternetOpen(NULL,INTERNET_OPEN_TYPE_PRECONFIG,NULL,NULL,NULL);
    if (NULL == hInternet1)
     {
        InternetCloseHandle(hInternet1);
		ret.v=M_NULL;
        return ret;
     }
    HINTERNET hInternet2 = 
        InternetOpenUrl(hInternet1,szUrl,NULL,NULL,INTERNET_FLAG_NO_CACHE_WRITE,NULL);
    if (NULL == hInternet2)
     {
        InternetCloseHandle(hInternet2);
        InternetCloseHandle(hInternet1);
        ret.v=M_NULL;
        return ret;
     }
    DWORD dwMaxDataLength = 500;
    PBYTE pBuf = (PBYTE)malloc(dwMaxDataLength*sizeof(TCHAR));
    if (NULL == pBuf)
     {
        InternetCloseHandle(hInternet2);
        InternetCloseHandle(hInternet1);
        ret.v=M_NULL;
        return ret;
     }
    DWORD dwReadDataLength = NULL;
    BOOL bRet = TRUE;
    do 
    {
        ZeroMemory(pBuf,dwMaxDataLength*sizeof(TCHAR));
        bRet = InternetReadFile(hInternet2,pBuf,dwMaxDataLength,&dwReadDataLength);
        for (DWORD dw = 0;dw < dwReadDataLength;dw++)
         {
            v.push_back(pBuf[dw]);
         }
     } while (NULL != dwReadDataLength);
	 InternetCloseHandle(hInternet2);
     InternetCloseHandle(hInternet1);
	 ret = String_CreateString(const_cast<char*>(v.c_str()));
	 free(pBuf);
	return ret;
}

StackState HideCursor()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);
	CursorInfo.bVisible = false; 
	SetConsoleCursorInfo(handle, &CursorInfo);
	StackState st;
	st.v=M_NULL;
	return st;
}
MentholPackMethod void example1_Init()
{
	RegisterPackAgeFunciton("HideCursor",HideCursor,0);	
	RegisterPackAgeFunciton("test",test,0);	
	RegisterPackAgeFunciton("CallBack",CallBack,1);	
	RegisterPackAgeFunciton("CreatePlay",CreatePlay,0);	
	RegisterPackAgeFunciton("OpenFile",OpenFile,2);	
	RegisterPackAgeFunciton("Release",Release,1);	
	RegisterPackAgeFunciton("GetStreamInfo",GetStreamInfo,1);	
	RegisterPackAgeFunciton("Play",Play,2);	
	RegisterPackAgeFunciton("Play2",Play2,1);	
	RegisterPackAgeFunciton("GetPosition",GetPosition,1);
	RegisterPackAgeFunciton("GetStatus",GetStatus,1);
	RegisterPackAgeFunciton("HttpGet",HttpGet,1);
}

