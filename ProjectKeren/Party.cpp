#include "Party.h"
#include <iostream>
using namespace std;
int Party ::partySerialNumber = 0;
Party::Party() 
{   
    PartyId = partySerialNumber;
}
Party::Party(const string _PartyName, Citizen& _LeadCand) :LeadCand(&_LeadCand)
{

    partySerialNumber++;
    PartyId = partySerialNumber;
    PartyName = _PartyName;
}

Party::Party(ifstream& inFile, Citizen& _LeadCand) :LeadCand(&_LeadCand)// file ctor
{
   
    partySerialNumber++;
    PartyId = partySerialNumber;
    int lenOfName;
    inFile.read(rcastc(&lenOfName), sizeof(int));
    PartyName.resize(lenOfName);
    inFile.read(rcastc(&PartyName[0]), sizeof(char) * lenOfName);
}

Party::~Party()
{
}

Party::Party(const Party& other)
{
    PartyName = other.PartyName;
    PartyId = other.PartyId;
    SumOfElectors = other.SumOfElectors;
    LeadCand = other.LeadCand;
    repArray = other.repArray;
}

bool Party::setPartyName(const string _PartyName)
{
    PartyName = _PartyName;
    return true;
}
bool Party :: addRep (Citizen* citizen,int& countyId) 
{

   
    if (countyId > repArray.size())
    {	   
        repArray.resize(countyId);
    }
    repArray[countyId-1].addPtrToCitizen(citizen);
    return true;
}
void Party::printRep() const
{
    for (int i = 0; i < repArray.size(); i++)
    {
	   cout << "the Reps of County number " << i+1 << "  are  " << endl << repArray[i] << endl;
    }

}
void Party::pritnRepByIdx(int CountOfRep,int CountyId) 
{
    if (CountOfRep == 0 || repArray.empty()==1 || repArray[CountyId - 1].size() == 0 )
    {
	   cout << " the party doesnt have rep for this county" << endl;
	   return;
    }
    
    if (CountOfRep > repArray[CountyId-1].size())
	   CountOfRep = repArray[CountyId-1].size();
    cout << "the Reps are :" << endl;

    for (int i = 0; i < CountOfRep; i++)
    {
	   cout << repArray[CountyId-1].getCitizen(i) << endl;
    }
}
const Party & Party::operator=(const Party & other)
{
    PartyName.clear();
    PartyName = other.PartyName;
	PartyId = other.PartyId;
	
	SumOfElectors = other.SumOfElectors;
	
	LeadCand = other.LeadCand;
    repArray = other.repArray;
	
	return *this;

}

void Party::save(ofstream& outFile) const
{
    long LeadCandid = LeadCand->getId();// lead candidate id
    int lenOfName = PartyName.size();// length of party name
    outFile.write(rcastcc(&LeadCandid), sizeof(long));//write lead cand id.
    outFile.write(rcastcc(&lenOfName), sizeof(int));//length of party name
    outFile.write(rcastcc(&PartyName[0]), sizeof(char) * lenOfName);
    int repArrSize = repArray.size();
    outFile.write(rcastcc(&repArrSize), sizeof(int));// for rep array

    for (int i = 0; i < repArrSize; i++) // write rep array
    {
	   repArray[i].save(outFile);
    }
}

ostream& operator<<(ostream& os, const Party& party)
{
    os << "Party Name: " << party.getPartyName() << endl << "Lead candidate details : " << party.getLeadCand() << endl;
    return os;
}
