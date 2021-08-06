#include "stdafx.h"
#include "DateTime.h"


namespace DateTime
{

	StackState CurrentDate(VmState* vmstate)
	{
		struct tm *local;  
		time_t t;  
		t=time(NULL);  
		local=localtime(&t);  
		StackState st;
		st =Dict_CreateDict(vmstate);
		StackState _y;_y.d = local->tm_year+1900;_y.v = M_NUMBER;
		StackState _m;_m.d = local->tm_mon+1;_m.v = M_NUMBER;
		StackState _d;_d.d = local->tm_mday;_d.v = M_NUMBER;
		Dict_Push("y",st.pdict,_y);
		Dict_Push("m",st.pdict,_m);
		Dict_Push("d",st.pdict,_d);
		return st;
	}

	StackState CurrentTime(VmState* vmstate)
	{

		struct tm *local;  
		time_t t;  
		t=time(NULL);  
		local=localtime(&t);  
		StackState st;
		st =Dict_CreateDict(vmstate);
		StackState _s;_s.d = local->tm_sec;_s.v = M_NUMBER;
		StackState _m;_m.d = local->tm_min;_m.v = M_NUMBER;
		StackState _h; _h.d = local->tm_hour;_h.v = M_NUMBER;
		Dict_Push("s",st.pdict,_s);
		Dict_Push("m",st.pdict,_m);
		Dict_Push("h",st.pdict,_h);
		return st;
	}


	StackState TimeZone(VmState* vmstate)
	{
		StackState st;
		struct tm *local;  
		time_t t;  
		t=time(NULL);  
		local=localtime(&t);  
		st.d = mktime(local);
		st.v = M_NUMBER;
		return st;
	}

	StackState CreateDateDict(tm *local,VmState* vmstate)
	{
		StackState st;
		st = Dict_CreateDict(vmstate);
		StackState _y; _y.d = local->tm_year + 1900; _y.v = M_NUMBER;
		StackState _m; _m.d = local->tm_mon + 1; _m.v = M_NUMBER;
		StackState _d; _d.d = local->tm_mday; _d.v = M_NUMBER;
		StackState _s; _s.d = local->tm_sec; _s.v = M_NUMBER;
		StackState _mi; _mi.d = local->tm_min; _mi.v = M_NUMBER;
		StackState _h; _h.d = local->tm_hour; _h.v = M_NUMBER;

		Dict_Push("y", st.pdict, _y);
		Dict_Push("m", st.pdict, _m);
		Dict_Push("d", st.pdict, _d);
		Dict_Push("h", st.pdict, _h);
		Dict_Push("mi", st.pdict, _mi);
		Dict_Push("s", st.pdict, _s); 
		return st;
		
	}
	time_t StringToDatetime(char* cha)
	{
		tm tm_;                                    
		int year, month, day, hour, minute, second;
		sscanf(cha, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		tm_.tm_year = year - 1900;                
		tm_.tm_mon = month - 1;                   
		tm_.tm_mday = day;                        
		tm_.tm_hour = hour;                       
		tm_.tm_min = minute;                      
		tm_.tm_sec = second;                      
		tm_.tm_isdst = 0;                         
		time_t t_ = mktime(&tm_);                 
		return t_;                                
	}
	StackState AddDays(VmState* vmstate)
	{
		time_t currentdate = StringToDatetime(GetParam(1, vmstate).str->string);
		StackState addday = GetParam(2, vmstate);
		time_t scale = 24 * 3600 * addday.d;
		struct tm *local;
		time_t t;
		t = currentdate + scale;
		local = localtime(&t);
		return CreateDateDict(local,vmstate);
	}
	StackState AddHours(VmState* vmstate)
	{
		time_t currentdate = StringToDatetime(GetParam(1, vmstate).str->string);
		StackState addhour = GetParam(2, vmstate);
		time_t scale = 3600 * addhour.d;
		struct tm *local;
		time_t t;
		t = currentdate + scale;
		local = localtime(&t);
		return CreateDateDict(local, vmstate);
	}
	StackState AddMinutes(VmState* vmstate)
	{
		time_t currentdate = StringToDatetime(GetParam(1, vmstate).str->string);
		StackState addminutes = GetParam(2, vmstate);
		time_t scale = 60 * addminutes.d;
		struct tm *local;
		time_t t;
		t = currentdate + scale;
		local = localtime(&t);
		return CreateDateDict(local, vmstate);
	}
	StackState AddSeconds(VmState* vmstate)
	{
		time_t currentdate = StringToDatetime(GetParam(1, vmstate).str->string);
		StackState addseconds = GetParam(2, vmstate);
		time_t scale = addseconds.d;
		struct tm *local;
		time_t t;
		t = currentdate + scale;
		local = localtime(&t);
		return CreateDateDict(local, vmstate);
	}
	StackState AddYears(VmState* vmstate)
	{
		time_t currentdate = StringToDatetime(GetParam(1, vmstate).str->string);
		StackState addyear = GetParam(2, vmstate);
		struct tm *local;
		local = localtime(&currentdate);

		StackState st;
		st = Dict_CreateDict(vmstate);
		StackState _y; _y.d = local->tm_year + 1900 + addyear.d; _y.v = M_NUMBER;
		StackState _m; _m.d = local->tm_mon + 1; _m.v = M_NUMBER;
		StackState _d; _d.d = local->tm_mday; _d.v = M_NUMBER;
		StackState _s; _s.d = local->tm_sec; _s.v = M_NUMBER;
		StackState _mi; _mi.d = local->tm_min; _mi.v = M_NUMBER;
		StackState _h; _h.d = local->tm_hour; _h.v = M_NUMBER;

		Dict_Push("y", st.pdict, _y);
		Dict_Push("m", st.pdict, _m);
		Dict_Push("d", st.pdict, _d);
		Dict_Push("h", st.pdict, _h);
		Dict_Push("mi", st.pdict, _mi);
		Dict_Push("s", st.pdict, _s);
		return st;
	}
};
