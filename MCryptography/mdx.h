#pragma once

#include "../MCryptography/cryp/md5.h"
#include "../MCryptography/cryp/md2.h"
#include "../MCryptography/cryp/md4.h"
#include "crpyt.h"
namespace mdx
{
	StackState MD5(VmState* vmstate);
	StackState MD2(VmState* vmstate);
	StackState MD4(VmState* vmstate);
	StackState MD5File(VmState* vmstate);
};