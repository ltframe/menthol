#include "stdafx.h"
#include "aesx.h"
#include "modes.h"

namespace aesx
{

	StackState AESEncryp(VmState* vmstate)
	{
		char* message = GetParam(1,vmstate).str->string;
		char* key = GetParam(2,vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_3<CryptoPP::AES>(message, key).c_str()), vmstate);
	}

	StackState AESDecryp(VmState* vmstate)
	{
		char* message = GetParam(1,vmstate).str->string;
		char* key = GetParam(2,vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_4<CryptoPP::AES>(message, key).c_str()), vmstate);
	}
};