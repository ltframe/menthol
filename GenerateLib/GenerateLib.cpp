// GenerateLib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#include "Menthol.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <Shlwapi.h>

#include <io.h>
#include <direct.h>
#include <errno.h>
#include <dbghelp.h>

 
inline void get_file_path(const char *path, const char *file_name, char *file_path)
{
    strcpy_s(file_path, sizeof(char) * _MAX_PATH, path);
    file_path[strlen(file_path) - 1] = '\0';
    strcat_s(file_path, sizeof(char) * _MAX_PATH, file_name);
    strcat_s(file_path, sizeof(char) * _MAX_PATH, "\\*");
}
 
int error(char* str,char* cf,int line)
{
	printf("\r\n");
	printf("compile error: %s, in %s,at line %d",str,cf,line);
	printf("\r\n");
	return 1;
}

string getdir(string _path)
{
	char drive[_MAX_DRIVE];    
	char dir[_MAX_DIR];    
	char fname[_MAX_FNAME];    
	char ext[_MAX_EXT];
	_splitpath_s(_path.c_str(), drive, dir, fname,ext);  
	return string(drive)+dir;
}

bool StrCmpNoCase(string str1,string str2)
{
	transform(str1.begin(), str1.end(), str1.begin(),::tolower);
	transform(str2.begin(), str2.end(), str2.begin(),::tolower);
	if(str1==str2)return true;
	else return false;
}

string GetRunPath()  
{  
    char szFilePath[MAX_PATH + 1]={0};  
    GetModuleFileNameA(NULL, szFilePath, MAX_PATH);  
    (strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串  
    string path = szFilePath;    
    return path;  
}  


static void TraverseFiles(const char *lpPath)
{
	ifstream input(lpPath, ios::in );
	string filedir = getdir(lpPath);
	string line;
	
	string runpath = GetRunPath();
	_chdir(runpath.c_str());

	while(std::getline(input, line))
    {
		int c;
		char* f = const_cast<char*>(line.c_str());
		char* p = const_cast<char*>(strrchr(f,'/'));

		char* cf = (char*)malloc(MAX_PATH);
		if(p)
		{
			char * name = p+1;
			*p = '\0';	

			string newpath = (string(runpath)+ "\\lib\\"+string(f) + "\\");
 
			replace(newpath.begin(),newpath.end(),'/','\\');
			MakeSureDirectoryPathExists(newpath.c_str());


			string gf = filedir+f+ "\\"+  name + ".mep";
			replace(gf.begin(),gf.end(),'/','\\');

			string dfile = (newpath+name+".med");

			DeleteFile(dfile.c_str());

			c = Compile(const_cast<char*>((gf).c_str()));
			MoveFile((runpath+"\\"+name+".med").c_str(),dfile.c_str());
			strcpy(cf,(gf).c_str());
		}else
		{
			string dpath = string(runpath) + "\\lib\\";
			string dfile =dpath +line+".med";
			DeleteFile(dfile.c_str());
			string filename = filedir+line+".mep";
			c = Compile(const_cast<char*>(filename.c_str()));
			MoveFile((runpath+"\\"+line+".med").c_str(),dfile.c_str());
			strcpy(cf,(filename).c_str());
		}
		
		if(!c){
			printf("%s,compile done\r\n",cf);
		}
		else{
			printf("%s,compile error\r\n",cf);
		}
		free(cf);
		_chdir(runpath.c_str());

	}
	input.close();
}

int _tmain(int argc, _TCHAR* argv[])
{

	SetPrintCompileErrorFunc(error);	
	char _currentdir[260]={0};   
	_getcwd(_currentdir,sizeof(_currentdir));  
	TraverseFiles((string(_currentdir)+"\\generatefile.txt").c_str());
	return 0;
}

