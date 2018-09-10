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

}



void MFile::WReadImportFiles(const char* fp,stack<const char*> *filetree)
{
	std::ifstream t;  
	int length;  
	t.open(fp,std::ios::in | ofstream::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	char *bufferf = new char[length];    // allocate memory for a buffer of appropriate dimension  
	t.read(bufferf, length);       // read the whole file into the buffer  
	t.close();                    // close file handle  
	
	int i=0;

	while(i<length){
		char buffer[4];
		buffer[0] = bufferf[i++];
		buffer[1] = bufferf[i++];
		buffer[2] = bufferf[i++];
		buffer[3] = bufferf[i++];
		int t = *(int*)buffer;

		if(t==3){
				buffer[0] = bufferf[i++];
				buffer[1] = bufferf[i++];
				buffer[2] = bufferf[i++];
				buffer[3] = bufferf[i++];
				int _lenght=*(int*)buffer;

				char * str =new char[_lenght];
				for(int s=0;s<_lenght;s++)
				{
					str[s] =bufferf[i++];
				}

				filetree->push(str);
				delete [] bufferf;
				WReadImportFiles(str,filetree);
		}else
		{
			break;
		}
	}

}

string MFile::currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
    return buf;
}


void MFile::GenerateFileData(vector<Instruction>* codelist,vector<StringAtter>* stringlist,vector <FunctionAtter> * functionlist,vector <const char*> * importfiles,string file)
{	
	PathInfo pinfo = MCommon::CreateInstance()->StringPathSplit(file);
	string fileext;
	if(pinfo.extension==MENTHOLEXTENSION){
		fileext = MENTHOLEXECUTEEXTENSION;
	}
	if(pinfo.extension==MENTHOLPACKAGEEXTENSION){
		fileext = MENTHOLPACKAGEDLLEXTENSION;
	}
	ofstream fileOut;
	fileOut.open((pinfo.name+fileext).c_str(), std::ios::out | ofstream::binary);		
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