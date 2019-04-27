#include "stdafx.h"
#include "GetInfo.h"
namespace GetInfo
{
	/*template<class T> T easy_getinfo_sld()
	{
		CURL *curl = GetParam(1).p;
		CURLINFO infop = CURLINFO(GetParam(2).d);
		T value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
			return 0;

		return value;
	}*/

	StackState m_easy_getinfo_string(VmState* vmstate) {
		CURL *curl = GetParam(1, vmstate).p;
		CURLINFO infop = CURLINFO((int)GetParam(2, vmstate).d);
		char *value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
			return Null_CreateNull();

		return String_CreateString(value, vmstate);
	}

	StackState m_easy_getinfo_long(VmState* vmstate) {
		CURL *curl = GetParam(1, vmstate).p;
		CURLINFO infop = CURLINFO((int)GetParam(2, vmstate).d);
		long value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
			return Number_CreateNumber(0);

		return Number_CreateNumber(value);
	}

	StackState m_easy_getinfo_double(VmState* vmstate) {
		CURL *curl = GetParam(1,vmstate).p;
		CURLINFO infop = CURLINFO((int)GetParam(2, vmstate).d);
		double value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
			return Number_CreateNumber(0);

		return Number_CreateNumber(value);
	}

	StackState m_easy_getinfo_curl_slist(VmState* vmstate) {
		CURL *curl = GetParam(1, vmstate).p;
		CURLINFO infop = CURLINFO((int)GetParam(2, vmstate).d);
		struct curl_slist *list;
		struct curl_slist *next;
		int i;

		if (curl_easy_getinfo(curl, infop, &list) != CURLE_OK)
			return Null_CreateNull();

		i = 1;
		next = list;
		StackState ret = Array_CreateArray(vmstate);

		while (next) {
			Array_Push(ret.parray, String_CreateString(next->data, vmstate));
			next = next->next;
		}

		curl_slist_free_all(list);
		return ret;
	}
};

