/*******************************************************
* COMP2012 - 2015/16 Fall
* Programming Assignment 1
* File: Polynomial.cpp
*******************************************************/
/*
Name: BAI Chunyan
Student ID: 20253689
*/
#include <string>
#include <iostream>
#include <regex>

#include "Polynomial.h"

using namespace std;

/* if Polynomial a is empty, retrun true, else false */
bool isEmpty(PolyNode* a)
{
       
  if(a == NULL){
    return true;
  }
  return false;
}

/* erase a Polynomial pointed by ptr and deallocate the nodes */
void erase(PolyNode* ptr)
{
  PolyNode* del = ptr;
  while(del != NULL) {
	  ptr = ptr->next;
	  delete del;
	  del = ptr;
  }
  ptr = NULL;
}

PolyNode* addTerm(PolyNode* front, string str)
{
	PolyNode* newTerm = new PolyNode;

	regex reg_x("x(\\^\\d+)?");
	regex reg_y("y(\\^\\d+)?");
	regex reg_d("[-]?\\d+");
	regex_iterator<string::iterator> iter_x(str.begin(), str.end(), reg_x);
	regex_iterator<string::iterator> iter_y(str.begin(), str.end(), reg_y);
	regex_iterator<string::iterator> end;

	if (iter_x == end)
	{
		newTerm->expx = 0;
	}
	else
	{
		newTerm->expx = 1;
		string part_x = iter_x->str();
		regex_iterator<string::iterator> iter_d(part_x.begin(), part_x.end(), reg_d);
		if (iter_d != end)
		{
			newTerm->expx = atoi(iter_d->str().c_str());
		}
	}

	if (iter_y == end)
	{
		newTerm->expy = 0;
	}
	else
	{
		newTerm->expy = 1;
		string part_y = iter_y->str();
		regex_iterator<string::iterator> iter_d(part_y.begin(), part_y.end(), reg_d);
		if (iter_d != end)
		{
			newTerm->expy = atoi(iter_d->str().c_str());
		}
	}

	str = regex_replace(str, reg_x, "");
	str = regex_replace(str, reg_y, "");
	regex_iterator<string::iterator> iter_d(str.begin(), str.end(), reg_d);
	if (iter_d == end)
	{
		if (str.find('-') != string::npos)
			newTerm->coef = -1;
		else
			newTerm->coef = 1;
	}
	else
	{
		newTerm->coef = atoi(iter_d->str().c_str());
	}

	newTerm->prev = nullptr;
	newTerm->next = front;
	if (front != nullptr)
		front->prev = newTerm;

	return newTerm;
}

/* read and create a Polynomial from a string*/
PolyNode* readPoly(string str)
{
	//empty input
	if (str.length() == 0)
	{
		return nullptr;
	}

	PolyNode* front = nullptr;

	regex two("[+-]?\\d*x(\\^\\d+)?y(\\^\\d+)?");
	regex one("[+-]?\\d*((x(\\^\\d+)?)|(y(\\^\\d+)?))");
	regex_iterator<string::iterator> iter_two(str.begin(), str.end(), two);
	regex_iterator<string::iterator> end;

	while (iter_two != end)
	{
		front = addTerm(front, iter_two->str());
		iter_two++;
	}

	str = regex_replace(str, two, "");
	std::regex_iterator<string::iterator> iter_one(str.begin(), str.end(), one);

	while (iter_one != end)
	{
		front = addTerm(front, iter_one->str());
		iter_one++;
	}

	str = regex_replace(str, one, "");
	if (str != "")
		front = addTerm(front, str);

	return front;
}

