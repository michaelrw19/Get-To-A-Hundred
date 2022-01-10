#include <iostream>
#include <stdlib.h>
#include "list.h"
using namespace std;

//initialize the variables
List::List(int size) {
	numsPtr = new(nothrow) int[size];
	int length = 0;
}

//add an element for the array
void List::addNum(int num) {
	numsPtr[length] = num;
	length++;
}

int List::getNumAt(int loc) {
	return numsPtr[loc];
}

int List::getLastNum() {
	return numsPtr[length - 1];
}

//Delete the allocated memory 
void List::deleteNums() {
	delete[] numsPtr;
}

int List::getLength() {
	return length;
}
