/*
This driver file was provided by Professor Duan of 
the Florida State Computer Science department for
standardization and therefore will retain its
provided name.

The bet.h and bet.cpp files were written and created
by Michael Borsellino to fulfil the following functions:

Project Description:
This is an excersize in building and utilizing tree containers
to be able to sort through information quickly and effectively.
In this case, the primary goal is to take a postfix mathematical
expression and print it out as an equivalent infix expression.
Project Specifics:
- Must be able to handle bad data entry.
- Must be able to accept functions via space separated operators/operands.
- Must print out parenthesis to maintain correct solved value
*/

#include <iostream>
#include <string>
#include "bet.h"

using namespace std;

int main() {
    string postfix;

    // get a postfix expression
    cout << "Enter the first postfix expression: ";
    getline(cin, postfix);

    // create a binary expression tree
    BET bet1(postfix);
    if (!bet1.empty()) {
    	cout << "Infix expression: ";
    	bet1.printInfixExpression();

	cout << "Postfix expression: ";
	bet1.printPostfixExpression();

	cout << "Number of nodes: ";
	cout << bet1.size() << endl;

	cout << "Number of leaf nodes: ";
	cout << bet1.leaf_nodes() << endl;

    	// test copy constructor
    	BET bet2(bet1);
    	cout << "Testing copy constructor: ";
    	bet2.printInfixExpression();

    	// test assignment operator
    	BET bet3;
    	bet3 = bet1;
    	cout << "Testing assignment operator: ";
    	bet3.printInfixExpression();
    }

    cout << "Enter a postfix expression (or \"quit\" to quit): ";
    while (getline(cin, postfix)) {
	if (postfix == "quit") {
	    break;
        }
	if (bet1.buildFromPostfix(postfix)) {
	    cout << "Infix expression: ";
	    bet1.printInfixExpression();
	    
	    cout << "Postfix expression: ";
	    bet1.printPostfixExpression();
		
	    cout << "Number of nodes: ";
	    cout << bet1.size() << endl;

	    cout << "Number of leaf nodes: ";
	    cout << bet1.leaf_nodes() << endl;
	}
	cout << "Enter a postfix expression (or \"quit\" to quit): ";
    }
    return 0;
}
