#pragma once
#include "arc4.h"
#include "rc2.h"
#include "base64.h"
#include "base32.h"
#include "crpyt.h"

namespace rcx
{	
	StackState RC4Encryp(VmState* vmstate);
	StackState RC4Decryp(VmState* vmstate);
	StackState RC2Encryp(VmState* vmstate);
	StackState RC2Decryp(VmState* vmstate);
};