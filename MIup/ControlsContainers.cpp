#include "ControlsContainers.h"

namespace ControlsContainers
{
	StackState Fill(VmState* vmstate)
	{
		return Object_CreateObject(IupFill());
	}

	StackState Space(VmState* vmstate)
	{
		return Object_CreateObject(IupSpace());
	}

	StackState Cbox(VmState* vmstate)
	{
		StackState p1 =GetParam(1,vmstate);
		if(p1.v==M_NULL)
		{
			return Object_CreateObject(IupCbox(0));
		}
		return Object_CreateObject(IupCbox(static_cast<Ihandle*>(p1.p),0));
	}

	StackState GridBox(VmState* vmstate)
	{
		StackState p1 =GetParam(1,vmstate);
		if(p1.v==M_NULL)
		{
			return Object_CreateObject(IupGridBox(0));
		}
		return Object_CreateObject(IupGridBox(static_cast<Ihandle*>(p1.p),0));
	}

	StackState MultiBox(VmState* vmstate)
	{
		StackState p1 =GetParam(1,vmstate);
		if(p1.v==M_NULL)
		{
			return Object_CreateObject(IupMultiBox(0));
		}
		return Object_CreateObject(IupMultiBox(static_cast<Ihandle*>(p1.p),0));
	}

	StackState Hbox(VmState* vmstate)
	{
		StackState p1 =GetParam(1,vmstate);
		if(p1.v==M_NULL)
		{
			return Object_CreateObject(IupHbox(0));
		}
		return Object_CreateObject(IupHbox(static_cast<Ihandle*>(p1.p),0));
	}

	StackState Vbox(VmState* vmstate)
	{
		StackState p1 =GetParam(1,vmstate);
		if(p1.v==M_NULL)
		{
			return Object_CreateObject(IupVbox(0));
		}
		return Object_CreateObject(IupVbox(static_cast<Ihandle*>(p1.p),0));
	}

	StackState Zbox(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupZbox(0));
		}
		return Object_CreateObject(IupZbox(static_cast<Ihandle*>(p1.p), 0));
	}

	StackState Radio(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupRadio(0));
		}
		return Object_CreateObject(IupRadio(static_cast<Ihandle*>(p1.p)));
	}

	StackState Normalizer(VmState* vmstate)
	{
		return Object_CreateObject(IupNormalizer(0));
	}

	StackState Frame(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupFrame(0));
		}
		return Object_CreateObject(IupFrame(static_cast<Ihandle*>(p1.p)));
	}

	StackState FlatFrame(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupFlatFrame(0));
		}
		return Object_CreateObject(IupFlatFrame(static_cast<Ihandle*>(p1.p)));
	}

	StackState Tabs(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupTabs(0));
		}
		return Object_CreateObject(IupTabs(static_cast<Ihandle*>(p1.p)));
	}

	StackState FlatTabs(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupFlatTabs(0));
		}
		return Object_CreateObject(IupFlatTabs(static_cast<Ihandle*>(p1.p)));
	}

	StackState BackgroundBox(VmState* vmstate)
	{
		return Object_CreateObject(IupBackgroundBox(0));
	}

	StackState ScrollBox(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupScrollBox(0));
		}
		return Object_CreateObject(IupScrollBox(static_cast<Ihandle*>(p1.p)));
	}

	StackState FlatScrollBox(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupFlatScrollBox(0));
		}
		return Object_CreateObject(IupFlatScrollBox(static_cast<Ihandle*>(p1.p)));
	}

	StackState DetachBox(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupDetachBox(0));
		}
		return Object_CreateObject(IupDetachBox(static_cast<Ihandle*>(p1.p)));
	}


	StackState Expander(VmState* vmstate)
	{
		StackState p1 = GetParam(1, vmstate);
		if (p1.v == M_NULL)
		{
			return Object_CreateObject(IupExpander(0));
		}
		return Object_CreateObject(IupExpander(static_cast<Ihandle*>(p1.p)));
	}

	StackState Sbox(VmState* vmstate)
	{
		return Object_CreateObject(IupSbox(0));
	}


	StackState Split(VmState* vmstate)
	{
		return Object_CreateObject(IupSplit(static_cast<Ihandle*>(GetParam(1,vmstate).p),static_cast<Ihandle*>(GetParam(2,vmstate).p)));
	}
};


