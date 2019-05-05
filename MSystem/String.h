#pragma once
#include "../Menthol/MentholHeader.h"
namespace String
{
	StackState StoN(VmState* vmstate);
	StackState IndexOf(VmState* vmstate);
	std::string replace(const std::string& inStr, const char* pSrc, const char* pReplace );
	StackState Replace(VmState* vmstate);
	StackState Toupper(VmState* vmstate);
	StackState Tolower(VmState* vmstate);
	StackState Length(VmState* vmstate);
	StackState Isdigit(VmState* vmstate);
	StackState Isalpha(VmState* vmstate);
	StackState Toascii(VmState* vmstate);
	StackState UTF8ToGBK(VmState* vmstate);
	StackState GBKToUTF8(VmState* vmstate);
}