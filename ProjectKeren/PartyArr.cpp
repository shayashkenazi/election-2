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
    
    parties[logic].setPartyName(add.getPartyName());
    parties[logic].setLeadCand(add.getLeadCand());

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



/*bool PartyArr::InitElectorsArray(int& CountyId)
{
    for (int i = 0; i < logic; i++)
    {
	   parties[i].initElectorsArray(CountyId);
    }
    return true;
}*/


