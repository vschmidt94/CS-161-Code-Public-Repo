/* Program:  	ex4_p1_p2.cpp
 * By:			(Carl) Vaughan Schmidt
 * Date:		2014.01.25
 * 
 * Purpose:		Exersize set 4
 *				Problems 1, 2
 */

#include <iostream>
#include <random>
#include <string>

using namespace std;

// declare funtions
int rand_int(int min, int max);
bool compare_string(string s1, string s2);

// main function that will check my functions
int main() {
	// declare variables
	int top_int, bottom_int, random_int;
	string string1, string2;

	// seed the random number
	srand(time(NULL));

	// testing the rand_int function:
	cout << "Testing rand_int() function by producing 10 random ints \n"
	     << "between other random ints \n\n";
	for(int i = 0; i < 10; i++) {
		bottom_int = rand() % 100;
		top_int = rand() % 1000;
		random_int = rand_int(bottom_int, top_int);
		cout << "A random integer between "
		     << bottom_int << " and " << top_int
		     << " is " << random_int << endl;
	}

	cout << "Testing edge cases...\n";
	cout << "A random int between 0 and 0 is: " << rand_int(0,0) << endl;
	cout << "A random int between 0 and 1 is: " << rand_int(0,1) << endl;
	cout << "A random int between -1 and 1 is: " << rand_int(-1,1) << endl;

	// Now testing problem 2, compare_string() function
	cout << endl << endl;
	cout << "Testing Problem #2 - compare_string() function" << endl;
	cout << "Enter string 1: ";
	getline(cin, string1);
	cout << "Enter string 2: ";
	getline(cin, string2);
	if(compare_string(string1, string2)) {
		cout << "Those strings ARE the same... \n";
	} else {
		cout << "Those strings ARE NOT the same... \n";
	}

return 1;
}

 /* Problem # 1
  * Write a simple function that acts like a random number generator
  * with the following behavior:
  * a) its definition looks like: int rand_int(int min, int max);
  * b) it accepts 2 int values (1 for bottom of range and 1 for 
  *    the top of the range) , generates a number within that range 
  *	   and returns the result.
  *
  * NOTE: random number will be: bottom <= rand_int <= top
  *       the possible range is INCLUSIVE of top and bottom arguments.
  */
int rand_int(int bottom, int top) {
	
	if(bottom == top) {
		// if there is no difference between the arguments,
		// return the same number
		return top;
	} else {
		// seed the random number
		// srand(time(NULL));

		if(bottom > top) {
			// the arguments are not entered in correct sequence
			// flip them so top > bottom.
			int hold = top;
			top = bottom;
			bottom = hold; 
		}
		int diff = top - bottom;

		int rand_num = rand() % (diff+1);

		return (rand_num + bottom); 

	}
}

/* Exercise set 4, Problem #2
 * Write a simple function that accepts 2 strings and returns whether they have the same contents.
 */
bool compare_string(string str1, string str2) {
	if(str1 == str2) {
		return true;
	} else {
		return false;
	}
}