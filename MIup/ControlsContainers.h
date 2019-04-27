#pragma once
#include "header.h"
namespace ControlsContainers
{
	StackState Fill(VmState* vmstate);
	StackState Space(VmState* vmstate);
	StackState Cbox(VmState* vmstate);
	StackState GridBox(VmState* vmstate);
	StackState MultiBox(VmState* vmstate);
	StackState Hbox(VmState* vmstate);
	StackState Vbox(VmState* vmstate);
	StackState Zbox(VmState* vmstate);
	StackState Radio(VmState* vmstate);
	StackState Normalizer(VmState* vmstate);
	StackState Frame(VmState* vmstate);
	StackState FlatFrame(VmState* vmstate);
	StackState Tabs(VmState* vmstate);
	StackState FlatTabs(VmState* vmstate);
	StackState BackgroundBox(VmState* vmstate);
	StackState ScrollBox(VmState* vmstate);
	StackState FlatScrollBox(VmState* vmstate);
	StackState DetachBox(VmState* vmstate);
	StackState Expander(VmState* vmstate);
	StackState Sbox(VmState* vmstate);
	StackState Split(VmState* vmstate);
};

