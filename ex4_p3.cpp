/* ex4_p3.cpp
 * By:		Carl Vaughan Schmidt
 * Date:	January 26, 2014
 * Purpose:	CS161 Winter 2014
 *			Exercise Set 4, Problem #3
 *			Programming project 3.1 from book p. 138
 *
 *			Write a program that will read in the number of liters
 *			of gasoline consumed by car and miles traveled, and output
 *			the mpg.  Use global constant for liters to gallon factor.
 *			Allow user to repeat as often as desired.
 */

 #include <iostream>
 
 #define CLEAR   "\033[2J"       /* Screen Clear Code */

 using namespace std;

 const float gpl = 0.264179;
 bool repeat = true;
 float liters, miles;
 char reply;

 //declare functions
 float calc_mpg(float, float);

 int main() {

 	cout << CLEAR;
 	while(repeat) {
 		cout << "Vehicle liters & miles to MPG calculation.\n";
 		cout << "Enter liters of gasoline used: ";
 		cin >> liters;
 		cout << "Enter the miles driven: ";
 		cin >> miles;
 		cout << "Your vehicle achieved " ;
 		cout << calc_mpg(liters, miles) << " MPG \n";
 		cout << "\nEnter Q to Quit or C to continue...\n";
 		cout << "==> ";
 		cin >> reply;
 		if(reply == 'Q' || reply == 'q') {
 			repeat = false;
 		} else {
 			repeat = true;
 		}
 	}
 }

 // Function calc_mpg - calculates Miles per Gallon based on liters and 
 // miles.
 float calc_mpg(float liters, float miles) {
 	return miles / liters / gpl;
 }