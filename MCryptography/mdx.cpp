#include "stdafx.h"
#include "mdx.h"

namespace mdx
{
	
	StackState MD5(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::Weak1::MD5 md5;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::Weak1::MD5>(md5, message).c_str()), vmstate);
	}

	StackState MD5File(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::Weak1::MD5 md5;
		const size_t size = CryptoPP::Weak1::MD5::DIGESTSIZE * 2;
		unsigned char  buf[size] = { 0 };
		CryptoPP::StringSource(message, true, new CryptoPP::HashFilter(md5, new CryptoPP::HexEncoder(new CryptoPP::ArraySink(buf,size))));
		string strHash = string(reinterpret_cast<const char*>(buf), size);
		return String_CreateString(const_cast<char*>(strHash.c_str()), vmstate);
	}

	StackState MD2(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::Weak1::MD2 md5;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::Weak1::MD2>(md5, message).c_str()), vmstate);
	}

	StackState MD4(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::Weak1::MD4 md5;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::Weak1::MD4>(md5, message).c_str()), vmstate);
	}

};