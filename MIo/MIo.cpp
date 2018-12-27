// MIo.cpp : 定义 DLL 应用程序的导出函数。
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
#include "Directory.h"
#include "Console.h"
#include "File.h"
#include "Drives.h"
using namespace std;

UserFunctionAtter Directorylist[] = {
	{"Getcwd",Directory::Getcwd,0},
	{"Chdir",Directory::Chdir,1},
	{"Getenv",Directory::Getenv,1},
	{"Remove",Directory::Remove,1},
	{"Rmdir",Directory::Rmdir,1},
	{"Mkdir",Directory::Mkdir,1},
	{"Rename",Directory::Rename,2},
	{"Exists",Directory::Exists,1},
	{NULL,NULL,0}
}; 

UserFunctionAtter Consolelist[] = {
	{"Oute",Console::Oute,1},	
	{"Out",Console::Out,1},	
	{"In",Console::In,0},
	{"Clear",Console::Clear ,0},
	{NULL,NULL,0}
}; 

UserFunctionAtter Filelist[] = {
	{"Readfile",File::Readfile,1},	
	{"Writefile",File::Writefile,2},
	{"Copy",File::Copy,3},
	{"Create",File::Create,1},
	{"Delete",File::Delete,1},
	{"Exists",File::Exists,1},
	{"Move",File::Move,2},
	{"GetCreationTime",File::GetCreationTime,1},
	{"GetLastAccessTime",File::GetLastAccessTime,1},
	{"GetLastWriteTime",File::GetLastWriteTime,1},
	{NULL,NULL,0}
}; 

UserFunctionAtter Driveslist[] = {
	{"GetDrives",Drives::GetDrives,0},
	{"AvailableFreeSpace",Drives::AvailableFreeSpace,1},
	{"DriveType",Drives::DriveType,1},
	{"TotalFreeSpace",Drives::TotalFreeSpace,1},
	{"TotalSize",Drives::TotalSize,1},
	{NULL,NULL,0}
}; 
	

MentholModuleMethod void	MP_Init()
{
	RunTimeState* Directoryprt = CreateModuleRunTime("CDirectory");
	RegisterModuleFunciton(Directoryprt,Directorylist);

	RunTimeState* Consoleprt = CreateModuleRunTime("CConsole");
	RegisterModuleFunciton(Consoleprt,Consolelist);

	RunTimeState* Fileprt = CreateModuleRunTime("CFile");
	RegisterModuleFunciton(Fileprt,Filelist);

	RunTimeState* Drivesprt = CreateModuleRunTime("CDrives");
	RegisterModuleFunciton(Drivesprt,Driveslist);
}