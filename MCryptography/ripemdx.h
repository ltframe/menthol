#pragma once

#include "../MCryptography/cryp/ripemd.h"
#include "crpyt.h"

namespace ripemdx
{
	StackState RIPEMD_128(VmState* vmstate);
	StackState RIPEMD_160(VmState* vmstate);
	StackState RIPEMD_256(VmState* vmstate);
	StackState RIPEMD_320(VmState* vmstate);
};