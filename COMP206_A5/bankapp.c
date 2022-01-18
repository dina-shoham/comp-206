/*
 * COMP 206 mini assignment 5
 * Author: Dina Shoham
 * Student ID: 260823582
 * Purpose: program to implement a simple banking system application,
 with three functions: adding an account number, making a deposit,
 and making a withdrawal
 * Edit history:
 * *******************************************************************
 * author	date	notes
 * Dina		Mar 11  initial code
 * Dina		Apr 3	debugging and finalizing
 */

#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h> 

//function to parse .csv file and get specified field
const char* getfield(char* line, int num){
	const char* field;
	for (field = strtok(line, ","); field && *field; field = strtok(NULL, ",\n")) {
		if (!--num) {
			return field; 
		}
	}
	return NULL;
}

//function to check if an account exists
int checkAccount(FILE *file, char* acctnum) {
	char line[1024];

	while(fgets(line, 1024, file)) {
		char* tmp = strdup(line);
		
		if(strcmp(getfield(tmp, 1), "AC") == 0 && strcmp(getfield(tmp, 2), acctnum) == 0) { 
			fprintf(stderr, "Error: account number %s already exists\n", acctnum);
			return 50;
		}
		free(tmp);	
	}
	return 0; 
}

//function to get balance from an existing account
int getBalance(FILE *file, char* acctnum) {
	int balance = 0;
	char line[1024];

	while(fgets(line, 1024, file)) {
		char* tmp = strdup(line);
		if(strcmp(getfield(tmp, 1), "TX") == 0 && strcmp(getfield(tmp, 2), acctnum) == 0) { 
			balance += atoi(getfield(tmp, 4));	
		}
		free(tmp);	
	}
	return balance;
}

//function to add a new account
int addAccount(FILE *file, char* acctnum, char* name) {
	//check if account exists
	fprintf(stderr, "checkAccount returns %d\n", checkAccount(file, acctnum));	
	if(checkAccount(file, acctnum) == 0) {
		fprintf(file, "AC,%s,%s\n", acctnum, name);	
	}
	return 0;
}

//function to make a deposit
int newDeposit(FILE *file, char* acctnum, char* date, char* amount) {
	if(checkAccount(file, acctnum) == 0) {
		fprintf(file, "TX,%s,%s,%s\n", acctnum, date, amount); 	
	}
	return 0;
}

//function to make a withdrawal
int newWithdrawal(FILE *file, char* acctnum, char* date, char* amount) {
	if(checkAccount(file, acctnum) == 0) {
		//check if balance is enough to make withdrawal
		int balance = getBalance(file, acctnum);
 		int amtVal = atoi(amount);
		if(amtVal > balance) {
			fprintf(stderr, "Error: account number %s only has %d\n", acctnum, balance);
			return 60;
		}
		fprintf(file, "TX,%s,%s,-%s\n", acctnum, date, amount); 	
	}
	return 0;
}

int main(int argc, char *argv[]) {
	//make sure a switch is included (check for a "-" in arg 1)
	if((int)*argv[1] != '-' || argc < 2 || argc > 5) {
		fprintf(stderr, "Error: incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
		return 1;
	}

	//check if file exists
	if(access("bankdata.csv", F_OK) == -1) {
		fprintf(stderr, "Error: unable to locate the data file bankdata.csv\n");
		return 100;
	} 
	FILE *bankdata = fopen("bankdata.csv", "at");

	//add a new account
	if(argv[1][1] == 'a') {
		//error for wrong num args
		if(argc != 4) {
			fprintf(stderr, "Error: incorrect usage!\n-a ACCTNUM NAME\n");
			return 1;
		}
		addAccount(bankdata, argv[2], argv[3]);
	}

	//make a deposit
	else if(argv[1][1] == 'd') {
		//error for wrong num args
		if(argc != 5) {
			fprintf(stderr, "Error: incorrect usage!\n-d ACCTNUM DATE AMOUNT\n");
			return 1;
		}
		newDeposit(bankdata, argv[2], argv[3], argv[4]);
	}

	//make a withdrawal
	else if(argv[1][1] == 'w') {
		//error for wrong num args
		if(argc != 5) {
			fprintf(stderr, "Error: incorrect usage!\n-w ACCTNUM DATE AMOUNT \n");
			return 1;
		}
		newWithdrawal(bankdata, argv[2], argv[3], argv[4]);
	}

	else {
		fprintf(stderr, "Error: incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
		return 1;
	}
}

