#include "StdAfx.h"
#include "MCommon.h"
#include <windows.h>
MCommon* MCommon::_inst = 0;
MCommon::MCommon(void)
{
	if(!_inst){
	_inst =this;
	}
}

MCommon::~MCommon(void)
{
	
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

unsigned int MCommon::ELFHash(string ss)
{
	char* str = const_cast<char*>(ss.c_str());
	size_t l=strlen(str);
	unsigned int h = l;  /* seed */
	size_t step = (l>>5)|1;  /* if string is too long, don't hash all its chars */
	for (; l>=step; l-=step)
		h = h ^ ((h<<5)+(h>>2)+(unsigned char)*(str++));
	return h;

}

string MCommon::GetRunPath()  
{  
    char szFilePath[MAX_PATH + 1]={0};  
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
    (strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串  
    string path = szFilePath;    
    return path;  
}  