/* print the Polynomial a in decreasing order of exponent */
void printPoly(PolyNode* a) {
	
	PolyNode* head = a;
	sortPoly(head);
	string output(PolyNode*);
	while (head != NULL) {
		if (head->prev == NULL) {
			cout << output(head);
			if (output(head) == "0") {
				head = head->next;
				continue;
			}
			head = head->next;
			if (head != NULL) {
				if (output(head)[0] == '-' || output(head->prev) == "" || output(head) == "") {
					continue;
				}
				else {
					cout << "+";
					continue;
				}
			}
			else {
				cout << endl;
				break;
			}
		}
		else {
			if (output(head) == "0") {
				head = head->next;
				continue;
			}
			if (head->next == NULL) {
				cout << output(head) << endl;
				break;
			}
			else {
				if (output(head->next)[0] == '-' || output(head) == "" || output(head->next) == "") {
					cout << output(head);
					head = head->next;
					continue;
				}
				else {
					cout << output(head);
					cout << "+";
					head = head->next;
					continue;
				}
			}
		}
	}

}
string output(PolyNode* head) {
	string output = "";
	if (head->coef == 0 && (head->prev != NULL || head->next != NULL)) {
		output = "";
		return output;
	}
	else if (head->coef == 0 && head->prev == NULL && head->next == NULL) {
		output = "0";
		return output;
	}
	else if (head->coef == 1 && (head->expx != NULL || head->expy != NULL)) {
		output += "";
	}
	else if (head->coef == -1 && (head->expx != NULL || head->expy != NULL)) {
		output += "-";
	}
	else {
		output += to_string(head->coef);
	}
	if (head->expx == 0) {
		output += "";
	}
	else if (head->expx == 1) {
		output += "x";
	}
	else {
		output += "x^";
		string temp = to_string(head->expx);
		output += temp;
	}
	if (head->expy == 0) {
		output += "";
	}
	else if (head->expy == 1) {
		output += "y";
	}
	else {
		output += "y^";
		string temp = to_string(head->expy);
		output += temp;
	}
	return output;
}

/* Sort the polynomial a in decreasing order of exponent and combine terms with same exponent of x and y */
void sortPoly(PolyNode* a) {
	PolyNode* temphead = a; 

	for (; temphead != NULL; temphead = temphead->next) {
		PolyNode* temp = temphead->next;
		while(temp != NULL) {
			if (temphead->expx == temp->expx && temphead->expy == temp->expy) {
				temphead->coef = temphead->coef + temp->coef;
				if (temp->next != NULL) {
					temp->prev->next = temp->next;
					temp->next->prev = temp->prev;
					PolyNode* cur = temp;
					temp = temp->next;
					delete cur;
					cur = NULL;
					continue;
				}
				else {
					temp->prev->next = NULL;
					delete temp;
					temp = NULL;
					continue;
				}

				
			}
			else if (temphead->expx + temphead->expy < temp->expx + temp->expy) {
				int coef = temphead->coef;
				int expx = temphead->expx;
				int expy = temphead->expy;
				temphead->coef = temp->coef;
				temphead->expx = temp->expx;
				temphead->expy = temp->expy;
				temp->coef = coef;
				temp->expx = expx;
				temp->expy = expy;
				temp = temp->next;
				continue;
			}
			else if (temphead->expx + temphead->expy == temp->expx + temp->expy) {
				if (temphead->expx >= temp->expx) {
					temp = temp->next;
					continue;
				}
				else {
					int coef = temphead->coef;
					int expx = temphead->expx;
					int expy = temphead->expy;
					temphead->coef = temp->coef;
					temphead->expx = temp->expx;
					temphead->expy = temp->expy;
					temp->coef = coef;
					temp->expx = expx;
					temp->expy = expy;
					temp = temp->next;
					continue;
				}
				
			}
			else {
				temp = temp->next;
				continue;
			}
		}
	}


}

