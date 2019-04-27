#include "MGc.h"







namespace MGc
{
	
	static vector<Garbage*> *globalgarbagelist;


	GcState* NewWGc()
	{
		GcState* gc = new GcState();
		GCSSTATEGARBAGECOLLECT(gc) =new vector<Garbage*>();
		GCSSTATEGARBAGEMEMORYSIZE(gc) = 0;
		return gc;
	}


	void InitWGc()
	{
		globalgarbagelist=new vector<Garbage*>();		
	}


	long GetGarBageMemorySize(GcState* gc)
	{
		return GCSSTATEGARBAGEMEMORYSIZE(gc);
	}

	vector<Garbage*> * GetGarbageCollect(GcState* gc)
	{
		return GCSSTATEGARBAGECOLLECT(gc);
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
				MarkArray((VECOTRSTACKSTATEPOINTER)(*it)->array);	
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

	void MarkAllGarbages(GcState* gc)
	{
		/*for (std::vector<Garbage*>::iterator it = garbagecollect->begin() ; it != garbagecollect->end(); ++it)
		{*/	
		VECTORFORSTART(Garbage*,GCSSTATEGARBAGECOLLECT(gc),it)
			(*it)->mark = 0;
		VECTORFOREND
		/*}	*/
	}


	void ClearGarbage(GcState* gc)
	{

		for (std::vector<Garbage*>::iterator it = GCSSTATEGARBAGECOLLECT(gc)->begin() ; it != GCSSTATEGARBAGECOLLECT(gc)->end();)
		{		
			if((*it)->mark==0){
				if((*it)->v==M_STRING){
					char* str = (char*)(*it)->string;
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=(strlen(str)+1);
					free(str);
					delete (*it);
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=sizeof(Garbage);
					it = GCSSTATEGARBAGECOLLECT(gc)->erase(it);
						
					continue;
				}
				if((*it)->v==M_SSTRING){
					delete (*it);
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=sizeof(Garbage);
					it = GCSSTATEGARBAGECOLLECT(gc)->erase(it);						
					continue;
				}
				if((*it)->v==M_ARRAY){
					delete (VECOTRSTACKSTATEPOINTER)((*it)->array);
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=sizeof(VECOTRSTACKSTATE);
					delete (*it);
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=sizeof(Garbage);
					it = GCSSTATEGARBAGECOLLECT(gc)->erase(it);
					continue;
				}
				if((*it)->v==M_DICT){
					delete (map<hashValue,StackState>*)((*it)->dict);
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=sizeof(map<hashValue,StackState>);
					delete (*it);
					GCSSTATEGARBAGEMEMORYSIZE(gc)-=sizeof(Garbage);
					it = GCSSTATEGARBAGECOLLECT(gc)->erase(it);
					continue;
				}
					
			}else
			{			
					++it;
			}
		}	

	}



	Garbage* CollectGarbage_Array(VECOTRSTACKSTATEPOINTER p,GcState* gc)
	{
		Garbage *g =new Garbage(p);
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=sizeof(Garbage);
		GCSSTATEGARBAGECOLLECT(gc)->push_back(g);
		return g;
	}


	Garbage* CollectGarbage_Dict(map<hashValue,StackState>* p,GcState* gc)
	{
		Garbage *g =new Garbage(p);
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=sizeof(Garbage);
		GCSSTATEGARBAGECOLLECT(gc)->push_back(g);
		return g;
	}

	Garbage* CollectGarbage_String(char* p,GcState* gc,ValueType v)
	{
		Garbage *g =new Garbage(p,v);
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=sizeof(Garbage);
		GCSSTATEGARBAGECOLLECT(gc)->push_back(g);
		return g;
	}




	Garbage* CreateString(char* str,VmState* vmstate)
	{

		size_t len = strlen(str)+1;
		char* _p = (char*)malloc(len);
		if(!_p){
			MError::CreateInstance()->PrintRunTimeError("Failed to create string",vmstate);
			return 0;
		}
		char* sss = (char*)_p;
		strcpy(sss,str);
		sss[len-1]='\0';
		
		GcState* gc = vmstate->gc;
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=len;
		return CollectGarbage_String(sss,gc);
	}



	Garbage* CreateNullString(size_t len,VmState* vmstate)
	{
		char* _p =(char*)malloc(len+1);
		if(!_p){
			MError::CreateInstance()->PrintRunTimeError("Failed to create string",vmstate);
			return 0;
		}
		GcState* gc = vmstate->gc;
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=len+1;
		return CollectGarbage_String(_p,gc);
	}


	Garbage* CreateArray(GcState* gc)
	{
		VECOTRSTACKSTATEPOINTER ar =new VECOTRSTACKSTATE();
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=sizeof(VECOTRSTACKSTATE);
		return CollectGarbage_Array(ar,gc);
	}

	Garbage* CreateDict(GcState* gc)
	{
		map<hashValue,StackState>* ma =new map<hashValue,StackState>();
		GCSSTATEGARBAGEMEMORYSIZE(gc)+=sizeof(map<hashValue,StackState>);
		return CollectGarbage_Dict(ma,gc);
	}

	void MarkArray(VECOTRSTACKSTATEPOINTER arr){

		/*for (std::vector<StackState>::iterator it = arr->begin() ; it != arr->end();++it)
		{	*/
		VECTORFORSTART(StackState,arr,it)
			if((*it).v==M_ARRAY){
					MarkGarbage((*it).parray,1);
					MarkArray((VECOTRSTACKSTATEPOINTER)(*it).parray->array);			
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
				MarkArray((VECOTRSTACKSTATEPOINTER)(*it).second.parray->array);	
			}
		}
	}

}