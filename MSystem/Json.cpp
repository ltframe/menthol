#include "stdafx.h"
#include "Json.h"

namespace Json
{
	static StackState getitem(cJSON *obj,VmState* vmstate)
	{
		StackState value;
		switch (obj->type)
		{
		case cJSON_False:
		{
			value.v = M_BOOL;
			value.b = false;
			break;
		}
		case cJSON_True:
		{
			value.v = M_BOOL;
			value.b = true;
			break;
		}
		case cJSON_NULL:
		{
			value.v = M_NULL;
			break;
		}
		case cJSON_Number:
		{
			value.v = M_NUMBER;
			value.d = obj->valuedouble;
			break;
		}
		case cJSON_String:
		{
			value.v = M_STRING;
			value.str = String_CreateString(obj->valuestring,vmstate).str;
			break;
		}
		case cJSON_Array:
			value.v = M_ARRAY;
			value.p = obj;
			break;
			break;
		case cJSON_Object:
			value.v = M_OBJECT;
			value.p = obj;
			break;
		default:
			break;
		}
		return value;

	}

	StackState GetArrayItem(VmState* vmstate)
	{
		StackState inst = GetParam(1,vmstate);
		StackState filed = GetParam(2,vmstate);
		cJSON *json = static_cast<cJSON*>(inst.p);
		cJSON *obj = cJSON_GetArrayItem(json, (int)filed.d);
		return getitem(obj,vmstate);
	}

	StackState GetArraySize(VmState* vmstate)
	{
		StackState inst = GetParam(1,vmstate);
		cJSON *json = static_cast<cJSON*>(inst.p);
		StackState t;
		t.v = M_NUMBER;
		t.d = cJSON_GetArraySize(json);
		return t;
	}

	StackState JsonParse(VmState* vmstate)
	{
		char* str = GetParam(1,vmstate).str->string;
		StackState t;
		t.p = cJSON_Parse(str);
		t.v = M_OBJECT;
		return t;
	}


	StackState GetObjectItem(VmState* vmstate)
	{
		StackState inst = GetParam(1,vmstate);
		StackState filed = GetParam(2,vmstate);
		cJSON *obj = cJSON_GetObjectItem(static_cast<cJSON*>(inst.p), filed.str->string);
		return getitem(obj,vmstate);
	}

	StackState Delete(VmState* vmstate)
	{
		StackState inst = GetParam(1,vmstate);
		cJSON_Delete(static_cast<cJSON*>(inst.p));
		StackState st;
		st.v = M_NULL;
		return st;
	}


	StackState Type(VmState* vmstate)
	{
		StackState inst = GetParam(1,vmstate);
		cJSON *obj = static_cast<cJSON*>(inst.p);
		switch (obj->type)
		{
		case cJSON_False:
			return String_CreateString("cJSON_False",vmstate);
		case cJSON_True:
			return String_CreateString("cJSON_True",vmstate);
		case cJSON_NULL:
			return String_CreateString("cJSON_NULL",vmstate);
		case cJSON_Number:
			return String_CreateString("cJSON_Number",vmstate);
		case cJSON_String:
			return String_CreateString("cJSON_String",vmstate);
		case cJSON_Array:
			return String_CreateString("cJSON_Array",vmstate);
		case cJSON_Object:
			return String_CreateString("cJSON_Object",vmstate);
			break;
		default:
			break;
		}
		return String_CreateString("",vmstate);
	}
};
