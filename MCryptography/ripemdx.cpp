#include "stdafx.h"
#include "ripemdx.h"
namespace ripemdx
{
	StackState RIPEMD_128(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::RIPEMD128 ripemd128;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::RIPEMD128>(ripemd128, message).c_str()),vmstate);
	}

	StackState RIPEMD_160(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::RIPEMD160 ripemd160;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::RIPEMD160>(ripemd160, message).c_str()),vmstate);
	}

	StackState RIPEMD_256(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::RIPEMD256 ripemd256;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::RIPEMD256>(ripemd256, message).c_str()),vmstate);
	}

	StackState RIPEMD_320(VmState* vmstate)
	{
		char* message = GetParam(1, vmstate).str->string;
		CryptoPP::RIPEMD320 ripemd320;
		return String_CreateString(const_cast<char*>(Template_1<CryptoPP::RIPEMD320>(ripemd320, message).c_str()),vmstate);
	}
};