/*
COMP 206 MINI A6 

author: Dina Shoham 
department: U1 Software Engineering 
purpose: main method of polynomial evaluation app 
         parses text file with coeffs and exponents then calls functions to evaluate and display polynomial  

history: 
***************************************************
date    * changes  
apr 11  * initial code 
***************************************************

*/ 

#include <stdio.h> 
#include <stdlib.h>
#include "utils.h"
#include "poly.h"

int main (int argc, char *argv[]) 
{ 
  //input validation - check usage  
  if (argc != 2) 
  { 
    fprintf(stderr, "error! usage: ./polyapp.c datafile.ssv\n"); 
    return 0; 
  } 

  FILE *datafile; 

  //check if text file exists 
  if ( ! (datafile = fopen(argv[1], "r")) ) 
  { 
    fprintf(stderr, "error! %s could not be found\n", argv[1]); 
    return 0; 
  } 

  //reading file line by line and calling parse file on each line 
  char line[128];
  while(fgets(line, sizeof(line), datafile) != NULL)
  {
    int *coeff = malloc(sizeof(int)); 
    int *exp = malloc(sizeof(int)); 
    parse(line, coeff, exp); 
    int result = powi(*coeff, *exp); 
    addPolyTerm(*coeff, *exp);
  }
  
  displayPolynomial();
  int x = -2; 
  evaluatePolynomial(x);
  x = -1; 
  evaluatePolynomial(x);
  x = 0; 
  evaluatePolynomial(x);
  x = 1; 
  evaluatePolynomial(x);
  x = 2; 
  evaluatePolynomial(x);

}
