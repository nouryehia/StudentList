#include <iostream> //Includes.
#include <cstring>

#ifndef STUDENT_H //If undefined.
#define STUDENT_H

using namespace std;

class Student{
 protected: //Declare variables.
  char fName[80];
  char lName[80];
  int ID;
  float GPA;
 public: //Declare functions
  Student(char f[80], char l[80], int i, float g);
  //  ~Student();
  
  char* getfName(); //Returns the first name.
  char* getlName(); //Returns the last name.
  int getID(); //Returns student ID number.
  float getGPA(); //Returns GPA.
};
#endif
