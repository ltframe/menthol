// MIo.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "Menthol.h"
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include  <direct.h>  
#include <list>
#include <stdarg.h>
#include <sstream>
#include <time.h>
#include <functional>
using namespace std;


StackState Out()
{
	StackState value =GetParam(1);
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
	cout<<"{Object}"<<endl;
	return st;
}

StackState Oute()
{
	StackState value =GetParam(1);
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


StackState In()
{
	string str;
	cin>>str;
	StackState st= String_CreateString(const_cast<char*>(str.c_str()));
	return st;
}

StackState Readfile()
{
	
	StackState value =GetParam(1);
	ifstream t(value.str->string);  
	string str((istreambuf_iterator<char>(t)),istreambuf_iterator<char>()); 
	StackState st=String_CreateString(const_cast<char*>(str.c_str()));
	return st;
}


StackState Writefile()
{
	StackState value1 =GetParam(1);
	StackState value2 =GetParam(2);
	ofstream OutFile(value1.str->string);
	OutFile << value2.str << endl;
    OutFile.close();
	StackState st;
	st.b=true;
	st.v = M_BOOL;
	return st;
}




MentholPackMethod void MP_Init()
{
	RegisterPackAgeFunciton("Oute",Oute,1);	
	RegisterPackAgeFunciton("Out",Out,1);	
	RegisterPackAgeFunciton("In",In,0);	
	RegisterPackAgeFunciton("Readfile",Readfile,1);	
	RegisterPackAgeFunciton("Writefile",Writefile,2);
}