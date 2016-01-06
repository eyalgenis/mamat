#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !_CRT_SECURE_NO_WARNINGS
#include "Person.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// CONSTRUCTOR
Person::Person(const int ID, const char* PersonName) :
	ID_(ID)
{
	PersonName_ = new char[strlen(PersonName) + 1];
	strcpy(PersonName_, PersonName);
}

//DESTRUCTOR
Person::~Person()
{
	delete []PersonName_;
}


//get ID of person
int Person::getID() const
{
	return ID_;
}


//get *COPY* Name of person
char* Person::getName() const
{
	char* CopyName = new char[strlen(PersonName_) + 1];
	strcpy(CopyName, PersonName_);
	return CopyName;
}