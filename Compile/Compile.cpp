#include "stdafx.h"
#include "Menthol.h"
#include <stdlib.h>  
int main(int argc, char * argv[])
{
	for(int i=1;i<argc;i++){
		int c = Compile2(argv[i]);
		if(!c){
			printf("%s,compile done\r\n",argv[i]);
		}
		else{
			printf("%s,compile error\r\n",argv[i]);
		}
	}
	return 0;
}