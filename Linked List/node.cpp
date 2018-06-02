#include "node.h"

//constructor
Node::Node(Student* _student) {
  student = _student;
  node = NULL;
}

//deconstructor
Node::~Node() {
  delete student;
  node = NULL;
}

//return the next node pointer
Node* Node::getNext() {
  return node;
}
//return the student pointer
Student* Node::getStudent() {
  return student;
}

//set next pointer to its node
void Node::setNext(Node* current) {
  node = current;
}
