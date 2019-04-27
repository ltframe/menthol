#pragma once
#include "des.h"
#include "base64.h"
#include "base32.h"
#include "crpyt.h"
namespace desx
{
	StackState DESEncryp(VmState* vmstate);
	StackState DESDecryp(VmState* vmstate);
};