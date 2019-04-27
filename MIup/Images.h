#pragma once
#include "header.h"
namespace Images
{
	StackState Image(VmState* vmstate);
	StackState LoadImage(VmState* vmstate);
	StackState SaveImage(VmState* vmstate);
	StackState LoadAnimation(VmState* vmstate);
	StackState LoadAnimationFrames(VmState* vmstate);
	StackState GetNativeHandleImage(VmState* vmstate);
	StackState GetImageNativeHandle(VmState* vmstate);
	StackState ImageFromImImage(VmState* vmstate);
	StackState ImageToImImage(VmState* vmstate);
	StackState SaveImageAsText(VmState* vmstate);
};