#include "stdafx.h"
#include "../Menthol/MentholHeader.h"
#include <stdlib.h>  


int error(char* str,char* cf,int line)
{
	printf("\r\n");
	printf("compile error: %s, in %s,at line %d",str,cf,line);
	printf("\r\n");
	return 1;
}
int main(int argc, char * argv[])
{
	SetPrintCompileErrorFunc(error);
	int c = Compile(argv[1]);
	if (!c) {
		printf("%s,compile done\r\n", argv[1]);
	}
	else {
		printf("%s,compile error\r\n", argv[1]);
	}
	return 0;
}