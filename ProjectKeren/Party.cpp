#include "Party.h"
#include <iostream>
using namespace std;
int Party ::partySerialNumber = 0;
Party::Party()
{
}
Party::Party(char* _PartyName, Citizen& _LeadCand) :LeadCand(&_LeadCand)
{
    RepArrayPhysical = 0;
    partySerialNumber++;
    PartyId = partySerialNumber;
    this->PartyName = new char[strlen(_PartyName) + 1];
    strcpy(this->PartyName, _PartyName);
}

Party::~Party()
{
    delete PartyName;
    delete [] repArray;//check if we need loop for delete all the array
   /* if (ElectorsByCounty != nullptr)
	   delete[] ElectorsByCounty;*/
}

Party::Party(const Party& other)
{
    PartyName = new char[strlen(other.PartyName) + 1];
    strcpy(PartyName, other.PartyName);
    PartyId = other.PartyId;//mispar sidori shel amiflaga

    SumOfElectors = other.SumOfElectors;

    RepArrayPhysical = other.RepArrayPhysical;

    LeadCand = other.LeadCand;
    repArray = other.repArray;
    numOfCounties = other.numOfCounties;
}

bool Party::setPartyName(const char* _PartyName)
{
    PartyName = new char[strlen(_PartyName) + 1];
    strcpy(PartyName, _PartyName);
    return true;
}
bool Party :: addRep (Citizen* citizen,int& countyId) 
{
    //int countyId;
    //countyId =citizen->getCounty().getCountyId();
    if (repArray == nullptr)
    { 
	   RepArrayPhysical = countyId;
	   repArray = new PtrCitizenArray  [countyId];
    }
    if (countyId > RepArrayPhysical)
    {	   
	   PtrCitizenArray* tmp = new PtrCitizenArray  [countyId];
	   for (int i = 0; i < RepArrayPhysical; i++)
		  tmp[i] = repArray[i];
	   delete[] repArray;
	   repArray = tmp;
    }
    RepArrayPhysical = countyId;
    repArray[countyId-1].addPtrToCitizen(citizen);
    return true;
}
void Party::printRep() const
{
    for (int i = 0; i < RepArrayPhysical; i++)
    {
	   cout << "the Reps of County number" << i << "  are  " << endl << repArray[i] << endl;
    }

}
void Party::pritnRepByIdx(int CountOfRep,int CountyId) 
{
    if (CountOfRep == 0 || repArray ==nullptr || repArray[CountyId - 1].size() == 0 )
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
	PartyName = new char[strlen(other.PartyName) + 1];
	strcpy(PartyName, other.PartyName);
	PartyId = other.PartyId;//mispar sidori shel amiflaga
	
	SumOfElectors = other.SumOfElectors;
	
	RepArrayPhysical = other.RepArrayPhysical;
	
	LeadCand = other.LeadCand;
	repArray = other.repArray;
	numOfCounties = other.numOfCounties;
	return *this;

}

void Party::save(ofstream& outFile) const
{
    int lenOfName = strlen(PartyName);// length of party name
    outFile.write((const char*)&lenOfName, sizeof(int));
    outFile.write((const char*)PartyName, sizeof(char) * lenOfName);
    outFile.write((const char*)&numOfCounties, sizeof(int));// for rep array
    long LeadCandid = LeadCand->getId();// lead candidate id
    outFile.write((const char*)&LeadCandid, sizeof(long));
    for (int i = 0; i < numOfCounties; i++) // write rep array
    {
	   repArray[i].save(outFile);
    }


}

ostream& operator<<(ostream& os, const Party& party)
{
    os << "Party Name: " << party.getPartyName() << endl << "Lead candidate details : " << party.getLeadCand() << endl;
    return os;
}
