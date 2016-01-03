#ifndef _PERSON_H_
#define _PERSON_H_
//#include <string>
#include <iostream>

//using std::string;

class Person {

public: // methods
	//* Function description: constructor of the object person, // STRING CLASS OR TYPE (CHAR*)?
	//* Return value: object person
	Person(const int ID, const string Name);

	//*************************************************************
	//* Function description: destructor of the object Student.
	//*************************************************************
	~Person() { delete Name }; // ???????????

	//* Function description: get ID of person
	//* Return value: int ,the ID of person
	int getID() const;

	//* Function description: get Name of person
	//* Return value: STRING CLASS OR TYPE (CHAR*)? the Name of person
	char* getName() const;

	////* NOT NEEDED HERE: print info of person using cout
	//void print() const;

protected: // PROPERTIES
	int ID; // UNIQUE
	char* Name; // STRING CLASS OR TYPE (CHAR*)?
};

#endif
