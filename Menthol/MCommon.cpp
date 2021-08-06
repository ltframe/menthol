#include "StdAfx.h"
#include "MCommon.h"
#include <algorithm>
#include <windows.h>
#include <Objbase.h>
//定义个实例的变量，在构造函数将其设置为this 以后使用CreateInstance。获取到当前类的实例
MCommon* MCommon::_inst = 0;
MCommon::MCommon(void)
{
	if(!_inst){
		_inst =this;
		char szFilePath[MAX_PATH + 1]={0};  
		GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
		(strrchr(szFilePath, '\\'))[0] = 0; 
		runpath = szFilePath;  

		SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);
		AddDllDirectory(AnsiToWideChar((runpath+"\\dll").c_str()));//把当前目录下的dll目录下的组件，作为默认加载的DLL路径.

		char szFilePath_coef[MAX_PATH];
		getcwd(szFilePath_coef, MAX_PATH);
		AddDllDirectory(AnsiToWideChar(szFilePath_coef));
	}
}

MCommon::~MCommon(void)
{
	_inst=0;
}

//char* 转为wchar_t*
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

//把完整路径拆分为驱动器、目录，文件名，扩展名
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

//生成字符串hash
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

//获取程序运行路径，在构造函数中赋值
string MCommon::GetRunPath()  
{    
    return runpath;  
}  

//不区分大小比较两个两个字符串，无论大小写，在程序内部转为小写
bool MCommon::StrCmpNoCase(string str1,string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(),::tolower);
	transform(str2.begin(), str2.end(), str2.begin(),::tolower);
	if(str1==str2)return true;
	else return false;
}

//查找枚举数组，是否包含一个制定的枚举，
bool MCommon::IsInArray(ValueType* _array,ValueType str,int c)
{
	//int t = sizeof(_array);
	for (int i = 0; i < c; i++)
	{
		if(_array[i]==str)
		{
			return true;
		}
	}
	return false;
}

//创建guid
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