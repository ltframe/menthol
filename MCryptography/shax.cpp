#include "stdafx.h"
#include "shax.h"

namespace shax
{
	StackState SHA1(VmState* vmstate)
	{
		char* message = GetParam(1,vmstate).str->string;
		CryptoPP::SHA1 sha1;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::SHA1>(sha1,message).c_str()),vmstate);
	}

	StackState SHA224(VmState* vmstate)
	{
		char* message = GetParam(1,vmstate).str->string;
		CryptoPP::SHA224 sha224;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::SHA224>(sha224,message).c_str()),vmstate);
	}

	StackState SHA256(VmState* vmstate)
	{
		char* message = GetParam(1,vmstate).str->string;
		CryptoPP::SHA256 sha265;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::SHA256>(sha265,message).c_str()),vmstate);
	}

	StackState SHA384(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::SHA384 sha384;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::SHA384>(sha384,message).c_str()),vmstate);
	}

	StackState SHA512(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::SHA512 sha512;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::SHA512>(sha512,message).c_str()),vmstate);
	}

};