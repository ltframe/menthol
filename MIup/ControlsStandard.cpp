#include "stdafx.h"
#include "ControlsStandard.h"

namespace ControlsStandard
{
	StackState AnimatedLabel(VmState* vmstate)
	{
		return Object_CreateObject(IupAnimatedLabel(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState Button(VmState* vmstate)
	{
		return Object_CreateObject(IupButton(GetParam(1,vmstate).str->string,0));
	}

	StackState FlatButton(VmState* vmstate)
	{
		return Object_CreateObject(IupFlatButton(GetParam(1,vmstate).str->string));
	}

	StackState DropButton(VmState* vmstate)
	{
		return Object_CreateObject(IupDropButton(static_cast<Ihandle*>(GetParam(1,vmstate).p)));
	}

	StackState Calendar(VmState* vmstate)
	{
		return Object_CreateObject(IupCalendar());
	}

	StackState Canvas(VmState* vmstate)
	{
		return Object_CreateObject(IupCanvas(GetParam(1,vmstate).str->string));
	}

	StackState Colorbar(VmState* vmstate)
	{
		return Object_CreateObject(IupColorbar());
	}

	StackState ColorBrowser(VmState* vmstate)
	{
		return Object_CreateObject(IupColorBrowser());
	}

	StackState DatePick(VmState* vmstate)
	{
		return Object_CreateObject(IupDatePick());
	}

	StackState Dial(VmState* vmstate)
	{
		return Object_CreateObject(IupDial(GetParam(1,vmstate).str->string));
	}

	StackState Gauge(VmState* vmstate)
	{
		return Object_CreateObject(IupGauge());
	}

	StackState Label(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupLabel(0));
		}
		return Object_CreateObject(IupLabel(p1.str->string));
	}

	StackState FlatLabel(VmState* vmstate)
	{
		return Object_CreateObject(IupFlatLabel(GetParam(1,vmstate).str->string));
	}

	StackState FlatSeparator(VmState* vmstate)
	{
		return Object_CreateObject(IupFlatSeparator());
	}

	StackState Link(VmState* vmstate)
	{
		return Object_CreateObject(IupLink(GetParam(1,vmstate).str->string,GetParam(2,vmstate).str->string));
	}

	StackState List(VmState* vmstate)
	{
		return Object_CreateObject(IupList(0));
	}

	StackState ProgressBar(VmState* vmstate)
	{
		return Object_CreateObject(IupProgressBar());
	}

	StackState Spin(VmState* vmstate)
	{
		return Object_CreateObject(IupSpin());
	}

	StackState Spinbox(VmState* vmstate)
	{
		return Object_CreateObject(IupSpinbox(IupText(NULL)));
	}

	StackState Text(VmState* vmstate)
	{
		return Object_CreateObject(IupText(0));
	}

	StackState MultiLine(VmState* vmstate)
	{
		return Object_CreateObject(IupMultiLine(0));
	}

	StackState Toggle(VmState* vmstate)
	{
		return Object_CreateObject(IupToggle(GetParam(1,vmstate).str->string,0));
	}

	StackState FlatToggle(VmState* vmstate)
	{
		return Object_CreateObject(IupFlatToggle(GetParam(1,vmstate).str->string));
	}

	StackState Tree(VmState* vmstate)
	{
		return Object_CreateObject(IupTree());
	}

	StackState Val(VmState* vmstate)
	{
		return Object_CreateObject(IupVal(GetParam(1, vmstate).str->string));
	}
};
