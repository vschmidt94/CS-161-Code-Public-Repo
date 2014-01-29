/* Program: 	ex4_p5.cpp
 * By:			Carl Vaughan Schmidt
 * Date:		2014.01.27
 * For:			CS161 Winter 2014
 *              Exercise Set 4 - Problem 5
 *              Programming project 3.13 from text.
 *
 * You have four identical prizes to give away and a pool 
 * of 25 finalists. The finalists are assigned numbers 
 * from 1 to 25. Write a program to randomly select the 
 * numbers of 4 finalists to receive a prize. 
 * Make sure not to pick the same number twice. 
 * For example, picking finalists 3, 15, 22, and 14 
 * would be valid but picking 3, 3, 31, and 17 would be invalid, 
 * because finalist number 3 is listed twice and 31 is not a 
 * valid finalist number..
 */

 #include <iostream>
 #include <cstdlib>
 #include <array>
 #include <string>


 using namespace std;

 int main() {

 	const int FINALIST_COUNT = 25;
 	const int MAX_WINNERS = 4;
 	bool play_again = true;

 	do {
	 	int winners[MAX_WINNERS];
	 	int winner;
	 	int count = 0;
	 	string reply;  // user's input to run program again or quit

	 	// declare function prototypes
	 	bool in_array(int winner, int winners[], int MAX_WINNERS);

	 	// seed random
	 	srand(time(NULL));
	 	
	 	while(count < MAX_WINNERS) {
	 		winner = rand() % (FINALIST_COUNT + 1);
	 		if(!in_array(winner, winners, MAX_WINNERS)) {
	 			winners[count] = winner;
	 			count++;
	 			cout << "Congratulations, Contestant #" << winner
	 			     << " is one of the final " << MAX_WINNERS
	 			     << " winners! " << endl;
	 		}	
	 	}

	 	cout << endl << "------------------------------ \n";
	 	cout << "Enter Q to quit or any other to run again...";
	 	getline(cin, reply);
	 	if(reply[0] == 'Q' || reply[0] == 'q') {
	 		play_again = false;
	 	}
	 	
	 } while (play_again == true);


 	return 0;
 }

 // Function in_array() returns true if the random winner number has
 // already been picked in current batch of winners, otherwise
 // returns false.
 bool in_array(int winner, int winners[], int array_length) {
 	bool found = false;
 	for(int i = 0; i < array_length; i++) {
 		// cout << "in in_array function for() loop i = " << i << endl;
 		if(winner == winners[i]) {
 			found = true;
 		}
 	}
 	return found;
 }