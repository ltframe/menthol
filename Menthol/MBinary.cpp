#include "stdafx.h"
#include "MBinary.h"
#include "MCommon.h"
#include <Windows.h>

MBinary::MBinary(void)
{
}
MBinary::~MBinary(void)
{
}

bool MBinary::IsInInclude(vector<PackageState*>* packagelist,hashValue hash)
{
	VECTORFORSTART(PackageState*,packagelist,it)
		if((*it)->hash==hash){
			return true;
		}
	VECTORFOREND
		return false;
}

void MBinary::ReadBinary(string filename,vector <FunctionAtter>* functionlist,vector<string>* stringconstants,vector<Instruction> *codelist,
						 vector<Instruction> &globalcodelist,vector<double>* doubleconstants,vector<PackageState*>* packagelist,vector<RunTimeState*> *vrts,vector<StringValue>* dictkeyconstants){	


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
	int importentry = ReadCode(bufferf,i);;	
	int globalentry =  ReadCode(bufferf,i);
	int functionentry = ReadCode(bufferf,i);
	int stringentry = ReadCode(bufferf,i);
	int doubleentry = ReadCode(bufferf,i);
	int dictkeyentry = ReadCode(bufferf,i);

	{
		i = importentry*4;	
		int allimportfileslength =  ReadCode(bufferf,i);
		int loopid = i;
		int c = i+allimportfileslength*4-4;
		while(loopid<c){
	
			char buffer2[4];
			int ptype = ReadCode(bufferf,loopid);
			int packagestringlength = ReadCode(bufferf,loopid);
			string packagestr;
			for(int s=0;s<packagestringlength;s++)
			{
				packagestr.push_back(ReadCode(bufferf,loopid));
			}

			PackageState* ps =new PackageState();
			//ps->pname = packagestr;
			ps->hash = MCommon::CreateInstance()->ELFHash(packagestr);

			VECTORFORSTART(RunTimeState*,vrts,it)
				if((*it)->hash==ps->hash){
					ps->rts =(*it);
					break;
				}
			VECTORFOREND
			
			if(!IsInInclude(packagelist,ps->hash)){
				packagelist->push_back(ps);
			}
		
			int fnamestringlength = ReadCode(bufferf,loopid);
			for(int s=0;s<fnamestringlength;s++)
			{
				ReadCode(bufferf,loopid);
			}
		}
	}
	{
		i = globalentry*4;
		int allgloballength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allgloballength*4-4;
		while(loopid<c){
			int codelenght = ReadCode(bufferf,loopid);
			for(int si = 0;si<codelenght;si++){
				globalcodelist.push_back(ReadCode(bufferf,loopid));					
			}
		}
	}
	{
		i = functionentry*4;
		int allfunctionlength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allfunctionlength*4-4;
		while(loopid<c){
	
		
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
			}			FunctionAtter fa = {str,0,hash,paramcount,codelenght};
			functionlist->push_back(fa);

		}
	
	}
	{
		i = stringentry*4;
		int allstringlength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+allstringlength*4-4;
		while(loopid<c){
	
			
			int stringlength =ReadCode(bufferf,loopid);
			string str;
			for(int si = 0;si<stringlength;si++){
				str.push_back(ReadCode(bufferf,loopid));
			}
			stringconstants->push_back(str);

		}
	}
	{
		i = doubleentry*4;
		int alldoublelength =  ReadCode(bufferf,i);
   		int loopid = i;
		int c = i+alldoublelength*4-4;
		while(loopid<c){
			CodeDouble cd;
			cd.m.c1 =  bufferf[loopid++];
			cd.m.c2 =  bufferf[loopid++];
			cd.m.c3 =  bufferf[loopid++];
			cd.m.c4 =  bufferf[loopid++];
			cd.m.c5 =  bufferf[loopid++];
			cd.m.c6 =  bufferf[loopid++];
			cd.m.c7 =  bufferf[loopid++];
			cd.m.c8 =  bufferf[loopid++];
			
			doubleconstants->push_back(cd.d);

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

void MBinary::MReadImportFiles(const char* fp,vector<PackageAttr> *filetree,char* modidr,char* workdir)
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
	int importentry = ReadCode(bufferf,i);
	i = importentry*4;
	
	int allimportfileslength =  ReadCode(bufferf,i);
   	int loopid = i;
	int c = i+allimportfileslength*4-4;
	while(loopid<c){
	
		char buffer2[4];
		int ptype = ReadCode(bufferf,loopid);
		int packagestringlength = ReadCode(bufferf,loopid);
		char * packagestr =new char[packagestringlength+1];
		for(int s=0;s<packagestringlength;s++)
		{
			packagestr[s] = ReadCode(bufferf,loopid);
		}

		packagestr[packagestringlength]=0;



		
		int fnamestringlength = ReadCode(bufferf,loopid);
		char * fnamestr =new char[fnamestringlength+1];
		for(int s=0;s<fnamestringlength;s++)
		{
			fnamestr[s] =  ReadCode(bufferf,loopid);
		}

		fnamestr[fnamestringlength]=0;


		char * _filenamestr = new char[_MAX_PATH];
		memset(_filenamestr,0,_MAX_PATH);
		

		if(ptype==MPA_SDLL || ptype==MPA_SPACKAGE)
		{		
			strcat(_filenamestr,modidr);
			strcat(_filenamestr,"\\lib\\");
			strcat(_filenamestr,fnamestr);
		}
		if( ptype==MPA_PACKAGE ||ptype==MPA_DLL)
		{		
			strcat(_filenamestr,workdir);
			strcat(_filenamestr,fnamestr);
		}


		


		
		if(ptype==MPA_SDLL ||ptype==MPA_DLL)
		{

			PackageAttr pa;
			strcpy(pa.fname,_filenamestr);
			strcpy(pa.pname,packagestr);
			pa.ptype = (PackAgeType)ptype;

				filetree->push_back(pa);

		}
		if(ptype==MPA_PACKAGE||ptype==MPA_SPACKAGE){	
			PackageAttr pa;
			strcpy(pa.fname,_filenamestr);
			strcpy(pa.pname,packagestr);
			pa.ptype = (PackAgeType)ptype;

			
				filetree->push_back(pa);

			MReadImportFiles(_filenamestr,filetree,modidr,workdir);
		}
		delete [] _filenamestr;
		delete [] packagestr;
	}

	delete [] bufferf;
}

void MBinary::ReadCode(string filename){
	
}