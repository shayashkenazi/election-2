
#include "CitizenArr.h"

CitizenArr::CitizenArr() //ctor
{
}

CitizenArr::CitizenArr(const CitizenArr& other)
{
	for (auto citizen : other.citizens)
		citizens.push_back(new Citizen(*citizen));//copy c'tor of survivor
}

CitizenArr::~CitizenArr()
{
	for (auto citizen : citizens)
		delete citizen;//copy c'tor of survivor
}

bool CitizenArr::addCitizen(Citizen& add)
{
    citizens.push_back( new Citizen(add));
    return true;
}

bool CitizenArr::SearchById(const long& id) const //check if a citizen is aleardy exist by id.
{
    for (int i = 0; i < citizens.size(); i++)
    {
	   if (citizens[i]->getId() == id)
		  return true;
    }
    return false;
}

Citizen* CitizenArr::PtrToCitizen(long& id)// search citizen by id and return ptr to hem if exists.
{
    for (int i = 0; i < citizens.size(); i++)
	   if (citizens[i]->getId() == id)
		  return citizens[i];
    return nullptr;//if the citizen wasn't found.
}

void CitizenArr::printList() const
{
    if (citizens.empty() == 1 ){
	   cout << "This county don't have citizens " << endl;
	   return;
    }
    for (int i = 0; i < citizens.size(); i++)
	   cout << *citizens[i] << endl;
	   
}

const CitizenArr & CitizenArr::operator=(const CitizenArr & other)
{
	if (this != &other) {
		for (auto citizen : citizens)
			delete citizen;//copy c'tor of survivor
		for (auto citizen : other.citizens)
			citizens.push_back(new Citizen(*citizen));
	}

	return *this;
}

void CitizenArr::save(ofstream& outfile) const
{
    for (int i = 0; i < citizens.size(); i++)
    {
	   citizens[i]->save(outfile);
    }
}

const Citizen* CitizenArr::getCitizen(long id) const
{
    for (int i = 0; i < citizens.size(); i++) {
	   if (citizens[i]->getId() == id)
		  return citizens[i];//return ptr to the citizen if found.
    }
	return nullptr;
}