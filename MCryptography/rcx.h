#pragma once
#include "../MCryptography/cryp/arc4.h"
#include "../MCryptography/cryp/rc2.h"
#include "../MCryptography/cryp/base64.h"
#include "../MCryptography/cryp/base32.h"
#include "crpyt.h"

namespace rcx
{	
	StackState RC4Encryp(VmState* vmstate);
	StackState RC4Decryp(VmState* vmstate);
	StackState RC2Encryp(VmState* vmstate);
	StackState RC2Decryp(VmState* vmstate);
};