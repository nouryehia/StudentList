/* Linked List 2
 * Author: Nour Yehia
 * Date: Jan 23 2018
 * This program allows the user to print a list of students along with their student ID and GPA.
 * It also allows the user to add and remove students from the list, as well as print out their average GPA.
 * This program uses a linked list to create the student list. */

#include "student.h" //Includes.
#include "node.h"
#include <iomanip>

Node* add(char fName[80], char lName[80], int ID, float GPA, Node* &n); //Declare functions.
Node* del(int ID, Node* &n);
void print(Node* n);
void avg(Node* n);
bool quit();
char* upperCase(char input[80]);
void readInput(char input[7]);

int main(){
  bool running = true; //Declare variables.
  char command[7];
  Node* head = NULL;

  while (running){
    cout << endl << "Enter 'ADD' to add a student to your list" << endl //Prompt user.
	 << "Enter 'DELETE' to remove a student from your list." << endl
	 << "Enter 'PRINT' to print out your list" << endl
	 << "Enter 'AVG' to print out the average GPA of the students on your list" << endl
	 << "Enter 'QUIT' to quit the program" << endl << endl;

    readInput(command);
    while(strcmp(command, "ADD") != 0 && strcmp(command, "DELETE") != 0 && strcmp(command, "PRINT") &&
	  strcmp(command, "AVG") != 0 && strcmp(command, "QUIT") != 0){ //Check if input is valid.
      cout << "Please enter a valid command." << endl << endl;
      readInput(command);
    }

    if (strcmp(command, "ADD") == 0){ //If add.
      char* fName = new char[80];
      char* lName = new char[80];
      int ID;
      float GPA;

      cout << endl << "Enter the student's first name." << endl; //Prompt user.
      cin >> fName;
      cin.ignore(80, '\n');
      fName = upperCase(fName);
      cout << endl << "Enter the student's last name." << endl;
      cin >> lName;
      cin.ignore(80, '\n');
      lName = upperCase(lName);
      cout << endl << "Enter the student's ID number." << endl;
      cin >> ID;
      cin.ignore(80, '\n');
      cout << endl << "Enter the student's GPA." << endl;
      cin >> GPA;
      cin.ignore(80, '\n');

      add(fName, lName, ID, GPA, head);
    }

    if (strcmp(command, "DELETE") == 0){ //If delete.
      int ID;
      
      if (head == NULL){
        cout << endl << "Your list is empty. Add some students!" << endl; 
      }
      else{
        cout << "Enter the ID number of the student you want to delete." << endl; //Prompt user.
        cin >> ID;
        cin.ignore(80, '\n');
      
        del(ID, head); //Delete.
      }
    }

    if (strcmp(command, "PRINT") == 0){ //If print.
      if (head == NULL){
        cout << endl << "Your list is empty. Add some students!" << endl; 
      }
      else {
        cout << endl << "Student List:" << endl;
        print(head); //Print.
      }
    }

    if (strcmp(command, "AVG") == 0){ //If avg.
      avg(head);
    }

    if (strcmp(command, "QUIT") == 0){ //If quit.
      running = quit();
    }
  }
}

Node* add(char fName[80], char lName[80], int ID, float GPA, Node* &n){ //Adds a student to the list.
if (n == NULL || ID < n->getStudent()->getID()){
    Node* temp;
    Student* s = new Student(fName, lName, ID, GPA);
    temp = new Node(s);
    temp->setNext(n);
    n = temp;
    cout << endl << s->getfName() << " " << s->getlName() << " was added to the list." << endl;
  }
  else{
    Node* next = n->getNext();
    n->setNext(add(fName, lName, ID, GPA, next)); //Recursion.
  }
  return n;
}

Node* del(int ID, Node* &n){ //Deletes a student from the list.
  if (n->getStudent()->getID() == ID){
    Node* temp;
    temp = n;
    cout << endl << n->getStudent()->getfName() << " " << n->getStudent()->getlName() << " was deleted from the list." << endl;
    n = n->getNext();
    delete temp;
  }
  else {
    Node* next = n->getNext();
    n->setNext(del(ID, next)); //Recursion.
  }
  return n;
}

void print(Node* n){ //Prints the list.
  if (n != NULL){
    cout << n->getStudent()->getfName() << " " << n->getStudent()->getlName()
	       << " ~ Student ID Number: " << n->getStudent()->getID()
	       << ", GPA: " << fixed << setprecision(2) << n->getStudent()->getGPA() << endl;
    print(n->getNext()); //Recursion.
  }
}

void avg(Node* n){ //Averages the GPAs of all the students in the list.
  double addedNum = 0;
  int studentNum = 0;
  double avg = 0;

  if (n == NULL){
    cout << endl << "Your list is empty. Add some students!" << endl; 
  }
  else{
    while (n != NULL){
      addedNum += n->getStudent()->getGPA();
      studentNum++;
      n = n->getNext();
    }
    avg = addedNum/studentNum;
    cout << endl << "Average GPA: " << fixed << setprecision(2) << avg << endl;
  }
}

bool quit(){ //Quits the program.
  return false;
}

char* upperCase(char input[80]) { //Turns input into upper case.
  for (int i = 0; i < strlen(input); i++){
      input[i] = toupper(input[i]);
  }
  return input;
}

void readInput(char input[7]){ //Turns input into upper case and reads it.
  cin.getline(input, 80);
  upperCase(input);
}

