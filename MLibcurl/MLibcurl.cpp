// MLibcurl.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Menthol.h"
#include "CallBack.h"
#include "GetInfo.h"
#include "SetOpt.h"
#include "System.h"




UserFunctionAtter SystemList[] = {
	{ "init", System::init, 0 },
	{ "cleanup", System::cleanup, 1 },
	{ "perform", System::perform, 1 },
	{ "version", System::version, 0 },
	{ "unescape", System::unescape, 2 },
	{ "escape", System::escape, 2 },
	{ NULL, NULL, 0 }
};

UserFunctionAtter SetoptList[] = {
  {"verbose",SetOpt::m_easy_setopt_long,3},
  {"header",SetOpt::m_easy_setopt_long,3},
  {"noprogress",SetOpt::m_easy_setopt_long,3},
  {"nosignal",SetOpt::m_easy_setopt_long,3},
  {"autoreferer",SetOpt::m_easy_setopt_long,3},
  {"encoding",SetOpt::m_easy_setopt_string,3},
  {"followlocation",SetOpt::m_easy_setopt_long,3},
  {"unrestricted_AUTH",SetOpt::m_easy_setopt_long,3},
  {"maxredirs",SetOpt::m_easy_setopt_long,3},
  {"post",SetOpt::m_easy_setopt_long,3},
  {"postfields",SetOpt::m_easy_setopt_string,3},
  {"postfieldsize",SetOpt::m_easy_setopt_long,3},
  {"postfieldsize_LARGE",SetOpt::m_easy_setopt_long,3},
  {"httppost",SetOpt::m_easy_setopt_long,3},
  {"referer",SetOpt::m_easy_setopt_string,3},
  {"useragent",SetOpt::m_easy_setopt_string,3},
  {"httpheader",SetOpt::m_easy_setopt_strings,2},
  {"httpauth",SetOpt::m_easy_setopt_httpauth,3},
  {"timeout",SetOpt::m_easy_setopt_long,3},
  {"cookie",SetOpt::m_easy_setopt_string,3},
  {"cookiefile",SetOpt::m_easy_setopt_string,3},
  {"cookiejar",SetOpt::m_easy_setopt_string,3},
  {"cookiesession",SetOpt::m_easy_setopt_long,3},
#ifdef CURLOPT_COOKIELIST
  {"cookielist",SetOpt::m_easy_setopt_string,3},
#endif
  {"httpget",SetOpt::m_easy_setopt_long,3},
  {"http_version",SetOpt::m_easy_setopt_long,3}, 
  {"ignore_content_length",SetOpt::m_easy_setopt_long,3},
#ifdef CURLOPT_HTTP_CONTENT_DECODING
  {"http_content_decoding",SetOpt::m_easy_setopt_long,3},
#endif
#ifdef CURLOPT_HTTP_TRANSFER_DECODING
  {"http_transfer_decoding ", CURLOPT_HTTP_TRANSFER_DECODING ,SetOpt::m_easy_setopt_long,3},
#endif
  {"transfertext",SetOpt::m_easy_setopt_long,3},
  {"crlf",SetOpt::m_easy_setopt_long,3},
  {"range",SetOpt::m_easy_setopt_string,3},
  {"resume_from",SetOpt::m_easy_setopt_long,3},
  {"resume_from_large",SetOpt::m_easy_setopt_long,3},
  {"customrequest",SetOpt::m_easy_setopt_string,3},
  {"filetime",SetOpt::m_easy_setopt_long,3},
  {"nobody",SetOpt::m_easy_setopt_long,3},
  {"infilesize",SetOpt::m_easy_setopt_long,3},
  {"infilesize_large",SetOpt::m_easy_setopt_long,3},
  {"upload",SetOpt::m_easy_setopt_long,3},
  {"maxfilesize",SetOpt::m_easy_setopt_long,3},
  {"maxfilesize_large",SetOpt::m_easy_setopt_long,3},
  {"timecondition",SetOpt::m_easy_setopt_long,3},
  {"timevalue ",SetOpt::m_easy_setopt_long,3},
  {"url",SetOpt::m_easy_setopt_string,3},
  {"protocols",SetOpt::m_easy_setopt_long,3},
  {"redir_protocols",SetOpt::m_easy_setopt_long,3},
  {"proxy",SetOpt::m_easy_setopt_string,3},
  {"username",SetOpt::m_easy_setopt_string,3},
  {"password",SetOpt::m_easy_setopt_string,3},
  {"userpwd",SetOpt::m_easy_setopt_string,3},
  {"proxyuserpwd",SetOpt::m_easy_setopt_string,3},
  {"proxyport",SetOpt::m_easy_setopt_long,3},
  {"proxytype",SetOpt::m_easy_setopt_proxytype,3},
  {"httpproxytunnel",SetOpt::m_easy_setopt_long,3},
  {"interface",SetOpt::m_easy_setopt_string,3},
  {"localport",SetOpt::m_easy_setopt_long,3},
  {"localportrange",SetOpt::m_easy_setopt_long,3},
  {"dns_cache_timeout",SetOpt::m_easy_setopt_long,3},
  {"dns_use_global_cache",SetOpt::m_easy_setopt_long,3},
  {"buffersize",SetOpt::m_easy_setopt_long,3},
  {"port",SetOpt::m_easy_setopt_long,3},
  {"TCP_nodelay",SetOpt::m_easy_setopt_long,3},
  {"ssl_verifypeer",SetOpt::m_easy_setopt_long,3},
  {"sslcert",SetOpt::m_easy_setopt_string,3},
  {"sslcerttype",SetOpt::m_easy_setopt_string,3},
  {"sslcertpasswd",SetOpt::m_easy_setopt_string,3},
  {"sslkey",SetOpt::m_easy_setopt_string,3},
  {"sslkeytype",SetOpt::m_easy_setopt_string,3},
  {"sslkeypasswd",SetOpt::m_easy_setopt_string,3},
  {"sslengine",SetOpt::m_easy_setopt_string,3},
  {"sslengine_default",SetOpt::m_easy_setopt_long,3},
  {"cainfo",SetOpt::m_easy_setopt_string,3},
  {"capath",SetOpt::m_easy_setopt_string,3},
  {"random_file",SetOpt::m_easy_setopt_string,3},
  {"egdsocket",SetOpt::m_easy_setopt_string,3},
  {"ssl_verifyhost",SetOpt::m_easy_setopt_long,3},
  {"ssl_cipher_list",SetOpt::m_easy_setopt_string,3},
#ifdef CURLOPT_SSL_SESSIONID_CACHE
  {"ssl_sessionid_cache",SetOpt::m_easy_setopt_long,3},
#endif
  { NULL, NULL, 0 }
};

