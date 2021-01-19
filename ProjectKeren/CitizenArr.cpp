
#include "CitizenArr.h"

CitizenArr::CitizenArr() //ctor
{
}

CitizenArr::CitizenArr(const CitizenArr& other)
{
	Citizen* newcit;
	for (auto citizen : other.citizens)
		 newcit = new Citizen(*citizen);
		citizens.push_back(newcit);
}

CitizenArr::~CitizenArr()
{
	for (auto citizen : citizens)
		delete citizen;
}

bool CitizenArr::addCitizen(Citizen& add)
{
	Citizen* newcitizen = new Citizen(add);
    citizens.push_back( newcitizen);
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
	Citizen* toAdd;
	if (this != &other) {
		for (auto citizen : citizens)
			delete citizen;
		for (auto citizen : other.citizens) {
			toAdd = new Citizen(*citizen);
			citizens.push_back(toAdd);
		}
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