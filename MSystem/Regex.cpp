#include "stdafx.h"
#include "Regex.h"

namespace Regex
{
	StackState Exec(VmState* vmstate)
	{

		StackState arr = Array_CreateArray(vmstate);



		StackState pText = GetParam(1,vmstate);
		StackState filed = GetParam(2,vmstate);
		StackState flag = GetParam(3,vmstate);
		int f = 0;
		if (flag.v == M_NUMBER){
			f = flag.d;
		}

		static CRegexpT<char> regexp(filed.str->string, f);

		CContext * pContext = regexp.PrepareMatch(pText.str->string);

		MatchResult result = regexp.Match(pContext);
		while (result.IsMatched())
		{
			StackState arr1 = Array_CreateArray(vmstate);
			int start = result.GetStart();
			int end = result.GetEnd();

			char* s0 = (char*)malloc(end - start + 1);
			memset(s0, 0, end - start + 1);
			s0[end - start] = 0;
			strncpy(s0, pText.str->string + start, (pText.str->string + end) - (pText.str->string + start));
			Array_Push(arr1.parray, String_CreateString(s0,vmstate));
			free(s0);

			for (int i = 1; i <= result.MaxGroupNumber(); i++){
				int _start = result.GetGroupStart(i);
				int _end = result.GetGroupEnd(i);
				char* s = (char*)malloc(_end - _start + 1);
				memset(s, 0, _end - _start + 1);
				s[_end - _start] = 0;
				strncpy(s, pText.str->string + _start, (pText.str->string + _end) - (pText.str->string + _start));
				Array_Push(arr1.parray, String_CreateString(s,vmstate));
				free(s);
			}
			Array_Push(arr.parray, arr1);
			result = regexp.Match(pContext);
		}
		regexp.ReleaseContext(pContext);
		return arr;
	}

	StackState Test(VmState* vmstate)
	{
		StackState ret;
		ret.v = M_BOOL;
		StackState pText = GetParam(1,vmstate);
		StackState filed = GetParam(2,vmstate);
		StackState flag = GetParam(3,vmstate);
		static CRegexpT<char> regexp(filed.str->string, flag.d);
		MatchResult result = regexp.Match(pText.str->string);
		while (result.IsMatched())
		{
			ret.b = true;
			return ret;
		}
		ret.b = false;
		return ret;
	}


	StackState Replace(VmState* vmstate)
	{

		StackState pText = GetParam(1,vmstate);
		StackState repText = GetParam(2,vmstate);
		StackState filed = GetParam(3,vmstate);
		StackState flag = GetParam(4,vmstate);
		static CRegexpT<char> regexp(filed.str->string, flag.d);
		char* s = regexp.Replace(pText.str->string, repText.str->string);
		StackState ret = String_CreateString(s,vmstate);
		regexp.ReleaseString(s);
		return ret;
	}

};

