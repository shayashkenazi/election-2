#include "Election.h"
#include "UnifiedCounty.h"
#include"DividedCounty.h"
#include <iostream>

using namespace std;

Election::Election() : day(-1),month(-1),year(-1)
{

}
Election::~Election()
{
	for (auto s : eligibleCitizenList)
		delete s;
}


bool Election::AddCounty(County& add)
{
    if (CountyArr.addCounty(add,PartyArr.size()) == false)
	   return false;
    
    return AddCitizenList(add);    
}

bool Election::AddCitizen(Citizen& add,int& CountyNum)
{
    //check if the citizen exist
    if ((SearchId(add.getId()) == true)|| CountyNum > eligibleCitizenList.size() ||CountyNum < 1)
    {
	   return false;
    }
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum-1)->AddCitizen(add);//check if we need to do -1
	return true;
}

Election::Election(int _day, int _month, int _year): day(_day), month(_month), year(_year)
{

}

bool Election::AddCitizenList(County& add)
{
	eligibleCitizenList.push_back( CountyArr.getCounty(add.getCountyId() - 1)->getCitizenList());
	return true;
}

bool Election::addParty(Party& add)
{
	CountyArr.updateCountyVoteArray();//update the array party vote
    return PartyArr.AddParty(add);
}


bool Election::SearchId(const long& id)
{
    for (int i = 0; i < eligibleCitizenList.size(); i++)
    {
	   if (eligibleCitizenList[i]->SearchById(id) == true)
	   {
		  return true;
	   }
    }
    return false;
}

Citizen* Election::PtrCitizenById(long& id)
{
    Citizen* ptrToCit=nullptr;
	   for (int i = 0; i < eligibleCitizenList.size();i++)
	   {
		  ptrToCit = eligibleCitizenList[i]->PtrToCitizen(id);
		  if (ptrToCit != nullptr)
			 return ptrToCit;
	   }
	 
	   return ptrToCit;
}


void Election::printCounties()
{
   
    CountyArr.printCounties();
  
}

void Election::printDate()
{
    cout << "***** WELCOME TO ELECTION *****" << endl;
    cout << "***** DATE : " << day << "/" << month << "/" << year << " *****" << endl;

}
   
void Election::printCitizens()
{
    cout << "Citizen's List : " << endl;
    
    for (int i = 0; i < eligibleCitizenList.size(); i++)
    {
	   cout << "Citizens of county number : " << i+1 << "Are: "<<endl;
	   eligibleCitizenList[i]->printList();
    }
}
 
void Election::printParties()
{
    cout << "Parties List" << endl;
    PartyArr.printPartyByOrder();
}

bool Election::addVote(long& id, int PartyId)
{
    if (PartyArr.size() < PartyId )
    {
	   cout << "the party does not exist" << endl;
	   return false;
    }
    Citizen* ptrToVoter = PtrCitizenById(id);
    if (ptrToVoter == nullptr)
    {
	   cout << "the citizen does not exist" << endl;
	   return false;
    }
    if ((ptrToVoter)->setVote() == false)
    {
	   cout << "the citizen is already voted" << endl;
	   return false;
    }
    //CountyArr.updateCountyVoteArray();
    
    ptrToVoter->getCounty().UpdateVoteArray(PartyId);
    return true;	   
}


void Election::PrintResultByCounty()
{
    int numOfRepByCounty;
    for (int i = 0; i < CountyArr.size(); i++)
    {
	   numOfRepByCounty = CountyArr.getCounty(i)->getNumOfRep();
	   cout << "County number :" << i+1 << endl
		  << "have  number of Representatives  : " << numOfRepByCounty << endl;
	   CountyArr.getCounty(i)->SetElectorsToParty(PartyArr);
	   CountyArr.getCounty(i)->PrintRepByCounty(PartyArr);
    }
}

