#pragma once
#include "header.h"
namespace GetInfo
{


		/*
		static char* easy_getinfo_string() {
		CURL *curl = GetParam(1).p;
		CURLINFO infop = CURLINFO(GetParam(2).d);
		char *value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
		return 0;

		return value;
		}

		static long easy_getinfo_long() {
		CURL *curl = GetParam(1).p;
		CURLINFO infop = CURLINFO(GetParam(2).d);
		long value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
		return 0;

		return value;
		}

		static double easy_getinfo_double() {
		CURL *curl = GetParam(1).p;
		CURLINFO infop = CURLINFO(GetParam(2).d);
		double value;

		if (curl_easy_getinfo(curl, infop, &value) != CURLE_OK)
		return 0;

		return value;
		}
		*/





	StackState m_easy_getinfo_string(VmState* vmstate);
	StackState m_easy_getinfo_long(VmState* vmstate);
	StackState m_easy_getinfo_double(VmState* vmstate);
	StackState m_easy_getinfo_curl_slist(VmState* vmstate);
};

