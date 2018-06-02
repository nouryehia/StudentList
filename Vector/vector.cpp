#include <iostream>
#include <cstring>
#include <vector>
#include <iomanip>

/* Student List
 * Author: Nour Yehia
 * Date: 11-1-2017
 * This program allows the user to print a list of students along with their student ID and their GPA.
   It also allows the user to add and remove students from the list.*/

using namespace std;

struct Student { //Declare struct.
  char fName[50];
  char lName[50];
  int ID;
  float GPA;
};

vector<Student*> list; //Declare vectors and pointers.
vector<Student*> *pointerList = &list;
bool running = true; //Declare variables and functions.
char command[7];
void add(vector<Student*> *pointerList);
void print(vector<Student*> *pointerList);
void del(vector<Student*> *pointerList);
void quit();
void readInput(char input[50]);

int main(){
  while (running == true){
    cout << "Enter 'ADD' to add a student to your list." << endl; //prompt user.
    cout << "Enter 'DELETE' to delete a student from the list." << endl;
    cout << "Enter 'PRINT' to print out the list." << endl;
    cout << "Enter 'QUIT' to quit the program." << endl;
    cout << endl;
    
    readInput(command); //read in command.
    while (strcmp(command, "ADD") != 0 && strcmp(command, "DELETE") != 0 &&
	   strcmp(command, "PRINT") != 0 && strcmp(command, "QUIT") != 0){
      cout << "Please enter a valid command." << endl;
      readInput(command);
    }
    
    if (strcmp(command, "ADD") == 0){ //check which function to run.
      add(pointerList);
    }
    if (strcmp(command, "DELETE") == 0){
      del(pointerList);
    }
    if (strcmp(command, "PRINT") == 0) {
      print(pointerList);
    }
    if (strcmp(command, "QUIT") == 0) {
      quit();
    }
  }
}

void add(vector<Student*> *pointerList){ //add a student.
  Student* apollo = new Student();
  cout<<endl;
  cout << "Enter the student's first name." << endl;
  cin >> apollo->fName;
  cout << "Enter the student's last name" << endl;
  cin >> apollo->lName;
  cout << "Enter the student's ID number." << endl;
  cin >> apollo->ID;
  cout << "Enter the student's GPA" << endl;
  cin >> apollo->GPA;
  cout << apollo->fName << " " << apollo->lName << " was added to the list." << endl;
  cout<< endl;
  pointerList->push_back(apollo);

}

void print(vector<Student*> *pointerList){ //orint out the list.
  cout<< endl;
  cout<< "Student List:" << endl;
  for (vector<Student*>::iterator i = pointerList->begin(); i != pointerList->end(); i++){
    Student* apollo = *i;
    cout << apollo->fName << " " << apollo->lName <<
      ": Student ID~ " << apollo->ID << " GPA~ " << fixed << setprecision(2) << apollo->GPA << endl;
  }
  cout<< endl;
}

void del(vector<Student*> *pointerList){ //delete a student.
  int input;
  int counter = -1;
  bool studentFound = false;
  cout<< endl;
  cout<< "Enter the student ID of the student you want to delete." << endl;
  cin >> input;
  for (vector<Student*>::iterator i = pointerList->begin(); i != pointerList->end(); i++){
    Student* apollo = *i;
    if (apollo->ID == input){
    counter++;
    cout << "You have deleted " << apollo->fName << " " << apollo->lName << " from the list." << endl;
    delete (*pointerList->begin() + counter);
    pointerList->erase(pointerList->begin() + counter);
    break;
    }
    else {
      counter++;
    }
  }
  cout<< endl;
}

void quit(){ //terminate the program.
  running = false;
}

void readInput(char input[7]){ //turns input to upper case. 
  cin >> input;
  for (int i = 0; i < strlen(input); i++){
    input[i] = toupper(input[i]);
  }
}
