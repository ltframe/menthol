#pragma once
#include "base64.h"
#include "base32.h"
#include "crpyt.h"

namespace basex
{	
	StackState Base64Encoder(VmState* vmstate);
	StackState Base64Decoder(VmState* vmstate);
	StackState Base32Encoder(VmState* vmstate);
	StackState Base32Decoder(VmState* vmstate);
};