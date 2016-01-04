#include "Person.H"

//using std::string;
using std::cout;
using std::endl;



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


//* Function description: get ID of person
//* Return value: int ,the ID of person
int Person::getID() const
{
	return ID_;
}


//* Function description: get Name of person
//* Return value: STRING CLASS OR TYPE (CHAR*)? the Name of person
char* Person::getName() const
{
	char* CopyName = new char[strlen(PersonName_) + 1];
	strcpy(CopyName, PersonName_);
	return CopyName;
}