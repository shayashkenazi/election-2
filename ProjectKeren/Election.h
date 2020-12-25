#pragma once
#include"PartyArr.h"
#include"CountyArr.h"
#define _CRT_SECURE_NO_WARNING


class Election
{
private:
    int day, month, year;
    int logic, physical;
    CitizenArr** eligibleCitizenList = nullptr;//points to the Counites eligible citizen's list.
    //save them by the county's index.
    PartyArr PartyArr ; 
    CountyArr CountyArr ;
public:
    Election();//default ctor.
    ~Election();
    Election(int _day, int _month, int _year);
    //setters//
    bool AddCounty(County& add);//add new county to CountyArr.
    bool AddCitizenList(County& add);//if we added new County we link his citizen's list to the main citizen list.
    bool addVote(long& id, int PartyId);//get id of citizen and party serial num. set citizen to vote for this party.
    bool AddCitizen(Citizen& add, int& CountyNum);//add new citizen to specific county.
    bool addParty(Party& add);//add new party to Party Arr.
    bool UpdateRepArray(long& id, int& CountyNum, int& PartyId);//set specific citizen as rep of an existing party.
    bool SearchId(const long& id);

    //getters//
    Citizen*  PtrCitizenById( long& id);
    void printCounties();
    
    void printCitizens();
    void printParties();
    void PrintResultByCounty();
    void PrintListRep(County* county);
    void PrintResultByParty();
    void PrintElection();
   // todo: election = operator.
};

