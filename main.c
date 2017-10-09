
#include <string.h>
#include "keystrokes.h"


int main(){
	keyandData firstIter,checkIter;
	int i=0;
	while(i==0){
		printf("%s\n","Enter password:" );
		firstIter = getInput();
		printf("%s\n","Enter password again:" );
		checkIter = getInput();
		if(strcmp(firstIter.password,checkIter.password)==0){
			printf("password:%s\n", checkIter.password);
			printList(checkIter.diffList);
			printf("\n");
			printList(firstIter.diffList);
			printf("\n");
			i=1;

		}else{
			printf("%s\n","Keys didnt match" );
		}
	}
	return 0;
}