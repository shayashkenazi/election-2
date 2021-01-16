#include "County.h"
#include"PartyArr.h"
#include <iostream>
#pragma warning(disable : 4996)

using namespace std;
int County :: countySerialNumber = 0;
County::County(const string _CountyName, int _NumOfRep) : NumOfRep(_NumOfRep), MaxPartyVotesIndex(0)
{
    countySerialNumber++;
    countyId = countySerialNumber;
	CountyName = _CountyName;
    voteArrayLogic = 0;
    voteArrayPhy = 2;
    VoteCountyArray = new int[voteArrayPhy];
    VoteCountyArray[0] = VoteCountyArray[1] = 0;
 
}
County::County()
{ 
    voteArrayLogic = 0;
    voteArrayPhy = 2;
    VoteCountyArray = new int[voteArrayPhy];
    VoteCountyArray[0] = VoteCountyArray[1] = 0;
}
County::County(const County& other)
{
	CountyName = other.CountyName;
    NumOfRep = other.NumOfRep;
    countyId = other.countyId;
    eligibleCitizen = other.eligibleCitizen;
    voteArrayLogic = other.voteArrayLogic;
    voteArrayPhy = other.voteArrayPhy;
    numOfVotes = other.numOfVotes;
    MaxPartyVotesIndex = other.MaxPartyVotesIndex;    
    VoteCountyArray = new int[voteArrayPhy];	
	 for (int i = 0; i < voteArrayPhy; i++)//init voteArray
	   {
		  VoteCountyArray[i] = other.VoteCountyArray[i];  
	   }
    
}
County::County(ifstream& inFile)//file ctor.
{
	int lenOfName;
	inFile.read(rcastc(&lenOfName), sizeof(int));//read the len of county name
	CountyName.resize(lenOfName);
	inFile.read(rcastc(&CountyName[0]), sizeof(char) * lenOfName);//load county name.
	inFile.read(rcastc(&NumOfRep), sizeof(int));//get num of Rep
	inFile.read(rcastc(&numOfVotes), sizeof(int));//get num of Rep

	voteArrayLogic = 0;
	voteArrayPhy = 2;
	VoteCountyArray = new int[voteArrayPhy];
	VoteCountyArray[0] = VoteCountyArray[1] = 0;
	countySerialNumber++;
	countyId = countySerialNumber;//keep serial Number updated
}
County::~County()
{
    delete[]VoteCountyArray;
	if (ElectorsByIdx != nullptr) {
		delete[] ElectorsByIdx;
		delete[]restArrayVoters;
	}
}

int County::FindMaxValueIdx()
{
    float temp,max= restArrayVoters[0]-(float)ElectorsByIdx[0];
    int idx=0;
    for (int i = 1; i < voteArrayLogic; i++)
    {
	   temp = restArrayVoters[i]- (float)ElectorsByIdx[i];
	   if (temp > max) {
		  max = temp;
		  idx = i;
	   }
    
    }
    restArrayVoters[idx] = 0;
    return idx;
}

const County& County::operator=(const County& other) {
	CountyName = other.CountyName;
    NumOfRep = other.NumOfRep;
	countyId = other.countyId;
	eligibleCitizen = other.eligibleCitizen;
	voteArrayLogic = other.voteArrayLogic;
	voteArrayPhy = other.voteArrayPhy;
	numOfVotes = other.numOfVotes;
	MaxPartyVotesIndex = other.MaxPartyVotesIndex;
	//percentvoter = other.percentvoter;
	
	    VoteCountyArray = new int[voteArrayPhy];	
	    for (int i = 0; i < voteArrayLogic; i++)
	    {
		   VoteCountyArray[i] = other.VoteCountyArray[i];	
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
    ElectorsByIdx = new int[voteArrayLogic];
    UpdateRestArrayVoters();
    for (int i = 0; i < voteArrayLogic; i++)
    {
	   ElectorsByIdx[i] = (int)restArrayVoters[i];
	   sumRep += ElectorsByIdx[i];
    }
  while(sumRep < NumOfRep)
    {
	   index = FindMaxValueIdx();
	   ElectorsByIdx[index]++;
	   sumRep++;
    }
  return true;
}
bool County::UpdateRestArrayVoters()
{
    
    restArrayVoters = new float[voteArrayLogic];
    for (int i = 0; i < voteArrayLogic; i++)
    {
	   if (numOfVotes == 0)
		  restArrayVoters[i] = 0;
	   else
		  restArrayVoters[i] = ((float)VoteCountyArray[i] / numOfVotes) * NumOfRep;
    }
    return true;
}
bool County::InitVoteArray(const int& CurNumOfParties)
{
     if (CurNumOfParties > voteArrayLogic)
    {	 
	   voteArrayLogic = CurNumOfParties;
	   voteArrayPhy = CurNumOfParties * 2;
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
void County::CreateVoteArrayFromFile(ifstream& inFile)
{
	   inFile.read(rcastc(&voteArrayLogic), sizeof(int));
	   voteArrayPhy = voteArrayLogic * 2;
	   VoteCountyArray = new int[voteArrayPhy];
	   for (int i = 0; i < voteArrayPhy; i++)
	   {
		  VoteCountyArray[i] = 0;
	   }
	  
	   inFile.read(rcastc(VoteCountyArray), sizeof(int) * voteArrayLogic);
	   
}
ostream& operator<<(ostream& os, const County& county) {

    os <<
	   "County Type: " <<  typeid(county).name() + 6 << endl <<
	   "County Name: " << county.getName() << endl <<
	   "CountyID: " << county.getCountyId() << endl <<
	   "number of reps : " << county.getNumOfRep() << endl;
    return os;
}