#pragma once
#include "header.h"
namespace SetOpt
{
	StackState m_easy_setopt_long(VmState* vmstate);
	StackState m_easy_setopt_string(VmState* vmstate);
	StackState m_easy_setopt_strings(VmState* vmstate);
	StackState m_easy_setopt_proxytype(VmState* vmstate);
	StackState m_easy_setopt_httpauth(VmState* vmstate);
};

