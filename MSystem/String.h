#pragma once
#include "Menthol.h"
namespace String
{
	StackState StoN();
	StackState IndexOf();
	std::string replace(const std::string& inStr, const char* pSrc, const char* pReplace );
	StackState Replace();
	StackState Toupper();
	StackState Tolower();
	StackState Length();
	StackState Isdigit();
	StackState Isalpha();
	StackState Toascii();
}