UserFunctionAtter GetinfoList[] = {
	{"effective_url", GetInfo::m_easy_getinfo_string, 2 },
	{"response_code", GetInfo::m_easy_getinfo_long, 2 },
	{"http_connectcode", GetInfo::m_easy_getinfo_long, 2 },
	{"filetime", GetInfo::m_easy_getinfo_long, 2 },
	{"total_time", GetInfo::m_easy_getinfo_double, 2 },
	{"namelookup_time", GetInfo::m_easy_getinfo_double, 2 },
	{"connect_time", GetInfo::m_easy_getinfo_double, 2 },
	{"pretransfer", GetInfo::m_easy_getinfo_double, 2 },
	{"starttransfer_time", GetInfo::m_easy_getinfo_double, 2 },
	{"redirect_time", GetInfo::m_easy_getinfo_double, 2 },
	{"redirect_count", GetInfo::m_easy_getinfo_long, 2 },
	{"size_upload", GetInfo::m_easy_getinfo_double, 2 },
	{"size_download", GetInfo::m_easy_getinfo_double, 2 },
	{"speed_download", GetInfo::m_easy_getinfo_double, 2 },
	{"speed_upload", GetInfo::m_easy_getinfo_double, 2 },
	{"header_size", GetInfo::m_easy_getinfo_long, 2 },
	{"request_size", GetInfo::m_easy_getinfo_long, 2 },
	{"ssl_verifyresult", GetInfo::m_easy_getinfo_long, 2 },
	{"ssl_engines", GetInfo::m_easy_getinfo_curl_slist, 2 },
	{"content_length_download", GetInfo::m_easy_getinfo_double, 2 },
	{"content_length_upload", GetInfo::m_easy_getinfo_double, 2 },
	{"content_type", GetInfo::m_easy_getinfo_string, 2 },
	{"private", GetInfo::m_easy_getinfo_string, 2 },
	{"httpauth_avail", GetInfo::m_easy_getinfo_long, 2 },
	{"proxyauth_avail", GetInfo::m_easy_getinfo_long, 2 },
	{"os_errno", GetInfo::m_easy_getinfo_long, 2 },
	{"num_connects", GetInfo::m_easy_getinfo_long, 2 },
	{"cookielist", GetInfo::m_easy_getinfo_curl_slist, 2 },
	{"lastsocket", GetInfo::m_easy_getinfo_long, 2 },
	{"ftp_entry_path", GetInfo::m_easy_getinfo_string, 2 },
	{ NULL, NULL, 0 }
};

UserFunctionAtter CallbackList[] = {
	{ "writefunction", CallBack::m_easy_setup_writefunction, 2 },
	{ "readfunction", CallBack::m_easy_setup_readfunction, 2 },
	{ "headerfunction", CallBack::m_easy_setup_headerfunction, 2 },
	{ NULL, NULL, 0 }
};

MentholModuleMethod void MP_Init(VmState* vmstate)
{	
	RunTimeState* system = CreateModuleRunTime("CCurl_System", vmstate);
	RegisterModuleFunciton(system, SystemList);

	RunTimeState* setopt = CreateModuleRunTime("CCurl_Setopt", vmstate);
	RegisterModuleFunciton(setopt, SetoptList);

	RunTimeState* getinfo = CreateModuleRunTime("CCurl_Getinfo", vmstate);
	RegisterModuleFunciton(getinfo, GetinfoList);

	RunTimeState* callback = CreateModuleRunTime("CCurl_Callback", vmstate);
	RegisterModuleFunciton(callback, CallbackList);
}