#include "stdafx.h"
#include "desx.h"
#include "modes.h"


namespace desx
{
	
	StackState DESEncryp(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		char* key = GetParam(2, vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_3<CryptoPP::DES>(message, key).c_str()), vmstate);
	}


	StackState DESDecryp(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		char* key = GetParam(2, vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_4<CryptoPP::DES>(message, key).c_str()), vmstate);
	}


};