/* print the Polynomial a in ascending order of exponent */
void printPolyReverse(PolyNode* a) {
  PolyNode* head = a;
  sortPoly(head);
  for(; head->next != NULL; head = head->next){
  }
  string output(PolyNode*);
  while (head != NULL) {
	  if (head->next == NULL) {
		  cout << output(head);
		  if (output(head) == "0") {
			  head = head->prev;
			  continue;
		  }
		  head = head->prev;
		  if (head != NULL) {
			  if (output(head)[0] == '-' || output(head->next) == "") {
				  continue;
			  }
			  else {
				  cout << "+";
				  continue;
			  }
		  }
		  else {
			  cout << endl;
			  break;
		  }
	  }
	  else {
		  if (head->prev == NULL) {
			  cout << output(head) << endl;
			  break;
		  }
		  else {
			  if (output(head->prev)[0] == '-' || output(head->prev) == "") {
				  cout << output(head);
				  head = head->prev;
				  continue;
			  }
			  else {
				  cout << output(head);
				  cout << "+";
				  head = head->prev;
				  continue;
			  }
		  }
	  }
  }

  
 
}

/* evaluate the Polynomial a at value of x, y */
long eval(PolyNode* a, int x, int y)
{
  long sum = 0;
  
  PolyNode* head = a;
  for(; head != NULL; head = head->next) {
	  long powx = 1;
	  long powy = 1;
    for(int i = 0; i != head->expx; i++) {
      powx *= x;
    }
    for(int j = 0; j != head->expy; j++) {
      powy *= y;
    }
	if (head->expx == 0) {
		powx = 1;
	}
	if (head->expy == 0) {
		powy = 1;
	}
    sum += head->coef * powx * powy;
  }
  return sum;
    
}

