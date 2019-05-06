#include "stdafx.h"
#include "rcx.h"
#include "../MCryptography/cryp/modes.h"

namespace rcx
{	


	StackState RC4Encryp(VmState* vmstate)
	{
		char* t = GetParam(1, vmstate).str->string;
		char* msg = new char[256];
		memset(msg,0,256);
		strcpy(msg,t);
		char* key = GetParam(2, vmstate).str->string;
		CryptoPP::Weak1::ARC4 arc4((CryptoPP::byte*)key, strlen(key));
		arc4.ProcessString((CryptoPP::byte*)msg, (CryptoPP::byte*)msg,strlen(key));

		string encoded;
		CryptoPP::StringSource(msg, true,
			new CryptoPP::Base64Encoder(
			new CryptoPP::StringSink(encoded)
		));
		StackState ret = String_CreateString(const_cast<char*>(encoded.c_str()), vmstate);
		delete [] msg;
		return ret;

	}

	StackState RC4Decryp(VmState* vmstate)
	{
		char* msg = GetParam(1, vmstate).str->string;
		char* key = GetParam(2, vmstate).str->string;

		string encoded;
		CryptoPP::StringSource(msg, true,
			new CryptoPP::Base64Decoder(
			new CryptoPP::StringSink(encoded)
		));

		CryptoPP::Weak1::ARC4 arc4((CryptoPP::byte*)key, strlen(key));
		arc4.ProcessString((CryptoPP::byte*)encoded.data(), (CryptoPP::byte*)encoded.data(), encoded.size());


		return String_CreateString(const_cast<char*>(encoded.c_str()), vmstate);
	}


	StackState RC2Encryp(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		char* key = GetParam(2, vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_3<CryptoPP::RC2>(message, key).c_str()), vmstate);
	}

	StackState RC2Decryp(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		char* key = GetParam(2, vmstate).str->string;
		return String_CreateString(const_cast<char*>(Template_4<CryptoPP::RC2>(message, key).c_str()), vmstate);
	}
};