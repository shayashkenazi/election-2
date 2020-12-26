#include "Election.h"
#include <iostream>
using namespace std;
Election::Election() : day(-1),month(-1),year(-1)
{
    logic = 0;
    physical = 2;
    eligibleCitizenList = new CitizenArr*[physical];
}
Election::~Election()
{
    delete[] eligibleCitizenList;
}


bool Election::AddCounty(County& add)
{
    if (CountyArr.addCounty(add) == false)
	   return false;
    
    return AddCitizenList(add);    
}

bool Election::AddCitizen(Citizen& add,int& CountyNum)
{
    //check if the citizen exist
    if ((SearchId(add.getId()) == true)|| CountyNum > logic ||CountyNum < 1)
    {
	   return false;
    }
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum-1)->AddCitizen(add);//check if we need to do -1
	return true;
}

Election::Election(int _day, int _month, int _year): day(_day), month(_month), year(_year)
{
    logic = 0;
    physical = 2;
    eligibleCitizenList = new CitizenArr*[physical];
}

bool Election::AddCitizenList(County& add)
{
    eligibleCitizenList[logic] = CountyArr.getCounty(add.getCountyId() - 1)->getCitizenList();
   logic++;
    if (logic == physical - 1) 
    {
	   physical *= 2;
	   CitizenArr** tmp = new CitizenArr*[physical];
	   for (int i = 0; i < logic; i++)
		  tmp[i] = eligibleCitizenList[i];
	   delete[] eligibleCitizenList;//check if all the pratim btoh arr is delete
	   eligibleCitizenList = tmp;
	}
	   return true;
}

bool Election::addParty(Party& add)
{
   
    CountyArr.updateCountyVoteArray();//update the array party vote
    return PartyArr.AddParty(add);
}


bool Election::SearchId(const long& id)
{
    for (int i = 0; i < logic; i++)
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
	   for (int i = 0; i < logic;i++)
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
   
void Election::printCitizens()
{
    cout << "Citizen List : " << endl;
    for (int i = 0; i < logic; i++)
    {
	   cout << "Citizens of county number : " << i+1 << endl;
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
    int indexMaxParty,numOfRepByCounty;
    County res;
    //int partyIdxW;//Party id of the most votes at spesicif county
    for (int i = 0; i < CountyArr.size(); i++)
    {
	   numOfRepByCounty = CountyArr.getCounty(i)->getNumOfRep();
	   cout << "  County number :" << i+1 << endl
		  << " have  number of Representatives  : " << numOfRepByCounty << endl;
	 
	   CountyArr.getCounty(i)->MostVotedParty();//update the max index party voted
	  
	   indexMaxParty = CountyArr.getCounty(i)->getMaxPartyVotesIndex();
	   PartyArr.getPartyRef(indexMaxParty).SetElectors(numOfRepByCounty);
	   res =*CountyArr.getCounty(i);
	   cout << " the lead candidate of party at specific county is " << res << endl
		  << " the percent of voters at the county is  " << CountyArr.getCounty(i)->getNumOfVotes() / CountyArr.getCounty(i)->getSizeOfEligiblE() * 100<< "%" << endl;
	   
	   PrintListRep(CountyArr.getCounty(i));
	   
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
	   cout << " Party number : " << i+1;
	   countLoopRep = county->getHelperByIdx(i);	   	
	   cout << " get " << countLoopRep << " Representatives , that mean as " << (county->getVoteByIdx(i) /(float) county->getNumOfVotes()) * 100 <<"%"<< endl;
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
		    //CountyArr.getCounty(k).setVoteById(i);//insert -1 after we count the votes
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
   
    PrintResultByCounty();
    PrintResultByParty();
   /* cout << " County number : " 
	   name is :" <<  "num of electors is " 
	   << " and the lead candidate is :" <<
	   cout << "The rep list "<< endl;
	   */
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
	   cout << " citizen NOT found " << endl;
	   return false;
    }
    return PartyArr.getPartyRef(PartyId - 1).addRep(ptrToRep, CountyNum);
}

