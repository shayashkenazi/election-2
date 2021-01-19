#include "PtrCitizenArray.h"

PtrCitizenArray::PtrCitizenArray() {

}

PtrCitizenArray::~PtrCitizenArray() {

}

bool PtrCitizenArray::addPtrToCitizen  ( Citizen* add) {
   
	citizens.push_back(add);
    return true;
    
}

const PtrCitizenArray & PtrCitizenArray::operator=(const PtrCitizenArray & other)
{
    citizens = other.citizens;
	return *this;
}

void PtrCitizenArray::save(ofstream& outFile) const
{
    int logicArrSize = citizens.size();
    outFile.write(rcastcc(&logicArrSize), sizeof(int));
    for (int i = 0; i < logicArrSize; i++)
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

