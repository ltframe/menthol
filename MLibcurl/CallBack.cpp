#include "stdafx.h"
#include "CallBack.h"
namespace CallBack
{
	struct callbackstate
	{
		VmState* vmstate;
		StackState ss;

	};
	static size_t m_easy_readfunction(void *ptr, size_t size, size_t nmemb, void *stream) 
	{
		callbackstate * cbs = (callbackstate *)stream;
		CreateFunctionCall(1,cbs->vmstate);
		PushString(String_CreateString((char*)ptr, cbs->vmstate).str, cbs->vmstate);
		CallFunction(cbs->ss, cbs->vmstate);
		return nmemb;
	}

	static size_t m_easy_writefunction(void *ptr, size_t size, size_t nmemb, void *stream) 
	{
		callbackstate * cbs = (callbackstate *)stream;
		CreateFunctionCall(1, cbs->vmstate);
		PushString(String_CreateString((char*)ptr, cbs->vmstate).str, cbs->vmstate);
		CallFunction(cbs->ss, cbs->vmstate);
		return nmemb*size;
	}
	
	static size_t m_easy_headerfunction(void *ptr, size_t size, size_t nmemb, void *stream) 
	{
		callbackstate * cbs = (callbackstate *)stream;
		CreateFunctionCall(1, cbs->vmstate);
		PushString(String_CreateString((char*)ptr, cbs->vmstate).str, cbs->vmstate);
		CallFunction(cbs->ss, cbs->vmstate);
		return nmemb*size;
	}

	StackState m_easy_setup_writefunction(VmState* vmstate) {
	CURL *curl = GetParam(1, vmstate).p;
	
	callbackstate *cbs = new callbackstate();
	cbs->vmstate = vmstate;
	cbs->ss = GetParam(2, vmstate);

	if (curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)cbs) != CURLE_OK)
		Number_CreateNumber(0);
	if (curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, m_easy_writefunction) != CURLE_OK)
		Number_CreateNumber(0);
	  return Number_CreateNumber(1);
	}

	StackState m_easy_setup_readfunction(VmState* vmstate)
	{
	  CURL *curl = GetParam(1, vmstate).p;
	  callbackstate cbs = { vmstate, GetParam(2, vmstate) };

	  if (curl_easy_setopt(curl, CURLOPT_READDATA, (void*)&cbs) != CURLE_OK)
		  Number_CreateNumber(0);

	  if (curl_easy_setopt(curl, CURLOPT_READFUNCTION, m_easy_readfunction) != CURLE_OK)
		Number_CreateNumber(0);
	  return Number_CreateNumber(1);
	}

	StackState m_easy_setup_headerfunction(VmState* vmstate)
	{
	  CURL *curl = GetParam(1, vmstate).p;
	  callbackstate cbs = { vmstate, GetParam(2, vmstate) };

	  if (curl_easy_setopt(curl, CURLOPT_WRITEHEADER, (void*)&cbs) != CURLE_OK)
		  Number_CreateNumber(0);

	  if (curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, m_easy_headerfunction) != CURLE_OK)
		Number_CreateNumber(0);

	  return Number_CreateNumber(1);
	}
};
