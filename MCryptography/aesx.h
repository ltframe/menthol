#pragma once

#include "../MCryptography/cryp/aes.h"
#include "../MCryptography/cryp/base64.h"
#include "../MCryptography/cryp/base32.h"
#include "crpyt.h"

namespace aesx
{	
	StackState AESEncryp(VmState* vmstate);
	StackState AESDecryp(VmState* vmstate);
};