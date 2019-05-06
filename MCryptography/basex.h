#pragma once
#include "../MCryptography/cryp/base64.h"
#include "../MCryptography/cryp/base32.h"
#include "crpyt.h"

namespace basex
{	
	StackState Base64Encoder(VmState* vmstate);
	StackState Base64Decoder(VmState* vmstate);
	StackState Base32Encoder(VmState* vmstate);
	StackState Base32Decoder(VmState* vmstate);
};