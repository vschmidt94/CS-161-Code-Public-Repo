/* Program: 	ex4_p4.cpp
 * By:			Carl Vaughan Schmidt
 * Date:		2014.01.27
 * For:			CS161 Winter 2014
 *              Exercise Set 4 - Problem 4
 *              Programming project 3.5 from text.
 *
 * Write a program that asks for the user’s height,
 * weight, and age, and then computes clothing sizes
 * according to the following formulas.
 */

 #include <iostream>
 #include <string>

 #define CLEAR "\033[2J"  // clear screen escape code 

 using namespace std;

 //declare functions
 float hat_size(int, int);
 float jacket_size(int, int, int);
 float waist_size(int, int);

 int main() {

 	// declare variables
 	int weight = 0;
 	int height = 0;
 	int age = 0;
 	bool run_program = true;
 	char quit;

 	do {
 		cout << CLEAR;  // clear the screen
 		cout << "Enter your weight (lbs): ";
 		cin >> weight;
 		cout << "Enter your height (inches): ";
 		cin >> height;
 		cout << "Enter your age (years): ";
 		cin >> age;
 		cout << "Based on your data: (weight = " << weight
 			 << ", height = " << height << ", age = " << age << ") \n";
 		cout << "Your hat size is " << hat_size(weight, height) << endl;
 		cout << "Your jacket size is " << jacket_size(weight, height, age)
 		     << endl;
 		cout << "Your waist size is " << waist_size(weight, age) << endl;
 		cout << "ENTER 'Q' TO QUIT OR 'A' TO RUN AGAIN...\n";
 		cout << "==> ";
 		cin >> quit;
 		if(quit == 'Q' || quit == 'q') {
 			run_program = false;
 		}
 	} while(run_program);

 	return 1;
 }

// Function hat_size(int weight, int height) 
// Hat size = weight in pounds divided by height in inches
// and all that multiplied by 2.9.
float hat_size(int weight, int height) {
	return ((float)weight/(float)height)*2.9;
}


// Function jacket_size(int weight, int height, int age) 
// Jacket size (chest in inches) = height times weight
// divided by 288 and then adjusted by adding one-eighth
// of an inch for each 10 years over age 30. 
// (Note that the adjustment only takes place after a 
// full 10 years. So, there is no adjustment for ages 30 
// through 39, but one-eighth of an inch is added for age 40.)
float jacket_size(int weight, int height, int age) {
	float jacket = float(height * weight) / 288.0;
	if(age > 39) {
		int extra_decades = (age - 29) / 10;
		jacket = jacket + extra_decades * 0.125;
	}
	return jacket;
}

// Function waist_size(int weight, int age)
// Waist in inches = weight divided by 5.7 and then adjusted 
// by adding one-tenth of an inch for each 2 years over age 28. 
// (Note that the adjustment only takes place after a full 2 years.
// So, there is no adjustment for age 29, but one-tenth of an 
// inch is added for age 30.)
float waist_size(int weight, int age) {
	float waist = weight / 5.7;
	if(age > 29) {
		int extra_two_years = (age - 28) / 2;
		waist = waist + (extra_two_years * 0.1);
	}
	return waist;
}