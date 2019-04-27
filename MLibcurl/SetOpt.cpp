#include "stdafx.h"
#include "SetOpt.h"
namespace SetOpt
{

	StackState m_easy_setopt_long(VmState* vmstate) {
		CURL *curl = GetParam(1,vmstate).p;
		CURLoption optionp = CURLoption((int)GetParam(2,vmstate).d);
		long value = GetParam(3,vmstate).d;
		if (curl_easy_setopt(curl, optionp, value) != CURLE_OK)
			return Number_CreateNumber(0);

		return Number_CreateNumber(1);
	}

	StackState m_easy_setopt_string(VmState* vmstate) {
		CURL *curl = GetParam(1,vmstate).p;
		CURLoption optionp = CURLoption((int)GetParam(2,vmstate).d);
		const char *value = GetParam(3,vmstate).str->string;

		if (curl_easy_setopt(curl, optionp, value) != CURLE_OK)
			return Number_CreateNumber(0);

		return Number_CreateNumber(1);
	}
	
	StackState m_easy_setopt_strings(VmState* vmstate) {
		CURL *curl = GetParam(1,vmstate).p;
		CURLoption optionp = CURLoption((int)GetParam(2,vmstate).d);
		struct curl_slist *list = NULL;
	

		pArray arr = GetParam(3,vmstate).parray;
		for (size_t i = 0; i < Array_Length(arr); i++)
		{
			list = curl_slist_append(list, Array_Get(arr,i).str->string);
		}
		if (curl_easy_setopt(curl, optionp, list) != CURLE_OK)
			return Number_CreateNumber(0);

		return Number_CreateNumber(1);
	}

	StackState m_easy_setopt_proxytype(VmState* vmstate)
	{
		CURL *curl = GetParam(1,vmstate).p;
		CURLoption optionp = CURLoption((int)GetParam(2,vmstate).d);
		const char *value = GetParam(3,vmstate).str->string;


		/* check for valid OPTION: */
		curl_proxytype type;

		if (!strcmp("HTTP", value))
			type = CURLPROXY_HTTP;
		else if (!strcmp("SOCKS4", value))
			type = CURLPROXY_SOCKS4;
		else if (!strcmp("SOCKS5", value))
			type = CURLPROXY_SOCKS5;
		else
			return Number_CreateNumber(0);

		if (curl_easy_setopt(curl, optionp, type) != CURLE_OK)
			return Number_CreateNumber(0);

		return Number_CreateNumber(1);
	}



	StackState m_easy_setopt_httpauth(VmState* vmstate) {
		CURL *curl = GetParam(1,vmstate).p;
		CURLoption optionp = CURLoption((int)GetParam(2,vmstate).d);
			const char *value = GetParam(3,vmstate).str->string;

		long type;

		if (!strcmp("NONE", value))
			type = CURLAUTH_NONE;
		else if (!strcmp("BASIC", value))
			type = CURLAUTH_BASIC;
		else if (!strcmp("DIGEST", value))
			type = CURLAUTH_DIGEST;
		else if (!strcmp("GSSNEGOTIATE", value))
			type = CURLAUTH_GSSNEGOTIATE;
		else if (!strcmp("NTLM", value))
			type = CURLAUTH_NTLM;
		else if (!strcmp("CURLAUTH_ANY", value))
			type = CURLAUTH_ANY;
		else if (!strcmp("ANYSAFE", value))
			type = CURLAUTH_ANYSAFE;
		else
			return Number_CreateNumber(0);

		if (curl_easy_setopt(curl, optionp, type) != CURLE_OK)
			return Number_CreateNumber(0);


		return Number_CreateNumber(1);
	}
};
