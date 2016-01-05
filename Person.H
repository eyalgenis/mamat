#ifndef _PERSON_H_
#define _PERSON_H_
#include <iostream>
#include "Proj.H"

class Person {

public: // methods

	//CONSTRUCTOR
	Person(const int ID, const char* PersonName);

	//DESTRUCTOR
	~Person(); // ???????????

	//* Function description: get ID of person
	//* Return value: int ,the ID of person
	int getID() const;

	//* Function description: get Name of person
	//* Return value: STRING CLASS OR TYPE (CHAR*)? the Name of person
	char* getName() const;

	////* NOT NEEDED HERE: print info of person using cout
	//void print() const;

protected: // PROPERTIES
	int ID_; // UNIQUE
	char* PersonName_; // STRING CLASS OR TYPE (CHAR*)?
};

#endif
