#include "Directory.h"
#include <Shlwapi.h>
namespace Directory
{
	StackState Getcwd()
	{
		char* buffer;
		if((buffer = _getcwd( NULL, 0 )) == NULL )
			return Null_CreateNull();
		else
		{
			StackState st = String_CreateString(buffer);
			free(buffer);
			return st;
		}
	}
	StackState Chdir()
	{
		StackState inst =GetParam(1);
		if(_chdir(inst.str->string))
		{
			return Number_CreateNumber(errno);     
		}
		return Null_CreateNull();
	}


	StackState Getenv()
	{
		StackState inst =GetParam(1);
		char *libvar;
		libvar = getenv(inst.str->string);   
		if( libvar != NULL ){
			return String_CreateString(libvar);
		}
		return Null_CreateNull();
	}

	StackState Remove()
	{
		 StackState inst =GetParam(1);
		 if( remove(inst.str->string) == -1 )
		 {
			 return Number_CreateNumber(1);
		 }
		 return Number_CreateNumber(0);
	}


	StackState Rmdir()
	{
		 StackState inst =GetParam(1);
		 if(!_rmdir(inst.str->string))
		 {
			 return Number_CreateNumber(0);
		 }
		 return Number_CreateNumber(-1);
	}

	StackState Mkdir()
	{
		 StackState inst =GetParam(1);
		 if(!_mkdir(inst.str->string))
		 {
			 return Number_CreateNumber(0);
		 }
		 return Number_CreateNumber(-1);
	}

	StackState Rename()
	{
		StackState oldF =GetParam(1);
		StackState newF =GetParam(2);
		int  result= rename(oldF.str->string, newF.str->string);
		 if( result != 0 )
			Number_CreateNumber(-1);
		 else
			return Number_CreateNumber(0);

	}
	StackState GetCreationTime()
	{
		return Null_CreateNull();
	}

	StackState Exists()
	{
		StackState inst =GetParam(1);
		return Bool_CreateBool(PathIsDirectory(inst.str->string));
	}
}