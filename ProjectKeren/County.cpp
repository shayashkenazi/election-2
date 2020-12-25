#include "County.h"
#include <iostream>
#pragma warning(disable : 4996)


using namespace std;
int County :: countySerialNumber = 0;
County::County(char* _CountyName, int _NumOfRep) : NumOfRep(_NumOfRep), MaxPartyVotesIndex(0)
{
    countySerialNumber++;
    countyId = countySerialNumber;
    CountyName = new char[strlen(_CountyName) + 1];
    strcpy(CountyName, _CountyName);
    voteArrayLogic = 0;
    voteArrayPhy = 2;
    VoteCountyArray = new int[voteArrayPhy];
    VoteCountyArray[0] = VoteCountyArray[1] = 0;
    HelpIntArray = new int[voteArrayPhy];
    restArrayVoters = new float[voteArrayPhy];
}
County::County()
{

}
County::County(const County& other)
{
    this->CountyName = new char[strlen(other.getName()) + 1];
    strcpy(CountyName, other.CountyName);
    NumOfRep = other.NumOfRep;
    countyId = other.countyId;
    eligibleCitizen = other.eligibleCitizen;
    voteArrayLogic = other.voteArrayLogic;
    voteArrayPhy = other.voteArrayPhy;
    numOfVotes = other.numOfVotes;
    MaxPartyVotesIndex = other.MaxPartyVotesIndex;
    VoteCountyArray = new int[voteArrayPhy];
    restArrayVoters = new float[voteArrayPhy];
    HelpIntArray = new int[voteArrayPhy];
    for (int i = 0; i < voteArrayLogic; i++)
    {
	   VoteCountyArray[i] = other.VoteCountyArray[i];
	   restArrayVoters[i] = other.restArrayVoters[i];
	   HelpIntArray[i] = other.HelpIntArray[i];
    }
}
County::~County()
{
    delete[] CountyName;
    delete[]VoteCountyArray;
    delete[] HelpIntArray;
    delete[]restArrayVoters;
}

int County::FindMaxValueIdx()
{
    float temp,max= restArrayVoters[0]-(float)HelpIntArray[0];
    int idx=0;
    for (int i = 1; i < voteArrayLogic; i++)
    {
	   temp = restArrayVoters[i]- (float)HelpIntArray[i];
	   if (temp > max) {
		  max = temp;
		  idx = i;
	   }
    
    }
    restArrayVoters[idx] = 0;
    return idx;
}

const County& County::operator=(const County& other) {
   this->CountyName = new char[strlen(other.getName()) + 1];
    strcpy(CountyName, other.CountyName);
    NumOfRep = other.NumOfRep;
	countyId = other.countyId;
	eligibleCitizen = other.eligibleCitizen;
	voteArrayLogic = other.voteArrayLogic;
	voteArrayPhy = other.voteArrayPhy;
	numOfVotes = other.numOfVotes;
	MaxPartyVotesIndex = other.MaxPartyVotesIndex;
	//percentvoter = other.percentvoter;
	VoteCountyArray = new int[voteArrayPhy];
	restArrayVoters = new float[voteArrayPhy];
	HelpIntArray = new int[voteArrayPhy];
	for (int i = 0; i < voteArrayLogic; i++)
	{
	    VoteCountyArray[i] = other.VoteCountyArray[i];
	    restArrayVoters[i] = other.restArrayVoters[i];
	    HelpIntArray[i] = other.HelpIntArray[i];
	}	    
	return *this;
}
bool County::ResizeVoteArray()
{
    voteArrayLogic++;
    if (voteArrayLogic == voteArrayPhy )
    {
	   voteArrayPhy *= 2;
	   int* tmp = new int[voteArrayPhy];
	   for (int i = 0; i < voteArrayPhy; i++)//init the tmp array
		  tmp[i] = 0;
	   for (int i = 0; i < voteArrayLogic; i++)
		  tmp[i] = VoteCountyArray[i];
	   delete[] VoteCountyArray;
	   VoteCountyArray = tmp;
    }
    
    return true;
}
bool County::UpdateVoteArrayToRep()
{
    float RepValue = (float)numOfVotes / NumOfRep;
    int sumRep=0,index;
    UpdateRestArrayVoters();
    for (int i = 0; i < voteArrayLogic; i++)
    {
	   HelpIntArray[i] = (int)restArrayVoters[i];
	   sumRep += HelpIntArray[i];
    }
  while(sumRep < NumOfRep)
    {
	   index = FindMaxValueIdx();
	   HelpIntArray[index]++;
	   sumRep++;
    }
  return true;
}
bool County::UpdateRestArrayVoters()
{
    float res;
    for (int i = 0; i < voteArrayLogic; i++)
    {
	   if (numOfVotes == 0)
		  restArrayVoters[i] = 0;
	   else
		  restArrayVoters[i] = (float)(VoteCountyArray[i] / numOfVotes) * NumOfRep;
    }
    return true;
}
void County::MostVotedParty()
{
    int  indexP = 0;
    int maxVote = VoteCountyArray[0];
    int temp;
    for (int i = 1; i < voteArrayLogic; i++)
    {
	   temp = VoteCountyArray[i];
	   if (temp > maxVote) {
		  maxVote = temp;
		  indexP = i;
	   }
    }

    setMaxPartyVotesIndex(indexP);//set index in county MaxPartyVotesIndex    
    UpdateVoteArrayToRep();        
}
ostream& operator<<(ostream& os, const County& county) {

    os <<
	   "County Name: " << county.getName() << endl <<
	   "CountyID: " << county.getCountyId() << endl <<
	   "number of reps : " << county.getNumOfRep() << endl;
	 
    return os;
}