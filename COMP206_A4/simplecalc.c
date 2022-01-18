/* 
 * program to implement simplecalc  
 *******************************************************
 * author       department      date    notes
 ******************************************************* 
 * Dina Shoham  Software Eng    Feb 19  initial version 
 * Dina Shoham  Software Eng    Feb 20  fixing errors 
 */


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){ 
	if (argc != 4){ //checking args 
		printf("Error: usage is simplecalc <x> <op> <y> \n");
		return 1;
	}
	
	//initializing vars 
	int x = atoi(argv[1]);
	int y = atoi(argv[3]);
	char op = *argv[2]; 

	//switch statement for diff operators  
	switch(op)
       	{
		case '+':
			printf("%d \n",x+y);
			break;
	      	case '-':
			printf("%d \n",x-y);
			break;
		case '*':
			printf("%d \n",x*y);
			break;
		case '/':
			printf("%d \n",x/y);
			break;
		default:
       			printf("%c is not a valid operator\n", op);
			return 2;
	}
	return 0;
}

