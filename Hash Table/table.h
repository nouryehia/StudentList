//Includes
#include <iostream> 
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

//If undefined.
#ifndef TABLE_H 
#define TABLE_H

//Define class.
class table {
protected:

	//Declare variables.
	struct node{
		char fName[80];
  		char lName[80];
  		int ID;
  		float GPA;
		node* next;
	};
	int ID;
	int size;
	node** list;
public:

	//Declare functions.
	table();
	void add();
	void rehash(node*, int);
	void addRandom();
	void remove();
	int hash(int);
	void print();
	bool isEmpty();
};

//Constructor.
table::table(){
	ID = 100001;
	size = 100;
	list = new node*[size];
	for (int i; i < size; i++) list[i] = NULL;
}

//Manually adds a a student to the list.
void table::add(){

	//Declare variables.
	node* toAdd = new node, *temp;
	int index;

	//Ask for student info.
	cout << "\nEnter the student's first name.\n\n";
	cin >> toAdd->fName;
	cout << "\nEnter the student's last name.\n\n";
	cin >> toAdd->lName;
    cout << "\nEnter the student's ID number.\n\n";
    cin >> toAdd->ID;
    cout << "\nEnter the student's GPA.\n\n";
    cin >> toAdd->GPA;

    //Make sure that ID is not already taken.
    index = hash(toAdd->ID);
    temp = list[index];
    while (temp){
    	if (toAdd->ID == temp->ID){
    		cout << "\nA student with this ID number already exists.\n";
    		return;
    	}
    	temp = temp->next;
    }

    //If ID is not taken, add student to the list.
	rehash(toAdd, index);

	//Confirmation message.
	cout << "\n" << toAdd->fName << " " << toAdd->lName << " was added to your list.\n";
}

//Adds student to the list according to the hash function while respecting the chaining rule.
void table::rehash(node* toAdd, int index){
	
	//Declare variables.
	bool added = false;
	node* temp, **oldList, **queue = new node*[size];
	int qCount = 0;

	//Find a spot to add student while making sure that no more than 3 collisions occur.
    while (!added){
    	if(!list[index]){
    		list[index] = toAdd;
    		list[index]->next = NULL;
    		added = true;
    	}
    	else {
    		temp = list[index];
    		for (int i = 0; i < 2; i++){
	    		if (temp->next) temp = temp->next;
    			else {
    				temp->next = toAdd;
    				temp->next->next = NULL;
    				added = true;
    				break;
	    		}
    		}
    	}

    	//If 3 more collisions occur, expand the table and rehash everything.
    	if (!added){
    		oldList = list;
    		size *= 2;
    		list = new node*[size];
    		for (int i; i < size; i++) list[i] = NULL;
    		for (int i = 0; i < size/2; i++) {
    			if (oldList[i]){
    				temp = oldList[i];
    				while(temp){
    					queue[qCount] = temp;
    					qCount++;
    					temp = temp->next;
    				}
    			}
    		}
    		for (int i = 0; i < qCount; i++) rehash(queue[i], hash(queue[i]->ID));
    		delete oldList;
    	}
    }
}

//Generates random students using names from files.
void table::addRandom(){

	//Declare variables.
	int count, posFirst = 0, posLast = 0;
	char firstFile[80], lastFile[80], name[80], firstNames[800][80], lastNames[800][80];

	//Prompt user for the number of students to be added.
	cout << "\nHow many random students do you want to add to your list?\n\n";
	cin >> count;

	//Quit function if user wishes to enter no student.
	if (count == 0) return;
	
	//Prompt user for file to be used to generate the names.
	if (count == 1){
		cout << "\nEnter the name of the file you want to use to generate a first name.\n\n";
		cin >> firstFile;
		cout << "\nEnter the name of the file you want to use to generate a last name.\n\n";
		cin >> lastFile;

	}
	else{
		cout << "\nEnter the name of the file you want to use to generate first names.\n\n";
		cin >> firstFile;
		cout << "\nEnter the name of the file you want to use to generate last names.\n\n";
		cin >> lastFile;
	}

	//Open file containing first names. If it does not exist, ask user to reenter the name.
	ifstream inFile;
	inFile.open(firstFile);
	while (!inFile){
		cout << "\nFile containing first names not found. Retype the name of the file you would like to read.\n\n";
		cin >> firstFile;
		inFile.open(firstFile);
	}

	//Copy the names in teh file in an array.
	while (inFile >> name) strcpy(firstNames[posFirst++], name); 
	inFile.close();

	//Open file containing last names. If it does not exist, ask user to reenter the name.
	inFile.open(lastFile);
	while (!inFile){
		cout << "\nFile containing last names not found. Retype the name of the file you would like to read.\n\n";
		cin >> lastFile;
		inFile.open(lastFile);
	}

	//Copy the names in teh file in an array.
	while (inFile >> name) strcpy(lastNames[posLast++], name);
	inFile.close();

	//Allows program to generate randomness (not really random but close enough).
	srand(time(NULL));

	//Creates new student using names from the files, an incrementing student ID #, and a random GPA.
	for (int i = 0; i < count; i++){
		node* toAdd = new node;
		strcpy(toAdd->fName, firstNames[rand()%posFirst]);
		strcpy(toAdd->lName, lastNames[rand()%posFirst]);
		toAdd->ID = ID++;
		toAdd->GPA = (float)rand()/(float)(RAND_MAX/5.00);
		rehash(toAdd, hash(toAdd->ID));
	}

	//Confirmation message.
	cout << "\n" << count << " random students were added to your list.\n";
}

//Removes a student from the list.
void table::remove(){

	//Declare variables.
	int ID, index;
	bool head = true, found = false;
	node *previous = NULL, *toRemove;

	//Tell the user if list is already empty.
	if(isEmpty()){
		cout << "\nThere are no students to remove in your list.\n";
		return;
	}

	//Prompt user for ID # of the student to be deleted.
	cout << "\nEnter the ID number of the student would like to delete.\n\n";
	cin >> ID;
	
	//Find student in table.
	index = hash(ID);
	node* temp = list[index];
	while (temp){
		if (temp->ID == ID){
			toRemove = temp;
			found = true;
			break;
		}
		else {
			head = false;
			previous = temp;
		}
		temp = temp->next;
	}

	//Quit function if student is not found.
	if (!found){
		cout << "\nThe student you want to delete is not in your list.\n";
		return;
	}

	//Confirmation message.
	cout << "\n" << toRemove->fName << " " << temp->lName << " was removed from your list.\n";
	
	//Delete student.
	if(head){
		list[index] = toRemove->next;
		delete toRemove;
	}
	else{
		previous->next = toRemove->next;
		delete toRemove;
	}
}

//Hash function.
int table::hash(int ID){ return 17*ID % size; }

//Prints table.
void table::print(){
	if(isEmpty()){
		cout << "\nYour list is empty.\n";
		return;
	}
	cout << "\nStudent List:\n\n";
	for (int i = 0; i < size; i++){
		if (list[i]){
			node* temp = list[i];
			while (temp){
				cout << temp->fName << " " << temp->lName << " ~ ID #: " << temp->ID << ", GPA: " << fixed << setprecision(2) << temp->GPA;
				if (temp->next) cout << "\n";
				temp = temp->next;
			}
			cout << "\n";
		}	
	}
}

//Checks if the list is empty.
bool table::isEmpty(){
	for (int i = 0; i < size; i++)
		if (list[i]) return false;
	return true;
}
#endif