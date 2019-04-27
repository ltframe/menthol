#pragma once

#include "md5.h"
#include "md2.h"
#include "md4.h"
#include "crpyt.h"
namespace mdx
{
	StackState MD5(VmState* vmstate);
	StackState MD2(VmState* vmstate);
	StackState MD4(VmState* vmstate);
	StackState MD5File(VmState* vmstate);
};