/* add two PolyNode*amials, a & b, and return the sum in a third Polynomial*/
PolyNode* padd(PolyNode* a, PolyNode* b)
{
	PolyNode* c = new PolyNode;
	c->coef = c->expx = c->expy = 0;
	c->prev = c->next = NULL;
	PolyNode* heada = a;
	PolyNode* headb = b;
	//c = a + b
	while(heada != NULL && headb != NULL) {
		
		if(heada->expx == headb->expx && heada->expy == headb->expy) {
	  	
			c->coef = heada->coef + headb->coef;
			c->expx = heada->expx;
			c->expy = heada->expy;
			if (heada->next == NULL || headb->next == NULL) {
				heada = heada->next;
				headb = headb->next;
				break;
			}
			else {
				c->next = new PolyNode;
				c->next->coef = c->next->expx = c->next->expy = 0;
				c->next->prev = c;
				c->next->next = NULL;
			}
		}
		else{
			c->next = new PolyNode;
			c->next->coef = c->next->expx = c->next->expy = 0;
			c->next->prev = c;
			c->next->next = NULL;
			c->coef = heada->coef;
			c->expx = heada->expx;
			c->expy = heada->expy;
			c->next->coef = headb->coef;
			c->next->expx = headb->expx;
			c->next->expy = headb->expy;
			if (heada ->next == NULL || headb->next == NULL) {
				c = c->next;
				heada = heada->next;
				headb = headb->next;
				break;
			}
			else {
				c = c->next;
				c->next = new PolyNode;
				
				c->next->coef = c->next->expx = c->next->expy = 0;
				c->next->prev = c;
				c->next->next = NULL;
				
			}
			
		}
		c = c->next;
		heada = heada->next;
		headb = headb->next;
		
	}
	if (heada == NULL && headb != NULL) {
		while (headb != NULL) {
			c->next = new PolyNode;
			c->next->coef = c->next->expx = c->next->expy = 0;
			c->next->prev = c;
			c->next->next = NULL;
			c = c->next;
			c->coef = headb->coef;
			c->expx = headb->expx;
			c->expy = headb->expy;
			headb = headb->next;
		}
	}
	else if (heada != NULL && headb == NULL) {
		while (heada != NULL) {
			c->next = new PolyNode;
			c->next->coef = c->next->expx = c->next->expy = 0;
			c->next->prev = c;
			c->next->next = NULL;
			c = c->next;
			c->coef = heada->coef;
			c->expx = heada->expx;
			c->expy = heada->expy;
			heada = heada->next;
		}
	}
	for (; c->prev != NULL; c = c->prev) {
	}
	sortPoly(c);
	return c;
}
/* subtract Polynomial b from Polynomial a, return the result in a third Polynomial */
PolyNode* psubtract(PolyNode* a, PolyNode* b)
{
	PolyNode* c = new PolyNode;
	c->coef = c->expx = c->expy = 0;
	c->prev = c->next = NULL;
	PolyNode* heada = a;
	PolyNode* headb = b;
	//c = a - b
	while (heada != NULL && headb != NULL) {

		if (heada->expx == headb->expx && heada->expy == headb->expy) {

			c->coef = heada->coef - headb->coef;
			c->expx = heada->expx;
			c->expy = heada->expy;
			if (heada->next == NULL || headb->next == NULL) {
				heada = heada->next;
				headb = headb->next;
				break;
			}
			else {
				c->next = new PolyNode;
				c->next->coef = c->next->expx = c->next->expy = 0;
				c->next->prev = c;
				c->next->next = NULL;
			}
		}
		else {
			c->next = new PolyNode;
			c->next->coef = c->next->expx = c->next->expy = 0;
			c->next->prev = c;
			c->next->next = NULL;
			c->coef = heada->coef;
			c->expx = heada->expx;
			c->expy = heada->expy;
			c->next->coef = -1 * headb->coef;
			c->next->expx = headb->expx;
			c->next->expy = headb->expy;
			if (heada->next == NULL || headb->next == NULL) {
				c = c->next;
				heada = heada->next;
				headb = headb->next;
				break;
			}
			else {
				c = c->next;
				c->next = new PolyNode;

				c->next->coef = c->next->expx = c->next->expy = 0;
				c->next->prev = c;
				c->next->next = NULL;

			}

		}
		c = c->next;
		heada = heada->next;
		headb = headb->next;

	}
	if (heada == NULL && headb != NULL) {
		while (headb != NULL) {
			c->next = new PolyNode;
			c->next->coef = c->next->expx = c->next->expy = 0;
			c->next->prev = c;
			c->next->next = NULL;
			c = c->next;
			c->coef = -1 * headb->coef;
			c->expx = headb->expx;
			c->expy = headb->expy;
			headb = headb->next;
		}
	}
	else if (heada != NULL && headb == NULL) {
		while (heada != NULL) {
			c->next = new PolyNode;
			c->next->coef = c->next->expx = c->next->expy = 0;
			c->next->prev = c;
			c->next->next = NULL;
			c = c->next;
			c->coef = heada->coef;
			c->expx = heada->expx;
			c->expy = heada->expy;
			heada = heada->next;
		}
	}
	for (; c->prev != NULL; c = c->prev) {
	}
	sortPoly(c);
	return c;
}

/* multiply Polynomial a with Polynomial b and return the result in a third Polynomial */
PolyNode* pmult(PolyNode* a, PolyNode* b)
{
	PolyNode* c = new PolyNode;
	c->coef = c->expx = c->expy = 0;
	c->prev = c->next = NULL;
	PolyNode* heada = a;
	PolyNode* headb = b;
	//c = a * b
	while(heada != NULL) {
		headb = b;
		while(headb != NULL) {
			if (heada->next == NULL && headb->next == NULL) {
				c->coef = heada->coef * headb->coef;
				c->expx = heada->expx + headb->expx;
				c->expy = heada->expy + headb->expy;
				headb = headb->next;
			}
			else {
				c->next = new PolyNode;
				c->next->coef = c->next->expx = c->next->expy = 0;
				c->next->prev = c;
				c->next->next = NULL;
				c->coef = heada->coef * headb->coef;
				c->expx = heada->expx + headb->expx;
				c->expy = heada->expy + headb->expy;
				c = c->next;
				headb = headb->next;
			}
		}
		heada = heada->next;
	}
	for (; c->prev != NULL; c = c->prev) {
	}
	sortPoly(c);
	return c;
}
