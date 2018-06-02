#include "student.h"

Student::Student(char f[80], char l[80], int i, float g){ //Constructor.
  strcpy(fName, f);
  strcpy(lName, l);
  ID = i;
  GPA = g;
}

char* Student::getfName(){ //Returns the first name.
  return fName;
}

char* Student::getlName(){ //Returns the last name.
  return lName;
}

int Student::getID(){ //Returns student ID number.
  return ID;
}

float Student::getGPA(){ //Returns GPA.
  return GPA;
}
