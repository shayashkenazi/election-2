#include "PartyArr.h"

PartyArr::PartyArr()
{

}

PartyArr::~PartyArr()
{

}

bool PartyArr::AddParty(Party& add)//check if its bool func
{
    parties.push_back(add);
    return true;
}

void PartyArr::printPartyByOrder()
{
   
    for (int i = 0; i < parties.size(); i++)
    {
	   cout << parties[i] << endl;
	   parties[i].printRep();
    }
}

const Party& PartyArr::GetWinnerParty() const
{
    int maxElec, pdex=0;
    maxElec = parties[0].getSumOfElectors();
    for (int i = 1; i < parties.size(); i++)
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

   if (!parties.empty())
        parties.clear();
    parties = other.parties;
    return *this;
}

void PartyArr::save(ofstream& outFile) const
{
    int partyArrSize = parties.size();
    outFile.write((const char*)&partyArrSize, sizeof(int));// num of parties
    for (int i = 0; i < partyArrSize; i++)
    {
	   parties[i].save(outFile);
    }
}



