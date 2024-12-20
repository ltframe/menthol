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

		string str = pText.str->string;
		smatch result;
		regex pattern(filed.str->string);
		string::const_iterator iterStart = str.begin();
		string::const_iterator iterEnd = str.end();
		string temp;
		while (regex_search(iterStart, iterEnd, result, pattern))
		{
			temp = result[0];
			Array_Push(arr.parray, String_CreateString(const_cast<char*>(temp.c_str()), vmstate));
			iterStart = result[0].second; 
		}
		return arr;
	}

	StackState Test(VmState* vmstate)
	{
		StackState ret;
		ret.v = M_BOOL;
		StackState filed = GetParam(2, vmstate);
		StackState pText = GetParam(1, vmstate);
		regex r(filed.str->string);
		string str= pText.str->string;
		if (regex_match(str, r)) {
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
		/*StackState flag = GetParam(4,vmstate);
		static CRegexpT<char> regexp(filed.str->string, flag.d);
		char* s = regexp.Replace(pText.str->string, repText.str->string);
		StackState ret = String_CreateString(s,vmstate);
		regexp.ReleaseString(s);
		return ret;*/


		regex pattern(filed.str->string);
		string s = regex_replace((pText.str->string), pattern,repText.str->string);
		StackState ret = String_CreateString((char*)s.c_str(), vmstate);
		return ret;
	}

};