void Election::PrintListRep(County* county)
{
    int countLoopRep;
    if (county->getNumOfVotes() == 0) {
	   cout << "no one has voted in this county " << endl;
	   return;
    }    
    for (int i = 0; i < PartyArr.size(); i++)
    {
	   cout << "Party number : " << i+1;
	   countLoopRep = county->getNumOfElectors(i);	   	
	   cout << " get " << countLoopRep << "Representatives , that mean as " << ((float)county->getVoteByIdx(i) /(float) county->getNumOfVotes()) * 100 <<"%"<< endl;
	   PartyArr.getPartyRef(i).pritnRepByIdx(countLoopRep,county->getCountyId());
	}
	   	
}
void Election::PrintResultByParty()
{
    int maxElectric = PartyArr.getPartyRef(0).getSumOfElectors(), max_idx = 0,sumVotes=0 ;
    cout << "***** RESULTS *****: " << endl;
    for (int i = 0; i < PartyArr.size(); i++) {
	   for (int j = 0; j < PartyArr.size(); j++)
	   {
		  if (PartyArr.getPartyRef(j).getSumOfElectors() >= maxElectric)
		  {
			 max_idx = j;
			 maxElectric = PartyArr.getPartyRef(j).getSumOfElectors();
		  }
	   }
	   cout << "Party: " << PartyArr.getPartyRef(max_idx).getPartyName();
	   cout << " Lead Cand id: " << PartyArr.getPartyRef(max_idx).getLeadCand().getId();
		cout << " representatives: " << PartyArr.getPartyRef(max_idx).getSumOfElectors();
		for (int k = 0; k < CountyArr.size(); k++)
		{
		    sumVotes += CountyArr.getCounty(k)->getVoteByIdx(max_idx);
		    PartyArr.getPartyRef(max_idx).SetInitToZero();//insert 0 after count the votes
		}
			cout << " total votes: " << sumVotes << endl;
			sumVotes = 0;
			maxElectric = 0;
	   cout << endl;
    }
    //county.setAddOneRep(false);//reset after finish one party print list
}
void Election::PrintElection()
{
    printDate();
    PrintResultByCounty();
    PrintResultByParty();

}

void Election::SetEligibleListFromFile(ifstream& inFile,int CountyIdx)
{
	int NumOfCitizens;
  
    inFile.read(rcastc(&NumOfCitizens), sizeof(int));//num of citizens in the county
    for (int i = 0; i < NumOfCitizens; i++)
    {
	   Citizen newCitizen(inFile);
	   AddCitizen(newCitizen, CountyIdx);// add the citizen to the eligible citizen's list.
    }
}

void Election::LoadPartiesFromFile(ifstream& inFile)
{
    int numOfParties,  numOfCounties, RepLogic;
    long LeadCandid,RepId;
    inFile.read(rcastc(&numOfParties), sizeof(int));
    for (int i = 0; i < numOfParties; i++)
    {
		inFile.read(rcastc(&LeadCandid), sizeof(long));
	   Citizen* ptrToLeadCand = PtrCitizenById(LeadCandid);
	   Party newParty(inFile, *ptrToLeadCand); // use file ctor of Party.
	   addParty(newParty);
	   inFile.read(rcastc(&numOfCounties), sizeof(int));
	   for (int j = 0; j < numOfCounties; j++)// init rep array of specific party.
	   {
		  inFile.read(rcastc(&RepLogic), sizeof(int));
		  for (int k = 0; k < RepLogic; k++)
		  {
			 inFile.read(rcastc(&RepId), sizeof(long));
			 int partyId = i + 1;
			 int countyId = j + 1;
			 UpdateRepArray(RepId, countyId, partyId);
		  }
	   }
    }
}

bool Election:: UpdateRepArray(long& id, int& CountyNum, int& PartyId)
{
    if (PartyArr.size() < PartyId || CountyArr.size() < CountyNum)
    {
	   cout << "wrong county ID or party NUM " << endl;

	   return false;
    }
    if (PartyArr.getPartyRef(PartyId - 1).getLeadCand().getId() == id)
    {
	   cout << "the Lead Candidate can NOT be A represent in a specific county" << endl;
	   return false;
    }
    
    Citizen* ptrToRep = PtrCitizenById(id);
    if (ptrToRep == nullptr)
    {
	   cout << "citizen NOT found " << endl;
	   return false;
    }
    return PartyArr.getPartyRef(PartyId - 1).addRep(ptrToRep, CountyNum);

}
const Election& Election::operator=(const Election& other) {
	day = other.day;
	month = other.month;
	year =other.year;
	eligibleCitizenList = other.eligibleCitizenList;
	CountyArr = other.CountyArr;
	PartyArr = other.PartyArr;
	return *this;
}

void Election::LoadElecFromFile(ifstream& inFile)
{
	int NumOfCounties, type;
    inFile.read(rcastc(&NumOfCounties), sizeof(int));//number of counties
    for (int i = 0; i < NumOfCounties; i++)
    {
	   inFile.read(rcastc(&type), sizeof(int));//read the type of county
	   if (type == unifiedCounty)//check type of County
	   {
		  UnifiedCounty county(inFile);//use file ctor
		  county.CreateVoteArrayFromFile(inFile);//set vote array from file
		  AddCounty(county);
	   }
	   else// its divided County
	   {
		  DividedCounty county(inFile);//use file ctor
		  county.CreateVoteArrayFromFile(inFile);//set vote array from file.
		  AddCounty(county);//add county to CountyArr.
	   }
	   SetEligibleListFromFile(inFile, i + 1);//load citizen's list for specific county.
	  
    }
    LoadPartiesFromFile(inFile);//load parties after loading counties and citizen's.
    inFile.close();
}
