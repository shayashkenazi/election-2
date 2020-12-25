
#include "CitizenArr.h"

CitizenArr::CitizenArr() //ctor
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
   
    if (logic == physical ) { //check if we need to resize the array.
	   physical *= 2;
	   Citizen** tmp = new Citizen*[physical];
	   for (int i = 0; i < logic; i++) {
		  tmp[i] = citizens[i];
	   }
	   delete[] citizens;
	   citizens = tmp;
    }
    
    citizens[logic] = new Citizen(add);
    logic++; //update logic size.
    return true;
}

bool CitizenArr::SearchById(const long& id) const //check if a citizen is aleardy exist by id.
{
    for (int i = 0; i < logic; i++)
    {
	   if (citizens[i]->getId() == id)
		  return true;
    }
    return false;
}

Citizen* CitizenArr::PtrToCitizen(long& id)// search citizen by id and return ptr to hem if exists.
{
    for (int i = 0; i < logic; i++)
	   if (citizens[i]->getId() == id)
		  return citizens[i];
    return nullptr;//if the citizen wasn't found.
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