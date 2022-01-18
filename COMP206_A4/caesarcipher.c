/* 
 * program to implement Caesar's cipher  
 *******************************************************
 * author       department      date    notes
 ******************************************************* 
 * Dina Shoham  Software Eng    Feb 19  initial version 
 * Dina Shoham  Software Eng    Feb 20  fixing errors 
 */


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
	if(argc != 2) { //validating args
		printf("error: usage is caesar cipher <offset>\n");
	     	return 1;
	}
	
	int n = atoi(argv[1]); //initializing shift
	char msg[100];
	char out[100]; 
	int char1; //this char will have to be pushed back onto stdin because the EOF file check uses it 

	while (char1 != EOF) {	
		char1 = getc(stdin); //first char from stdin
		if(char1 == EOF) {break;} //break here so EOF doesn't end loop in the right place 	
		ungetc(char1, stdin); 
		fgets(msg, 100, stdin);	
		for(int i = 0; i < 100; i++) { //loop through msg 
			if(islower(msg[i])) { //if lowercase 
				if(msg[i]+n < 'a') { //if shift before a  
					out[i] = (msg[i]+26+n);	
				}else if(msg[i]+n > 'z') { //if shift after z
					out[i] = (msg[i]-26+n);
				}else { //shift the character normally 
					out[i] = (msg[i]+n); 	
				} 
			}else {
				out[i] = msg[i];
			}	
		}
		printf("%s", out);
	}
	return 0;
}

