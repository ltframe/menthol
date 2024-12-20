// MThread.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#pragma comment(lib,"../requirements/pthread/pthreadVC2.lib")
#include "../requirements/pthread/pthread.h"
#include "../Menthol/MentholHeader.h"

struct threadinfo
{
	StackState ss;
	pthread_t pt;
};

map<int, threadinfo> functionlist;
pthread_mutex_t pmutex = PTHREAD_MUTEX_INITIALIZER;  

void* callback(void *arg)
{
	VmState* vmstate = NewVmState();
	NewVm(vmstate);
	int key = (int)(int*)arg;
	CreateFunctionCall(0,vmstate);
	threadinfo ti = functionlist.find(key)->second;
	CallFunction(ti.ss,vmstate);
	ClearVmState(vmstate);

	pthread_detach(ti.pt);
	pthread_exit(0) ;
	for (auto it = functionlist.begin(); it != functionlist.end();)
		if (it->first==key)
			it = functionlist.erase(it);
		else
			++it;
	
	return 0;
}

StackState NewThread(VmState* vmstate)
{

	int k  = 0;
	while (1){
		srand(time(0));
		k  = rand()%(1-RAND_MAX+1)+RAND_MAX;
		if (functionlist.find(k) == functionlist.end())
		{

			pthread_t thread;
			pthread_attr_t attr;
			pthread_attr_init(&attr);
			//pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
			int stauts = pthread_create(&thread, &attr, callback,(int*)k);
			threadinfo ti = {GetParam(1, vmstate),thread};
			functionlist.insert(pair<int, threadinfo>(k,ti ));
			if (stauts!= 0){
				
				return Number_CreateNumber(0);
			}
			pthread_attr_destroy(&attr);
			break;
		}
	}
	Sleep(1);
	return Number_CreateNumber(k);
}




StackState Join(VmState* vmstate)
{
	threadinfo ti = functionlist.find(GetParam(1, vmstate).d)->second;
	void *ret;
	int stauts =pthread_join(ti.pt,&ret);
	if(stauts)
	{
		return Bool_CreateBool(false);
	}
	return Bool_CreateBool(true);
}

StackState Lock(VmState* vmstate)
{
	if(pthread_mutex_lock(&pmutex))
	{
		return Bool_CreateBool(false);
	}
	return Bool_CreateBool(true);
}

StackState UnLock(VmState* vmstate)
{
	if(pthread_mutex_unlock(&pmutex))
	{
		return Bool_CreateBool(false);
	}
	return Bool_CreateBool(true);
}


UserFunctionAtter Threadlist[] = {
	{ "NewThread", NewThread, 1 },
	{"Join",Join,1},
	{"Lock",Lock,0},
	{"UnLock",UnLock,0},
	{ NULL, NULL, 0 }
};

MentholModuleMethod void MP_Init(VmState* vmstate)
{
	RunTimeState* prt = CreateModuleRunTime("CThread", vmstate);
	RegisterModuleFunciton(prt, Threadlist);
}

