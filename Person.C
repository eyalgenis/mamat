#include "Person.H"

using std::string;
using std::cout;
using std::endl;


//* Function description: constructor of the object person
//* Return value: object person
Person::Person(const int ID, const string Name) :
	ID(ID), Name(Name) {}

//* Function description: get ID of person
//* Return value: int ,the ID of person
int Person::getID() const { return ID;}


//* Function description: get Name of person
//* Return value: STRING CLASS OR TYPE (CHAR*)? the Name of person
string Person::getName() const { return Name;}


////* NOT NEEDED HERE: print info of person using cout
//void Person::print() const
//{
//	cout << "Name : " << Name << endl;
//	cout << "Age : " << age << endl;
//}


