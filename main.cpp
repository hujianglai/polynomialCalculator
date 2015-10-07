/*******************************************************
* COMP2012 - 2015/16 Fall
* Programming Assignment 1
* A simple calculator for polynomials with two variables
* File: main.cpp
*******************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "Polynomial.h"

using namespace std;

int main(void)
{
	/* initialize the polynomial linked lists */
	PolyNode *a = nullptr, *b = nullptr, *c = nullptr, *d = nullptr, *e = nullptr;

	cout << " ============================================================================" << endl;
	cout << "  COMP2012 (Fall 2015) " << endl;
	cout << "  Assignment 1: a simple calculator for polynomials with two variables " << endl;
	cout << "  Operations:" << endl;
	cout << "    'q' for quit" << endl;
	cout << "    'i' for entering two polynomials, a & b" << endl;
	cout << "    'p' for printing the two polynomials in sorted order" << endl;
	cout << "    'r' for printing the two polynomials in reverse order" << endl;
	cout << "    'e' for evaluating the two polynomials at give values of x and y" << endl;
	cout << "    'a' for adding the two polynomials (a+b) " << endl;
	cout << "    's' for subtracting the polynomial b from the polynomial a (a-b)" << endl;
	cout << "    'm' for multiplying the two polynomials (a*b)" << endl;
	cout << " ============================================================================" << endl << endl;

	string cmd = "";
	while (cmd != "q") /* exit the program */
	{
		cout << ">>> Menu: q:quit, i:input, p:print, r:reversely print, e:evaluate, a:add, s:subtract, m:multiply" << endl;
		cout << ">>> Command: ";
		getline(cin, cmd);

		cout << endl;
		if (cmd == "i") /* read the polynomials */
		{
			string polyString1, polyString2;

			cout << "Input the polynomials in sorted order ..." << endl;
			cout << "Input the first polynomial, a : ";
			cin >> polyString1;

			if (!isEmpty(a))
				erase(a);
			a = readPoly(polyString1.c_str());

			cout << "Input the second polynomial, b : ";
			cin >> polyString2;
			if (!isEmpty(b))
				erase(b);
			b = readPoly(polyString2.c_str());
			cin.ignore();

		}
		else if (cmd == "p") /* print the polynomials to screen */
		{
			cout << "Print the polynomials in sorted order ..." << endl;
			cout << "The first polynomial, a = ";
			if (!isEmpty(a))
				printPoly(a);
			else
				cout << "0" << endl;
			cout << "The second polynomial, b = ";
			if (!isEmpty(b))
				printPoly(b);
			else
				cout << "0" << endl;
		}
		else if (cmd == "r") /* print the polynomials in reverse order */
		{
			cout << "Print the polynomials in reverse order ..." << endl;
			cout << "The first polynomial, a = ";
			if (!isEmpty(a))
				printPolyReverse(a);
			else
				cout << "0" << endl;
			cout << "The first polynomial, b = ";
			if (!isEmpty(b))
				printPolyReverse(b);
			else
				cout << "0" << endl;
		}
		else if (cmd == "e") /* evaluate the polynomials */
		{
			cout << "Evaluate the polynomials ..." << endl;
			int x = 0, y = 0;
			cout << "Input the value for x: ";
			cin >> x;
			cout << "Input the value for y: ";
			cin >> y;
			cout << "a(" << x << "," << y << ") = " << eval(a, x, y) << endl;
			cout << "b(" << x << "," << y << ") = " << eval(b, x, y) << endl;
			cin.ignore();
		}
		else if (cmd == "a") /* add the two polynomials */
		{
			cout << "a + b = ";
			c = padd(a, b);
			printPoly(c);
		}
		else if (cmd == "s") /* subtract the polynomial b from a */
		{
			cout << "a - b = ";
			d = psubtract(a, b);
			printPoly(d);
		}
		else if (cmd == "m") /* multiply the two polynomials */
		{
			cout << "a * b = ";
			e = pmult(a, b);
			printPoly(e);
		}

		cout << endl << endl;
	}
	printPoly(a);

	/* erase all the polynomials */
	if (!isEmpty(a))
		erase(a);
	if (!isEmpty(b))
		erase(b);
	if (!isEmpty(c))
		erase(c);
	if (!isEmpty(d))
		erase(d);
	if (!isEmpty(e))
		erase(e);

	return (0);

}

