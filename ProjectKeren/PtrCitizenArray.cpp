#include "PtrCitizenArray.h"

PtrCitizenArray::PtrCitizenArray() {
   
    citizens = new Citizen* [2];
    for (int i = 0; i < 2; i++)
	   citizens[i] = nullptr;
    logic = 0;
    physical = 2;
}

PtrCitizenArray::~PtrCitizenArray() {
    delete[]citizens;
}

bool PtrCitizenArray::addPtrToCitizen  ( Citizen* add) {
   
    if (logic == physical) {
	   physical *= 2;
	   Citizen** tmp = new Citizen * [physical];
	   for (int i = 0; i < logic; i++)
		  tmp[i] = citizens[i];
	   delete[] citizens;
	   citizens = tmp;
    }
	citizens[logic] = add;
	logic++;
    return true;
    
}

const PtrCitizenArray & PtrCitizenArray::operator=(const PtrCitizenArray & other)
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

void PtrCitizenArray::save(ofstream& outFile) const
{
    outFile.write(rcastcc(&logic), sizeof(int));
    for (int i = 0; i < logic; i++)
    {
	   long id = citizens[i]->getId();
	   outFile.write(rcastcc(&id), sizeof(long));
    }
    

}

std::ostream& operator<<(std::ostream& os, const PtrCitizenArray& listrep)
{
    for (int i = 0; i < listrep.size() ; i++)
    {
	   os  << *(listrep.citizens[i]) << endl;
    }

    return os;

}

