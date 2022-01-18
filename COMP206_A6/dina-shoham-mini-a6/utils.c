/*
COMP 206 MINI A6 

author: Dina Shoham 
department: U1 Software Engineering 
purpose: util functions for polyapp.c
         one function to parse a string and another to evaluate an exponent  

history: 
***************************************************
date    * changes  
apr 11  * initial code 
***************************************************

*/ 

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

//parse function 
void parse (char* line, int *coeff, int *exp) 
{ 
  char* tok; 

  tok = strtok(line, " "); 
  *coeff = atoi(tok);  

  tok = strtok(NULL, " ");
  *exp = atoi(tok);  
}

//powi function 
int powi (int x, int exp) 
{ 
  int result = 1; 

  for ( int i = 0 ; i < exp ; i++ )
  {
    result = result * x;
  }
  
  return result; 
}

