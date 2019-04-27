#pragma once

#include "aes.h"
#include "base64.h"
#include "base32.h"
#include "crpyt.h"

namespace aesx
{	
	StackState AESEncryp(VmState* vmstate);
	StackState AESDecryp(VmState* vmstate);
};