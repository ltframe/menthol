#include "MGc.h"





namespace MGc
{
	static vector<Garbage*> *garbagecollect;
	static vector<Garbage*> *globalgarbagelist;
	static long garbagememorysize;

void InitWGc()
{
	garbagecollect =new vector<Garbage*>();
	globalgarbagelist=new vector<Garbage*>();
	garbagememorysize = 0;
}


long GetGarBageMemorySize()
{
	return garbagememorysize;
}

void CopyToGlobalGarBage(Garbage* g)
{
	globalgarbagelist->push_back(g);
}


void MarkGlobalGarBage()
{
	/*for (std::vector<Garbage*>::iterator it = globalgarbagelist->begin() ; it != globalgarbagelist->end(); ++it)
	{	*/	
	VECTORFORSTART(Garbage*,globalgarbagelist,it)
		if((*it)->v==M_ARRAY)
		{
			MarkArray((vector<StackState>*)(*it)->array);	
		}
		
		if((*it)->v==M_DICT)
		{
			MarkDict((map<hashValue,StackState>*)(*it)->dict);	
		}
		(*it)->mark = 1;
	//}	
	VECTORFOREND
}

static void MarkGarbage(Garbage* g,int mark)
{
	g->mark = mark;
}

void MarkAllGarbages()
{
	/*for (std::vector<Garbage*>::iterator it = garbagecollect->begin() ; it != garbagecollect->end(); ++it)
	{*/	
	VECTORFORSTART(Garbage*,garbagecollect,it)
		(*it)->mark = 0;
	VECTORFOREND
	/*}	*/
}


void ClearGarbage()
{

	for (std::vector<Garbage*>::iterator it = garbagecollect->begin() ; it != garbagecollect->end();)
	{		
		if((*it)->mark==0){
			if((*it)->v==M_STRING){
				char* str = (char*)(*it)->string;
				garbagememorysize-=(strlen(str)+1);
				free(str);
				delete (*it);
				garbagememorysize-=sizeof(Garbage);
				it = garbagecollect->erase(it);
						
				continue;
			}
			if((*it)->v==M_SSTRING){
				delete (*it);
				garbagememorysize-=sizeof(Garbage);
				it = garbagecollect->erase(it);						
				continue;
			}
			if((*it)->v==M_ARRAY){
				delete (vector<StackState>*)((*it)->array);
				garbagememorysize-=sizeof(vector<StackState>);
				delete (*it);
				garbagememorysize-=sizeof(Garbage);
				it = garbagecollect->erase(it);
				continue;
			}
			if((*it)->v==M_DICT){
				delete (map<hashValue,StackState>*)((*it)->dict);
				garbagememorysize-=sizeof(map<hashValue,StackState>);
				delete (*it);
				garbagememorysize-=sizeof(Garbage);
				it = garbagecollect->erase(it);
				continue;
			}
					
		}else
		{			
				++it;
		}
	}	

}



Garbage* CollectGarbage_Array(vector<StackState>* p)
{
	Garbage *g =new Garbage(p);
	garbagememorysize+=sizeof(Garbage);
	garbagecollect->push_back(g);
	return g;
}


Garbage* CollectGarbage_Dict(map<hashValue,StackState>* p)
{
	Garbage *g =new Garbage(p);
	garbagememorysize+=sizeof(Garbage);
	garbagecollect->push_back(g);
	return g;
}

Garbage* CollectGarbage_String(char* p,ValueType v)
{
	Garbage *g =new Garbage(p,v);
	garbagememorysize+=sizeof(Garbage);
	garbagecollect->push_back(g);
	return g;
}




Garbage* CreateString(char* str)
{

	size_t len = strlen(str)+1;
	char* _p = (char*)malloc(len);
	if(!_p){
		MError::CreateInstance()->PrintRunTimeError("Failed to create string");
		return 0;
	}
	char* sss = (char*)_p;
	strcpy(sss,str);
	sss[len-1]='\0';
	garbagememorysize+=len;
	return CollectGarbage_String(sss);
}



Garbage* CreateNullString(size_t len)
{
	char* _p =(char*)malloc(len+1);
	if(!_p){
		MError::CreateInstance()->PrintRunTimeError("Failed to create string");
		return 0;
	}
	garbagememorysize+=len+1;
	return CollectGarbage_String(_p);
}


Garbage* CreateArray()
{
	vector<StackState>* ar =new vector<StackState>();
	garbagememorysize+=sizeof(vector<StackState>);
	return CollectGarbage_Array(ar);
}

Garbage* CreateDict()
{
	map<hashValue,StackState>* ma =new map<hashValue,StackState>();
	garbagememorysize+=sizeof(map<hashValue,StackState>);
	return CollectGarbage_Dict(ma);
}

void MarkArray(vector<StackState>* arr){

	/*for (std::vector<StackState>::iterator it = arr->begin() ; it != arr->end();++it)
	{	*/
	VECTORFORSTART(StackState,arr,it)
		if((*it).v==M_ARRAY){
				MarkGarbage((*it).parray,1);
				MarkArray((vector<StackState>*)(*it).parray->array);			
		}
		if((*it).v==M_STRING)		
		{
			MarkGarbage((*it).str,1);
		}
		if((*it).v==M_DICT){
			MarkGarbage((*it).pdict,1);
			MarkDict((map<hashValue,StackState>*)(*it).pdict->dict);			
		}
	VECTORFOREND
	/*}*/
}

void MarkDict(map<hashValue,StackState>* arr){

	for (std::map<hashValue,StackState>::iterator it = arr->begin() ; it != arr->end();++it)
	{	
		if((*it).second.v==M_DICT){
			MarkGarbage((*it).second.pdict,1);
			MarkDict((map<hashValue,StackState>*)(*it).second.pdict->dict);				
		}
		if((*it).second.v==M_STRING)
		{
			MarkGarbage((*it).second.str,1);
		}
		if((*it).second.v==M_ARRAY){
			MarkGarbage((*it).second.parray,1);
			MarkArray((vector<StackState>*)(*it).second.parray->array);	
		}
	}
}

}