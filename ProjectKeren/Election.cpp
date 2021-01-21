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
}


void Election::AddCounty(County& add)
{
  
}

void Election::AddCitizen(Citizen& add,int& CountyNum)
{
    //check if the citizen exist
    if (year - add.getyearOfBirth() < 18)
	   throw  InvalidYearOfBirthException();
	if (SearchId(add.getId()) == true)
		throw CitizenAlreadyExistsException();
	if (CountyNum > eligibleCitizenList.size() || CountyNum < 1)
	    throw  WrongCountyNumException();
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum-1)->AddCitizen(add);
	
}

Election::Election(int _day, int _month, int _year): day(_day), month(_month), year(_year)
{
    if (_year < 1)
    {
	   throw WrongYearDateException();
    }
    if (_month < 1 || _month > 12) {
	   throw WrongMonthDateException();
    }
   
    if (_month == February && (_month < 0 || _day> 28))
    {
	   throw WrongDayDateException();
    }
    if ((_month == January || _month == March || _month == May || _month == July || _month == August || _month == October || _month == December) && (_month > 31 || _month < 0))
    {
	   throw WrongDayDateException();
    }
    if ((_month == April || _month == June || _month == September || _month == November) && (_month > 30 || _month < 0))
    {
	   throw WrongDayDateException();
    }
}

bool Election::AddCitizenList(County& add)
{
	CitizenArr* toAdd =CountyArr.getCounty(add.getCountyId() - 1)->getCitizenList();
	eligibleCitizenList.push_back(toAdd);
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
    if (PartyArr.size() == 0)
	   throw NoPartiesException();
    cout << "Parties List" << endl;
    PartyArr.printPartyByOrder();
}

void Election::addVote(long& id, int PartyId)
{
    if (PartyArr.size() < PartyId )
    {
		throw WrongPartyIndexException();
    }
    Citizen* ptrToVoter = PtrCitizenById(id);
    if (ptrToVoter == nullptr)
    {
		throw WrongIdException();
    }
    if ((ptrToVoter)->setVote() == false)
    {
		throw CitizenAleardyVotedException();
    }
    
    ptrToVoter->getCounty().UpdateVoteArray(PartyId);
   
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
    if (CountyArr.size() == 0 || PartyArr.size() == 0)
	   throw ShowResultException();
 
    if (CountyArr.getTotalNumOfVotes() == 0)
	   throw NoVotesException();
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

void Election:: UpdateRepArray(long& id, int& CountyNum, int& PartyId)
{
	if (PartyArr.size() < PartyId)
		throw WrongPartyIndexException();
	if (CountyArr.size() < CountyNum)
		throw WrongCountyNumException();
	if (PartyArr.getPartyRef(PartyId - 1).getLeadCand().getId() == id)
		throw LeadCandAsRepException();
 
    Citizen* ptrToRep = PtrCitizenById(id);
	if (ptrToRep == nullptr)
		throw WrongIdException();
   PartyArr.getPartyRef(PartyId - 1).addRep(ptrToRep, CountyNum);

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
