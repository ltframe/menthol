// MSystem.cpp : 定义 DLL 应用程序的导出函数。
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
using namespace std;


StackState Version()
{
	return String_CreateString("Water 1.0.0,2018/3/14,@2017 ltplayer.com");

}
StackState Sleep()
{
	StackState inst =GetParam(1);
	Sleep(inst.d);
	return inst;
}

MentholPackMethod void MSystem_Init()
{
	RegisterPackAgeFunciton("Version",Version,0);	
	RegisterPackAgeFunciton("Sleep",Sleep,0);	
}