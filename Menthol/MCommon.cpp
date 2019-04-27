#include "StdAfx.h"
#include "MCommon.h"
#include <algorithm>
#include <windows.h>
#include <Objbase.h>
MCommon* MCommon::_inst = 0;
MCommon::MCommon(void)
{
	if(!_inst){
		_inst =this;
		char szFilePath[MAX_PATH + 1]={0};  
		GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
		(strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串  
		runpath = szFilePath;  

		SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
		AddDllDirectory(AnsiToWideChar((runpath+"\\dll").c_str()));

		char szFilePath_coef[MAX_PATH];
		getcwd(szFilePath_coef, MAX_PATH);
		AddDllDirectory(AnsiToWideChar(szFilePath_coef));
	}
}

MCommon::~MCommon(void)
{
	_inst=0;
}


wchar_t * MCommon::AnsiToWideChar(const char* str)
{
	WCHAR *wstr =new WCHAR[MAX_PATH+1];
	int nSize = MultiByteToWideChar(CP_UTF8 ,0,str,-1,NULL,0);
	MultiByteToWideChar(CP_UTF8 ,0,str,-1,wstr,nSize);
	return wstr;
}

MCommon* MCommon::CreateInstance()
{
	return _inst;
}
PathInfo MCommon::StringPathSplit(string _path)
{
	char drive[_MAX_DRIVE];    
	char dir[_MAX_DIR];    
	char fname[_MAX_FNAME];    
	char ext[_MAX_EXT];
	_splitpath(_path.c_str(), drive, dir, fname,ext);  
	PathInfo info = {drive,dir,fname,ext,string(fname)+string(ext)};
	return info;
}

M_UInt MCommon::ELFHash(string ss)
{
	char* str = CONSTCAST(char)(ss.c_str());
	size_t l=strlen(str);
	M_UInt h = l;  /* seed */
	size_t step = (l>>5)|1;  /* if string is too long, don't hash all its chars */
	for (; l>=step; l-=step)
		h = h ^ ((h<<5)+(h>>2)+(unsigned char)*(str++));
	return h;

}

string MCommon::GetRunPath()  
{    
    return runpath;  
}  

bool MCommon::StrCmpNoCase(string str1,string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(),::tolower);
	transform(str2.begin(), str2.end(), str2.begin(),::tolower);
	if(str1==str2)return true;
	else return false;
}


string MCommon::CreateGuid()
{
	char buffer[64] = { 0 };  
    GUID guid;  
    
    if (CoCreateGuid(&guid))  
    {  
        return "";  
    }  
    _snprintf(buffer, sizeof(buffer),  
        "%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",  
        guid.Data1, guid.Data2, guid.Data3,  
        guid.Data4[0], guid.Data4[1], guid.Data4[2],  
        guid.Data4[3], guid.Data4[4], guid.Data4[5],  
        guid.Data4[6], guid.Data4[7]);  
    return buffer;  

}