/* Hash Table
 * Author: Nour Yehia
 * Date: 6-2-18
 * This program allows user to add students to a list by cstoring them in a hash table. Additionally, it allows the user to remove students from the list, print the list, and generate a random student.*/

//Include.
#include "table.h"

int main(){

	//Declare variables.
	table table;
	char answer;
	bool running = true;

	cout << "\nThis program creates a student list.\n";

	while (running){
		
		//Prompt user.
		cout << "\nCommands:\n" 
			 << "(1) Add a student\n"
			 << "(2) Remove a student\n"
			 << "(3) Generate random students\n"
			 << "(P) Print list\n"
			 << "(Q) Quit\n\n";
		cin >> answer;

		//Make sure answer is valid.
		while (answer != '1' && answer != '2' && answer != '3' && 
			   answer != 'P' && answer != 'p' && answer != 'Q' && answer != 'q'){
			cout << "\nChoose one of the options above.\n\n";
			cin >> answer;
		}

		//Call function based on answer.
		if (answer == '1') table.add();
		if (answer == '2') table.remove();
		if (answer == '3') table.addRandom();
		if (answer == 'P' || answer == 'p') table.print();
		if (answer == 'Q' || answer == 'q') running = false;
	}
}