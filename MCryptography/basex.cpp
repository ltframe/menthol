#include "stdafx.h"
#include "basex.h"
namespace basex
{	
	StackState Base64Encoder(VmState* vmstate)
	{
		char* decoded = GetParam(1,vmstate).str->string;		
		return String_CreateString(const_cast<char*>(Template_2<CryptoPP::Base64Encoder>(decoded).c_str()), vmstate);
	}

	StackState Base64Decoder(VmState* vmstate)
	{
		char* decoded = GetParam(1,vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_2<CryptoPP::Base64Decoder>(decoded).c_str()), vmstate);
	}

	StackState Base32Encoder(VmState* vmstate)
	{
		char* decoded = GetParam(1,vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_2<CryptoPP::Base32Encoder>(decoded).c_str()), vmstate);
	}

	StackState Base32Decoder(VmState* vmstate)
	{
		char* decoded = GetParam(1,vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_2<CryptoPP::Base32Decoder>(decoded).c_str()), vmstate);
	}

};