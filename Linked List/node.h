#include "student.h" //Include.

#ifndef NODE_H //If undefined
#define NODE_H

class Node {
 protected: //Declare variables.
  Student* student;
  Node* node;
 public: //Declare functions.
  Node(Student*); //Constructor.
  ~Node(); //Destructor.
  Node* getNext(); //Returns next node in list.
  Student* getStudent(); //Returns the student node is pointing to.
  void setNext(Node*); //Creates next node in list. io
};
#endif
