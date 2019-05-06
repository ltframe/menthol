
#include "System.h"
#include "include\iup_config.h"
vector<callbackstruct> *_tvalues;

namespace System
{	
	
	StackState Init(VmState* vmstate)
	{
		_tvalues =new vector<callbackstruct>();
		return Number_CreateNumber(IupOpen(0,0));
	}


	StackState Close(VmState* vmstate)
	{
		IupClose();

		delete _tvalues;
		return Null_CreateNull();
	}

	StackState Version(VmState* vmstate)
	{
		StackState ver = Dict_CreateDict(vmstate);
		Dict_Push("IUP_NAME",ver.pdict,String_CreateString(IUP_NAME,vmstate));
		Dict_Push("IUP_COPYRIGHT",ver.pdict,String_CreateString(IUP_COPYRIGHT,vmstate));
		Dict_Push("IUP_DESCRIPTION",ver.pdict,String_CreateString(IUP_DESCRIPTION,vmstate));
		Dict_Push("IUP_VERSION",ver.pdict,String_CreateString(IUP_VERSION,vmstate));
		Dict_Push("IUP_VERSION_NUMBER",ver.pdict,Number_CreateNumber(IUP_VERSION_NUMBER));
		Dict_Push("IUP_VERSION_DATE",ver.pdict,String_CreateString(IUP_VERSION_DATE,vmstate));
		return ver;
	}

	StackState Clipboard(VmState* vmstate)
	{
		return Object_CreateObject(IupClipboard());
	}

	StackState Timer(VmState* vmstate)
	{
		return Object_CreateObject(IupTimer());
	}

	StackState User(VmState* vmstate)
	{
		return Object_CreateObject(IupUser());
	}

	StackState Config(VmState* vmstate)
	{
		return Object_CreateObject(IupConfig());
	}

	static void GetALLChilders(Ihandle* b,vector<Ihandle*>* list)
	{
		Ihandle* child = IupGetNextChild(b, NULL);
		if (child){
			list->push_back(child);
		}
		while (child){
			GetALLChilders(child, list);
			child = IupGetNextChild(NULL, child);
		}
	}

	StackState Create(VmState* vmstate)
	{
		return Object_CreateObject(IupCreate(GetParam(1, vmstate).str->string));
	}

	StackState ClassName(VmState* vmstate)
	{
		return String_CreateString(IupGetClassName(static_cast<Ihandle*>(GetParam(1, vmstate).p)),vmstate);
	}

	
	StackState Update(VmState* vmstate)
	{
		IupUpdate(static_cast<Ihandle*>(GetParam(1, vmstate).p));
		return Null_CreateNull();
	}

		
	StackState Redraw(VmState* vmstate)
	{
		IupRedraw(static_cast<Ihandle*>(GetParam(1, vmstate).p),GetParam(1, vmstate).d);
		return Null_CreateNull();
	}
	StackState Destroy(VmState* vmstate)
	{
		vector<Ihandle*>* list = new vector<Ihandle*>();
		Ihandle* handle = static_cast<Ihandle*>(GetParam(1, vmstate).p);
		GetALLChilders(handle, list);
		IupDestroy(handle);
		list->push_back(handle);
		for (std::vector<Ihandle*>::iterator it = list->begin(); it != list->end(); ++it)
		{
			for (std::vector<callbackstruct>::iterator it2 = _tvalues->begin(); it2 != _tvalues->end(); ++it2)
			{
				if ((*it2).handle == (*it))
				{
					_tvalues->erase(it2);
					break;
				}
			}
		}
		delete list;
		return Null_CreateNull();
	}

	
};

