
#include "CitizenArr.h"

CitizenArr::CitizenArr() 
{
    citizens = new Citizen*[2];
    logic = 0;
    physical = 2;
}

CitizenArr::~CitizenArr()
{
    delete[] citizens;
}

bool CitizenArr::addCitizen(Citizen& add)
{
   
    if (logic == physical ) {
	   physical *= 2;
	   Citizen** tmp = new Citizen*[physical];
	   for (int i = 0; i < logic; i++) {
		  tmp[i] = citizens[i];
	   }
	   delete[] citizens;
	   citizens = tmp;
    }
    
    citizens[logic] = new Citizen(add);
    logic++;
    return true;
}

bool CitizenArr::SearchById(const long& id) const
{
    for (int i = 0; i < logic; i++)
    {
	   if (citizens[i]->getId() == id)
		  return true;
    }
    return false;
}

Citizen* CitizenArr::PtrToCitizen(long& id)
{
    for (int i = 0; i < logic; i++)
	   if (citizens[i]->getId() == id)
		  return citizens[i];
    return nullptr;
}

void CitizenArr::printList() const
{
    for (int i = 0; i < logic; i++)
	   cout << citizens[i] << endl;
	   
}

const CitizenArr & CitizenArr::operator=(const CitizenArr & other)
{
	logic = other.logic;
	physical = other.physical;
	citizens = new Citizen*[physical];
	for (int i = 0; i < logic; i++)
	{
		citizens[i] = other.citizens[i];
	}
	return *this;
}

const Citizen* CitizenArr::getCitizen(long id) const
{
    for (int i = 0; i < logic; i++) {
	   if (citizens[i]->getId() == id)
		  return citizens[i];//check if its ref
    }
	return nullptr;
}