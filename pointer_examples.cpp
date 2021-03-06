/* Program:	pointer_examples.cpp
 * By:		Vaughan Schmidt
 * For:		CS161 - Winter 2014
 *
 * Based on examples in book Absolute C++ (Savitch)
 * Chapter 10.
 */

#include <iostream>

using namespace std;

void printit(int *p1, int *p2);

int main() {

	// declare some pointer variables
	int *p1, *p2;

	// declare some regular variables
	int v1, v2;

	v1 = 123;
	v2 = 246;

	// assign pointers 
	p1 = &v1;
	p2 = &v2;

	// let's print it out:
	printit(p1, p2);

	// assign one pointer to another
	p2 = p1;
	cout << "STATEMENT: p2 = p1, now: " << endl;
	printit(p1, p2);

	// make changes with *p2
	*p2 = 987;
	cout << "STATEMENT: *p2 = 987, now: " << endl;
	printit(p1, p2);

	// look at the * and & operators:
	cout << "Now, I am looking into the * and & operators: \n";
	cout << "The value of *p1: " << *p1 << endl;
	cout << "Should be the same as \n";
	cout << "The value of &v1: " << &v1 << endl;
	cout << "v2 remains equal to the original value: " << v2 << endl;
	cout << "The value of &v2: " << &v2 << endl;
	cout << "----------------------------------\n\n";

	return 0;
}

void printit(int* p1, int* p2) {
	cout << "The value of *p1: " << *p1 << endl;
	cout << "The value of *p2: " << *p2 << endl;
	cout << "The value of p1:  " << p1 << endl;
	cout << "The value of p2:  " << p2 << endl;
	cout << "-------------------------------\n\n";
	return;
}