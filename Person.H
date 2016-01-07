#ifndef _PERSON_H_
#define _PERSON_H_
#include "Proj.H"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std;

class Person {

public:
	//CONSTRUCTOR
	Person(const int ID, const char* PersonName);

	//DESTRUCTOR
	~Person(); // ???????????

			   //get ID of person
	int getID() const;

	//get *COPY* Name of person
	char* getName() const;

protected:
	int ID_;
	char* PersonName_;
};

#endif

