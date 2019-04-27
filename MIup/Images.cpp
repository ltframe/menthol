#include "stdafx.h"
#include "Images.h"
#include "include\im.h"
#include "include\im_image.h"
#include  "include\iupim.h"
namespace Images
{

	StackState Image(VmState* vmstate)
	{
		pArray arr = GetParam(3,vmstate).parray;
		int s = Array_Length(arr);

		unsigned char *pixmap_x = new unsigned char[s];
		for (size_t i = 0; i < s; i++)
		{
			pixmap_x[i] = (unsigned char)(int)Array_Get(arr, i).d;
		}

		StackState ret = Object_CreateObject(IupImage((int)GetParam(1,vmstate).d,(int)GetParam(2,vmstate).d, pixmap_x));
		//delete pixmap_x;
		return ret;
	}
	StackState LoadImage(VmState* vmstate)
	{
		char* str = GetParam(1,vmstate).str->string;
		return Object_CreateObject(IupLoadImage(str));
	}

	StackState SaveImage(VmState* vmstate)
	{
		return Number_CreateNumber(IupSaveImage(static_cast<Ihandle*>(GetParam(1,vmstate).p),GetParam(2,vmstate).str->string,GetParam(3,vmstate).str->string));
	}

	StackState LoadAnimation(VmState* vmstate)
	{
		return Object_CreateObject(IupLoadAnimation(GetParam(1,vmstate).str->string));
	}

	StackState LoadAnimationFrames(VmState* vmstate)
	{
		pArray arr = GetParam(1,vmstate).parray;
		int s = Array_Length(arr);
		const char** f = new const char*[s];
		for (size_t i = 0; i < s ; i++)
		{
			f[i] = Array_Get(arr, i).str->string;
		}
		StackState ret = Object_CreateObject(IupLoadAnimationFrames(f, s));
		delete f;
		return ret;
	}

	StackState GetNativeHandleImage(VmState* vmstate)
	{
		return Object_CreateObject(IupGetNativeHandleImage(static_cast<void*>(GetParam(1,vmstate).p)));

	}
	StackState GetImageNativeHandle(VmState* vmstate)
	{
		return Object_CreateObject(IupGetImageNativeHandle(static_cast<imImage*>(GetParam(1,vmstate).p)));
	}
	
	StackState ImageFromImImage(VmState* vmstate)
	{
		return Object_CreateObject(IupImageFromImImage(static_cast<imImage*>(GetParam(1,vmstate).p)));
	}
	StackState ImageToImImage(VmState* vmstate)
	{
		return Object_CreateObject(IupImageToImImage(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}
	StackState SaveImageAsText(VmState* vmstate)
	{
		return Number_CreateNumber(IupSaveImageAsText(static_cast<Ihandle*>(GetParam(1,vmstate).p), GetParam(2,vmstate).str->string, GetParam(3,vmstate).str->string, GetParam(4,vmstate).str->string));
	}
};
