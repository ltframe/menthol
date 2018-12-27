#include "stdafx.h"
#include "MBinary.h"
#include "MCommon.h"
#include <Windows.h>
#include <algorithm>

MBinary* MBinary::_inst = 0;
MBinary::MBinary(void)
{
	if(!_inst){
		_inst =this;
	}
}
MBinary::~MBinary(void)
{
	_inst = 0;
}



MBinary* MBinary::CreateInstance()
{
	return _inst;
}

void MBinary::ReadBinary(ImportFileAttr fileattr, vector<Instruction> *codelist,
	vector<RunTimeState*> *vrts, vector<StringValue>* dictkeyconstants, void(*_AddRunTimeStateList)(RunTimeState*)
	,vector<GlobalCodeRuntimeAtter>* globallist){


	std::ifstream t;  
	int length;  
	t.open(fileattr.filename.c_str(),std::ios::in | ofstream::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	char *bufferf = new char[length];    // allocate memory for a buffer of appropriate dimension  
	t.read(bufferf, length);       // read the whole file into the buffer  
	t.close();                    // close file handle  
	int i=0;

	for(int mm=0;mm<3;mm++){ //跳过文件类型
		ReadCode(bufferf,i);
	}




	//Vm::

	int importentry = ReadCode(bufferf,i);;	

	int packageentry = ReadCode(bufferf,i);;	

	int includepackageentry = ReadCode(bufferf,i);;

	int globalentry =  ReadCode(bufferf,i);
	int functionentry = ReadCode(bufferf,i);
	int stringentry = ReadCode(bufferf,i);
	int doubleentry = ReadCode(bufferf,i);
	int dictkeyentry = ReadCode(bufferf,i);
	int debugentry = ReadCode(bufferf,i);

	vector<RunTimeState*> *_tempruntimestate =new vector<RunTimeState*>(); 
	{
		i = packageentry*4;	
		int allpackageentrylength =  ReadCode(bufferf,i);
		int loopid = i;
		int c = i+allpackageentrylength*4-4;
loopstart:	
		while(loopid<c){

			char buffer2[4];

			hashValue hash = ReadCode(bufferf,loopid);
			int packagestringlength = ReadCode(bufferf,loopid);
			string packagestr;
			for(int s=0;s<packagestringlength;s++)
			{
				packagestr.push_back(ReadCode(bufferf,loopid));
			}

			VECTORFORSTART(RunTimeState*,vrts,it)
				if((*it)->hash==hash){
					goto loopstart;
					break;
				}
			VECTORFOREND
			

			RunTimeState *currentruntimestate = new RunTimeState();
			currentruntimestate->hash = hash;
			currentruntimestate->modulename = packagestr;
			currentruntimestate->ptype = fileattr.ptype;

			currentruntimestate->doubles = new vector<double>();
			currentruntimestate->functionlist = new vector <FunctionAtter>();
			currentruntimestate->strings = new vector<string>();
			currentruntimestate->includemodule = new vector<ModuleState*>();
			currentruntimestate->globalvalues = new VECOTRSTACKSTATE();
			currentruntimestate->debuglist = new vector<MentholDebug>();
			_AddRunTimeStateList(currentruntimestate);
			_tempruntimestate->push_back(currentruntimestate);
		}
	}
	{

		i = includepackageentry*4;	
		int allincludepackageentrylength =  ReadCode(bufferf,i);
		int loopid = i;
		int c = i+allincludepackageentrylength*4-4;
		while(loopid<c){
			char buffer2[4];

			hashValue hash = ReadCode(bufferf,loopid);
			int packagestringlength = ReadCode(bufferf,loopid);
			string packagestr;
			for(int s=0;s<packagestringlength;s++)
			{
				packagestr.push_back(ReadCode(bufferf,loopid));
			}

			VECTORFORSTART(RunTimeState*,vrts,it)
				if((*it)->hash==hash){
						ModuleState* ps =new ModuleState();
						ps->hash = hash;
						ps->rts = (*it);
						VECTORFORSTART(RunTimeState*,_tempruntimestate,it1)
							(*it1)->includemodule->push_back(ps);
						VECTORFOREND
					break;
				}
			VECTORFOREND
		}
	}
	delete _tempruntimestate;

	{
		i = stringentry*4;
		int allstringlength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allstringlength*4-4;
		while(loopid<c){
	
			hashValue packagenamehash = ReadCode(bufferf, loopid);
			VECTORFORSTART(RunTimeState*,vrts,it)
				if((*it)->hash==packagenamehash){
						int stringlength =ReadCode(bufferf,loopid);
						string str;
						for(int si = 0;si<stringlength;si++){
							str.push_back(ReadCode(bufferf,loopid));
						}
						(*it)->strings->push_back(str);
				}
			VECTORFOREND
		}
	}

	{
		i = doubleentry*4;
		int alldoublelength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+alldoublelength*4-4;
		while(loopid<c){
			hashValue packagenamehash = ReadCode(bufferf, loopid);
			VECTORFORSTART(RunTimeState*,vrts,it)
				if((*it)->hash==packagenamehash){
					CodeDouble cd;
					cd.m.c1 =  bufferf[loopid++];
					cd.m.c2 =  bufferf[loopid++];
					cd.m.c3 =  bufferf[loopid++];
					cd.m.c4 =  bufferf[loopid++];
					cd.m.c5 =  bufferf[loopid++];
					cd.m.c6 =  bufferf[loopid++];
					cd.m.c7 =  bufferf[loopid++];
					cd.m.c8 =  bufferf[loopid++];
			
					(*it)->doubles->push_back(cd.d);
				}
			VECTORFOREND
		}
	}

	{
		i = globalentry*4;
		int allgloballength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allgloballength*4-4;
		while(loopid<c){
				vector<Instruction> *globalcodelist =new vector<Instruction>();
				hashValue packagenamehash = ReadCode(bufferf, loopid);
				VECTORFORSTART(RunTimeState*,vrts,it)
					if((*it)->hash==packagenamehash){
						int codelenght = ReadCode(bufferf, loopid);
						for (int si = 0; si<codelenght; si++)
						{
							globalcodelist->push_back(ReadCode(bufferf, loopid));
						}
						GlobalCodeRuntimeAtter gcra = { globalcodelist, (*it), codelenght };
						globallist->push_back(gcra);
						break;
					}
				VECTORFOREND
		}
	}
	{
		i = functionentry*4;
		int allfunctionlength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allfunctionlength*4-4;
		while(loopid<c){
	
			hashValue packagenamehash = ReadCode(bufferf, loopid);
			VECTORFORSTART(RunTimeState*,vrts,it)
			if((*it)->hash==packagenamehash){
						int stringlength = ReadCode(bufferf,loopid);
						string str;//函数名称
						for(int si = 0;si<stringlength;si++){
							str.push_back(ReadCode(bufferf,loopid));
						}
						int postion = ReadCode(bufferf,loopid); //函数位置
						int hash = ReadCode(bufferf,loopid);;
						int paramcount = ReadCode(bufferf,loopid);


						int codelenght = ReadCode(bufferf,loopid);

						for(int si = 0;si<codelenght;si++){
							codelist->push_back(ReadCode(bufferf,loopid));
						}

						vector <int> *defaultvaluelenghtlist =new vector <int>();
						defaultvaluelenghtlist->push_back(0);
						for (int i = 0; i < paramcount; i++)
						{
							defaultvaluelenghtlist->push_back(ReadCode(bufferf,loopid));
						}
						FunctionAtter fa = {str,0,hash,paramcount,codelenght,defaultvaluelenghtlist};
						(*it)->functionlist->push_back(fa);
			}
			VECTORFOREND
		}	
	}

	

	{
		i = dictkeyentry*4;
		int allstringlength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allstringlength*4-4;
		while(loopid<c){
	

						int stringlength =ReadCode(bufferf,loopid);
						string str;
						for(int si = 0;si<stringlength;si++){
							str.push_back(ReadCode(bufferf,loopid));
						}

						bool a = false;

						VECTORFORSTART(StringValue,dictkeyconstants,it)
							if((*it).hash==MCommon::CreateInstance()->ELFHash(str)){
								a = true;
								break;
							}
						VECTORFOREND
						int hash = ReadCode(bufferf,loopid);;
						if(!a){
				
							StringValue sv = {str,hash};
							dictkeyconstants->push_back(sv);
						}		
	
		}
	}
	{
		i = debugentry*4;
		int allstringlength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allstringlength*4-4;
		while(loopid<c){		
			hashValue packagenamehash = ReadCode(bufferf, loopid);
			VECTORFORSTART(RunTimeState*,vrts,it)
				if((*it)->hash==packagenamehash){
					int instno =ReadCode(bufferf,loopid);
					int lineno =ReadCode(bufferf,loopid);
					int filenamelenght = ReadCode(bufferf,loopid);
					string str;
					for(int si = 0;si<filenamelenght;si++){
						str.push_back(ReadCode(bufferf,loopid));
					}
					MentholDebug debuginfo = {instno,lineno,filenamelenght,str};
					(*it)->debuglist->push_back(debuginfo);
				}
			VECTORFOREND
		}
	}
	delete [] bufferf;
	
}

Instruction MBinary::ReadCode(char* bufferf,int& i)
{
	CodeInst ci;
	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	return ci.i;
}

void MBinary::MReadImportFiles(const char* fp,vector<ImportFileAttr> *filetree,char* modidr,char* workdir)
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
	//WBhead* head =new WBhead();

	for(int mm=0;mm<3;mm++){ //跳过文件类型
		ReadCode(bufferf,i);
	}

	int importentry = ReadCode(bufferf,i);
	i = importentry*4;
	
	int allimportfileslength =  ReadCode(bufferf,i);
   	int loopid = i;
	int c = i+allimportfileslength*4-4;
	while(loopid<c){
	
		char buffer2[4];
		int ptype = ReadCode(bufferf,loopid);
		int fnamestringlength = ReadCode(bufferf,loopid);
		char * fnamestr =new char[fnamestringlength+1];
		for(int s=0;s<fnamestringlength;s++)
		{
			fnamestr[s] =  ReadCode(bufferf,loopid);
		}

		fnamestr[fnamestringlength]=0;


		char * _filenamestr = new char[_MAX_PATH];
		memset(_filenamestr,0,_MAX_PATH);
		


		if(IsSYSPackage(ptype))
		{		
			strcat(_filenamestr,modidr);
			strcat(_filenamestr,"\\lib\\");
			strcat(_filenamestr,fnamestr);
		}else{
			strcat(_filenamestr,workdir);
			strcat(_filenamestr,fnamestr);
		}
		for (std::vector<ImportFileAttr>::iterator it = filetree->begin() ; it != filetree->end();)
		{		
			string _str = _filenamestr;
			transform((*it).filename.begin(), (*it).filename.end(), (*it).filename.begin(),::tolower);
			transform(_str.begin(), _str.end(), _str.begin(),::tolower);
			if((*it).filename==_str)
			{
				it = filetree->erase(it);
				break;
			}
			++it;
		}


		
		if(IsEXTPackage(ptype))
		{
			ImportFileAttr ifa = {_filenamestr,(PackAgeType)ptype};
			filetree->push_back(ifa);
		}
		if(IsPackage(ptype)){	
			ImportFileAttr ifa = {_filenamestr,(PackAgeType)ptype};
			filetree->push_back(ifa);
			MReadImportFiles(_filenamestr,filetree,modidr,workdir);
		}
		delete [] _filenamestr;
	}

	delete [] bufferf;
}

