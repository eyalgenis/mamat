#ifndef _PERSON_H_
#define _PERSON_H_
#include <iostream>
#include "Proj.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
