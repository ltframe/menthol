#pragma once

#include "sha.h"
#include "crpyt.h"

namespace shax
{	
	StackState SHA1(VmState* vmstate);
	StackState SHA224(VmState* vmstate);
	StackState SHA256(VmState* vmstate);
	StackState SHA384(VmState* vmstate);
	StackState SHA512(VmState* vmstate);
};