#include "StdAfx.h"
#include "MFile.h"
#include "windows.h"
MFile* MFile::_inst = 0;

MFile::MFile(void)
{
	if(!_inst){
	_inst =this;
	}
}

MFile* MFile::CreateInstance()
{
	return _inst;
}
MFile::~MFile(void)
{
		_inst=0;
}





string MFile::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}


void MFile::GenerateFileData(vector<Instruction>* codelist,vector<StringAtter>* stringlist,vector <FunctionAtter> * functionlist,vector <const char*> * importfiles,string extension,string name)
{	
	//PathInfo pinfo = MCommon::CreateInstance()->StringPathSplit(file);
	string fileext;
	if(MCommon::CreateInstance()->StrCmpNoCase(extension,MENTHOLEXTENSION)){
		fileext = MENTHOLEXECUTEEXTENSION;
	}
	if(MCommon::CreateInstance()->StrCmpNoCase(extension,MENTHOLPACKAGEEXTENSION)){
		fileext = MENTHOLPACKAGEDLLEXTENSION;
	}
	ofstream fileOut;
	fileOut.open((name+fileext).c_str(), std::ios::out | ofstream::binary);		
	string _t;
	int strlen = codelist->size();

	for (int i=0;i<strlen;i++)
	{
		CodeInst c;
		c.i = codelist->at(i);
		_t.push_back(c.m.c1);_t.push_back(c.m.c2);_t.push_back(c.m.c3);_t.push_back(c.m.c4);
	}	
	fileOut.write(_t.c_str(),_t.size());
	fileOut.close();

}


bool MFile::IsFileExist(string csFile)
{
	DWORD dwAttrib = GetFileAttributesA(csFile.c_str());
    return INVALID_FILE_ATTRIBUTES != dwAttrib && 0 == (dwAttrib & FILE_ATTRIBUTE_DIRECTORY);
}