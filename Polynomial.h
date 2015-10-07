/*******************************************************
* COMP2012 - 2015/16 Fall
* Programming Assignment 1
* A simple calculator for polynomials with two variables
* File: Polynomial.h
*******************************************************/

#ifndef _POLYNOMIAL_H_
#define _POLYNOMIAL_H_

using namespace std;

/* struct definition for polynomial in singly linked list */
struct PolyNode
{
	int coef;
	int expx;
	int expy;
	PolyNode* prev;
	PolyNode* next;
};

/* if polynomial a is empty, retrun true, else false */
bool isEmpty(PolyNode* a);

/* erase a polynomial pointed by ptr and deallocate the nodes */
void erase(PolyNode* ptr);

/* read and create a polynomial from a string*/
PolyNode* readPoly(string str);

/* print the polynomial a in decreasing order of exponent */
void printPoly(PolyNode* a);

/* Sort the polynomial a in decreasing order of exponent and combine terms with same exponent of x and y */
void sortPoly(PolyNode* a);

/* print the polynomial a in ascending order of exponent */
void printPolyReverse(PolyNode* a);

/* Evaluate a polynomial given a particular value of x and y */
long eval(PolyNode* a, int x, int y);

/* add two polynoamials, a & b, and return the sum in a third polynomial*/
PolyNode* padd(PolyNode* a, PolyNode* b);

/* subtract polynomial b from polynomial a, return the result in a third polynomial */
PolyNode* psubtract(PolyNode* a, PolyNode* b);

/* multiply polynomial a with polynomial b and return the result in a third polynomial */
PolyNode* pmult(PolyNode* a, PolyNode* b);

#endif

