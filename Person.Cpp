#include "Person.H"

using std::string;
using std::cout;
using std::endl;


//* Function description: constructor of the object person
//* Return value: object person
Person::Person(const int ID, const string Name) :
	ID_(ID), Name_(Name) {}

Person::~Person()	{	delete Name_;	}

//* Function description: get ID of person
//* Return value: int ,the ID of person
int Person::getID() const { return ID_;}


//* Function description: get Name of person
//* Return value: STRING CLASS OR TYPE (CHAR*)? the Name of person
char* Person::getName() const { return Name_;}


////* NOT NEEDED HERE: print info of person using cout
//void Person::print() const
//{
//	cout << "Name : " << Name << endl;
//	cout << "Age : " << age << endl;
//}


