#include "stdafx.h"
#include "Console.h"

namespace Console
{
	StackState Out(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.v=M_NULL;
		if(value.v==M_NUMBER){
			if(value.d != (int)value.d){
				printf("%.6lf\n",value.d);
			}
			else{
				printf("%d\n",(int)value.d);
			}	
			return st;
		}
		if(value.v==M_STRING){	
			//cout<<value.str->string<<endl;
			printf("%s\n",value.str->string);
			return st;
		}
		if(value.v==M_BOOL){
			cout<<(value.b?"true":"false")<<endl;
			return st;
		}
		if(value.v==M_NULL){
			cout<<"NULL"<<endl;
			return st;
		}
		if(value.v==M_ARRAY){
			cout<<"{Array Object}"<<endl;
			return st;
		}
		if(value.v==M_DICT){
			cout<<"{Dictionary Object}"<<endl;
			return st;
		}
		if(value.v==M_FUN){
			cout<<"{Function Object}"<<endl;
			return st;
		}
		if (value.v == M_MMRT) {
			cout << "{M_MMRT Object}" << endl;
			return st;
		}
		cout<<"{Object}"<<endl;
		return st;
	}

	std::string replaceformat(std::string str, VmState* vmstate)
	{
		size_t start_pos = 0;
		string from = "%";
		int i = 2;
		while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
			StackState value = GetParam(i, vmstate);
			string to = string(value.str->string);
			str.replace(start_pos, from.length(), to);
			start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
			i++;
		}
		return str;
	}

	StackState OutFormat(VmState* vmstate) 
	{		

		StackState value = GetParam(1, vmstate);
		StackState st = String_CreateString(const_cast<char*>(replaceformat(string(value.str->string), vmstate).c_str()), vmstate);
		printf("%s\n", st.str->string);
		StackState rst;
		rst.v = M_NULL;
		return rst;
	}

	StackState Oute(VmState* vmstate)
	{
		StackState value =GetParam(1,vmstate);
		StackState st;
		st.v=M_NULL;
		if(value.v==M_NUMBER){
			if(value.d != (int)value.d){
				printf("%.6lf",value.d);
			}
			else{
				printf("%d",(int)value.d);
			}	
			return st;
		}
		if(value.v==M_STRING){	
			//cout<<value.str->string<<endl;
			printf("%s",value.str->string);
			return st;
		}
		if(value.v==M_BOOL){
			printf("%s",(value.b?"true":"false"));
			return st;
		}
		if(value.v==M_NULL){
			printf("NULL");
			return st;
		}
		if(value.v==M_ARRAY){
			printf("{Array Object}");
			return st;
		}
		if(value.v==M_DICT)
		{	printf("{Dictionary Object}");
			return st;
		}
		if(value.v==M_FUN){
			printf("{Function Object}");
			return st;
		}
		printf("{Object}");
		return st;
	}


	StackState In(VmState* vmstate)
	{
		string str;
		cin>>str;
		StackState st= String_CreateString(const_cast<char*>(str.c_str()),vmstate);
		return st;
	}


	StackState Clear(VmState* vmstate)
	{
		system("cls");
		StackState st;
		st.v = M_NULL;
		return st;
	}
}