void MBinary::ReadCode(string filename){
	
}

void MBinary::ReadMEPPackage(string filename,vector<string>* list)
{
	std::ifstream t;  
	int length;  
	t.open(filename.c_str(),std::ios::in | ofstream::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	char *bufferf = new char[length];    // allocate memory for a buffer of appropriate dimension  
	t.read(bufferf, length);       // read the whole file into the buffer  
	t.close();                    // close file handle  
	int i=0;

	for(int mm=0;mm<3;mm++){ //跳过文件类型
		ReadCode(bufferf,i);
	}

	int importentry = ReadCode(bufferf,i);;	

	int packageentry = ReadCode(bufferf,i);;	

	{
		i = packageentry*4;	
		int allpackageentrylength =  ReadCode(bufferf,i);
		int loopid = i;
		int c = i+allpackageentrylength*4-4;
		while(loopid<c){
			char buffer2[4];

			hashValue hash = ReadCode(bufferf,loopid);
			int packagestringlength = ReadCode(bufferf,loopid);
			string packagestr;
			for(int s=0;s<packagestringlength;s++)
			{
				packagestr.push_back(ReadCode(bufferf,loopid));
			}
			list->push_back(packagestr);
		}
	}
	delete [] bufferf;
}


string MBinary::ReadPackageFormat(string filename)
{
	std::ifstream t;  
	int length;  
	t.open(filename,std::ios::in | ofstream::binary);      // open input file  
	t.seekg(0, std::ios::end);    // go to the end  
	length = t.tellg();           // report location (this is the length)  
	t.seekg(0, std::ios::beg);    // go back to the beginning  
	char *bufferf = new char[length];    // allocate memory for a buffer of appropriate dimension  
	t.read(bufferf, length);       // read the whole file into the buffer  
	t.close();                    // close file handle  

	string flag;
	int i=0;

	CodeInst ci;
	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	flag.push_back(ci.i);

	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	flag.push_back(ci.i);

	ci.m.c1 = bufferf[i++];
	ci.m.c2 = bufferf[i++];
	ci.m.c3 = bufferf[i++];
	ci.m.c4 = bufferf[i++];
	flag.push_back(ci.i);

	delete[] bufferf;

	return flag;
}
