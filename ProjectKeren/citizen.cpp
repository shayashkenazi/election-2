    

#include "citizen.h"
#include"County.h"
#include <iostream>

#pragma warning(disable : 4996)

using namespace std;
Citizen::Citizen (const char* _name, long  _id, unsigned int _yearOfBirth) : yearOfBirth(_yearOfBirth), id(_id),county(nullptr) {
     this->name = new char [strlen(_name) + 1];
    strcpy(this->name, _name);
}

Citizen::Citizen(const Citizen& other)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
    id = other.id;
    county = other.county;
    yearOfBirth = other.yearOfBirth;
    isVoted = other.isVoted;
}


Citizen::~Citizen() { delete [] name; }

Citizen& Citizen::operator=(const Citizen& add) {
    name = new char[strlen(add.name) + 1];
    strcpy(name, add.name);
	id = add.id;
	county = add.county;
	yearOfBirth = add.yearOfBirth;
	isVoted = add.isVoted; 
    return *this;
}
bool Citizen::setVote()
{
    if (isVoted == false)
    {
	   isVoted = true;
	   return true;
    }
    return false;
}
ostream& operator<<(ostream& os,const Citizen& citizen) {

    os <<
	   "Citizen Name: " << citizen.getName() << endl <<
	   "ID: " << citizen.getId() << endl <<
	   "year of birth : " << citizen.getyearOfBirth() << endl <<
	   "Citizen County Number is : " << citizen.getCounty().getCountyId() << endl;
    
    return os;
}