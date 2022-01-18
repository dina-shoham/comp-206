/*
COMP 206 MINI A6 

author: Dina Shoham 
department: U1 Software Engineering 
purpose: linked list and associated functions for polyapp.c  

history: 
***************************************************
date    * changes  
apr 11  * initial code 
apr 13  * writing more functions and debugging
***************************************************

*/ 

#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include "utils.h"

//setting up struct for nodes of linked list 
struct PolyTerm 
{ 
  int coeff;
  int exp;
  struct PolyTerm *next;
};

//creating pointer to head of linked list 
struct PolyTerm *head;

//function add new polyterm to front of linked list 
int addPolyTerm (int coeff, int exp) 
{
  struct PolyTerm *newnode = (struct PolyTerm*) malloc(sizeof(struct PolyTerm)); 
  
  if(newnode == NULL) {
    return -1;
  }
  
  //initializing head if it hasn't been initialized yet
  if(head == NULL) {
    head = newnode; 
    newnode->exp = exp;
    newnode->coeff = coeff;
    newnode->next = NULL;
    return 0; 
  }
  
  //add first 
  else if(exp < head->exp) {
    newnode->exp = exp;
    newnode->coeff = coeff;
    newnode->next = head;
    head = newnode;
    return 0;
  }

  //if exp already exists in the list 
  else if(exp == head->exp) {
    head->coeff += coeff;
    return 0;
  }

  //add in the middle or end 
  else {
    struct PolyTerm *tmp = head; 
    //while tmp is not null and exp isn't in the correct slot 
    while(tmp->next != NULL && exp >= tmp->next->exp)
    {
      tmp = tmp->next;
    }
      
    //if exponents are equal combine coeffs
    if(exp == tmp->exp) {
      tmp->coeff += coeff;
      return 0;
    } 
   
    //insert next
    else {
      newnode->exp = exp;
      newnode->coeff = coeff;
      newnode->next = tmp->next; 
      tmp->next = newnode;
      return 0;
    }
  } 
  return 0;
}


//function to display polynomial 
void displayPolynomial () 
{
  char* polynomial[256] ; 

  //traversing linkedlist  
  struct PolyTerm *tmp = head; 
  
  while(tmp != NULL) 
  { 
    if(tmp == head && tmp->coeff > 0) {
      printf("%dx%d", tmp->coeff, tmp->exp);
    }
    else {
      if(tmp->coeff < 0) {
        printf("%dx%d", tmp->coeff, tmp->exp);
      }
      else {
        printf("+%dx%d", tmp->coeff, tmp->exp);
      }
    }
    tmp = tmp->next; 
  }
  printf("\n");
}

//function to evaluate polynomial given x value 
void evaluatePolynomial (int x)
{
  int y = 0;
  struct PolyTerm *tmp = head;
  while(tmp != NULL)
  {
    int term = tmp->coeff * powi(x, tmp->exp);
    y += term; 
    tmp = tmp->next;
  }
  printf("for x=%d, y=%d\n", x, y);
}



