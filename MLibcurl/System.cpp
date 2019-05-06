#include "stdafx.h"
#include "System.h"
namespace System
{
	
	StackState init(VmState* vmstate)
	{
		return  Object_CreateObject(curl_easy_init());
	}

	StackState cleanup(VmState* vmstate)
	{
		curl_easy_cleanup(GetParam(1,vmstate).p);
		return  Null_CreateNull();
	}


	StackState perform(VmState* vmstate)
	{
		return  Number_CreateNumber(curl_easy_perform(GetParam(1,vmstate).p));
	}

	StackState version(VmState* vmstate)
	{
		return  String_CreateString(curl_version(),vmstate);
	}


	StackState unescape(VmState* vmstate) {
		CURL *curl = GetParam(1,vmstate).p;
		char *url = GetParam(2,vmstate).str->string;
		int outlength = 0;
		size_t inlength = strlen(url);
		char *rurl = curl_easy_unescape(curl, url, inlength, &outlength);
		StackState ret = String_CreateString(rurl,vmstate);
		curl_free(rurl);
		return ret;
	}

	StackState escape(VmState* vmstate)
	{
		CURL *curl = GetParam(1,vmstate).p;
		char *url = GetParam(2,vmstate).str->string;
		size_t length = strlen(url);
		char *rurl = curl_easy_escape(curl, url, length);
		StackState ret = String_CreateString(rurl,vmstate);
		curl_free(rurl);
		return ret;
	}
};
