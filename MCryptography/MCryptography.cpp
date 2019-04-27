// MCryptography.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#ifdef _DEBUG
#pragma comment(lib,"cryptlibD.lib")
#else
#pragma comment(lib,"cryptlib.lib")
#endif
#include "aesx.h"
#include "basex.h"
#include "desx.h"
#include "mdx.h"
#include "rcx.h"
#include "ripemdx.h"
#include "shax.h"

UserFunctionAtter AESList[] = {
	{"AESEncryp",aesx::AESEncryp,2},
	{"AESDecryp",aesx::AESDecryp,2},
	{NULL,NULL,0}
}; 

UserFunctionAtter BASEList[] = {
	{"Base64Encoder",basex::Base64Encoder,1},
	{"Base64Decoder",basex::Base64Decoder,1},
	{"Base32Encoder",basex::Base32Encoder,1},
	{"Base32Decoder",basex::Base32Decoder,1},
	{NULL,NULL,0}
}; 


UserFunctionAtter DESList[] = {
	{"DESEncryp",desx::DESEncryp,2},
	{"DESDecryp",desx::DESDecryp,2},
	{NULL,NULL,0}
}; 


UserFunctionAtter MDList[] = {
	{"MD5",mdx::MD5,1},
	{"MD5File", mdx::MD5File, 1 },
	{"MD2",mdx::MD2,1},
	{"MD4",mdx::MD4,1},
	{NULL,NULL,0}
}; 
	
UserFunctionAtter RCList[] = {
	{"RC4Encryp",rcx::RC4Encryp,2},
	{"RC4Decryp",rcx::RC4Decryp,2},
	{"RC2Encryp",rcx::RC2Encryp,2},
	{"RC2Decryp",rcx::RC2Decryp,2},
	{NULL,NULL,0}
}; 


UserFunctionAtter RIPEMDList[] = {
	{"RIPEMD128",ripemdx::RIPEMD_128,1},
	{"RIPEMD160",ripemdx::RIPEMD_160,1},
	{"RIPEMD256",ripemdx::RIPEMD_256,1},
	{"RIPEMD320",ripemdx::RIPEMD_320,1},
	{NULL,NULL,0}
}; 


UserFunctionAtter SHAList[] = {
	{"SHA1",shax::SHA1,1},
	{"SHA224",shax::SHA224,1},
	{"SHA256",shax::SHA256,1},
	{"SHA384",shax::SHA384,1},
	{"SHA512",shax::SHA512,1},
	{NULL,NULL,0}
}; 


MentholModuleMethod void MP_Init(VmState* vmstate)
{
	RunTimeState* aesprt = CreateModuleRunTime("CAES",vmstate);
	RegisterModuleFunciton(aesprt,AESList);


	RunTimeState* baseprt = CreateModuleRunTime("CBASE", vmstate);
	RegisterModuleFunciton(baseprt,BASEList);

	RunTimeState* desprt = CreateModuleRunTime("CDES", vmstate);
	RegisterModuleFunciton(desprt,DESList);

	RunTimeState* mdprt = CreateModuleRunTime("CMDX", vmstate);
	RegisterModuleFunciton(mdprt,MDList);

	RunTimeState* rcprt = CreateModuleRunTime("CRC", vmstate);
	RegisterModuleFunciton(rcprt,RCList);

	RunTimeState* ripemdprt = CreateModuleRunTime("CRIPEMD", vmstate);
	RegisterModuleFunciton(ripemdprt,RIPEMDList);

	RunTimeState* shaprt = CreateModuleRunTime("CSHA", vmstate);
	RegisterModuleFunciton(shaprt,SHAList);
}
