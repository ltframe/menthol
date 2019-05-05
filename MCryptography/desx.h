#pragma once
#include "../MCryptography/cryp/des.h"
#include "../MCryptography/cryp/base64.h"
#include "../MCryptography/cryp/base32.h"
#include "crpyt.h"
namespace desx
{
	StackState DESEncryp(VmState* vmstate);
	StackState DESDecryp(VmState* vmstate);
};