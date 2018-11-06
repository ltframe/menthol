#include "stdafx.h"
#include "Menthol.h"
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
	bool debug  = false;
	SetPrintCompileErrorFunc(error);
	for(int i=1;i<argc;i++){
		if (argv[i][0] == '-' && argv[i][1] =='d') {
			 debug = true;
		}else
		{
			int c = Compile(argv[i],debug);
			if(!c){
				printf("%s,compile done\r\n",argv[i]);
			}
			else{
				printf("%s,compile error\r\n",argv[i]);
			}
		}
	}
	return 0;
}