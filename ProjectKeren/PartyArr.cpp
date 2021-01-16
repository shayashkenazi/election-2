#include "PartyArr.h"

PartyArr::PartyArr()
{
    parties = new Party[2];
    logic = 0;
    physical = 2;
}

PartyArr::~PartyArr()
{
    delete [] parties;
}

bool PartyArr::AddParty(Party& add)//check if its bool func
{
    parties[logic] = add;
    logic++;
    if (logic == physical - 1) {
	   physical *= 2;
	   Party* tmp = new Party[physical];
	   for (int i = 0; i < logic; i++)
		  tmp[i] = parties[i];
	   delete[] parties;
	   parties = tmp;
    }
    return true;
}

void PartyArr::printPartyByOrder()
{
   
    for (int i = 0; i < logic; i++)
    {
	   cout << parties[i] << endl;
	   parties[i].printRep();
    }
}

const Party& PartyArr::GetWinnerParty() const
{
    int maxElec, pdex=0;
    maxElec = parties[0].getSumOfElectors();
    for (int i = 1; i < logic; i++)
    {
	   if (parties[i].getSumOfElectors() > maxElec)
	   {
		  maxElec = parties[i].getSumOfElectors();
		  pdex = i;
	   }
    }
    return parties[pdex];
}

const PartyArr& PartyArr::operator=(const PartyArr& other)
{
    logic = other.logic;
    physical = other.physical;
   if (parties != nullptr)
        delete[] parties;
    parties = new Party[physical];
    for (int i = 0; i < logic; i++)
    {
        parties[i] = other.parties[i];
    }
    return *this;
}

void PartyArr::save(ofstream& outFile) const
{
    outFile.write((const char*)&logic, sizeof(int));// num of parties
    for (int i = 0; i < logic ; i++)
    {
	   parties[i].save(outFile);
    }
}



