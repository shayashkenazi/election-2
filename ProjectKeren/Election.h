#pragma once
#include"PartyArr.h"
#include"CountyArr.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

#define _CRT_SECURE_NO_WARNING

class Election
{
protected:
    int day, month, year;
    DynamicArray <CitizenArr*> eligibleCitizenList ;//points to the Counites eligible citizen's list.
    //save them by the county's index.
    PartyArr PartyArr ; 
    CountyArr CountyArr ;
    
public:
    Election();//default ctor.
    virtual  ~Election();
    Election(int _day, int _month, int _year);
    //setters//
    bool AddCounty(County& add);//add new county to CountyArr.
    bool AddCitizenList(County& add);//if we added new County we link his citizen's list to the main citizen list.
    bool addVote(long& id, int PartyId);//get id of citizen and party serial num. set citizen to vote for this party.
    virtual bool AddCitizen(Citizen& add, int& CountyNum)=0;//add new citizen to specific county.
    bool addParty(Party& add);//add new party to Party Arr.
    bool UpdateRepArray(long& id, int& CountyNum, int& PartyId);//set specific citizen as rep of an existing party.
    bool SearchId(const long& id);

    //getters//
    Citizen*  PtrCitizenById( long& id);
    void printCounties();
    void printDate();
    virtual void printCitizens()=0;
    void printParties();
    virtual void PrintResultByCounty()=0;
    void PrintListRep(County* county);
    void PrintResultByParty();
    virtual void PrintElection() =0 ;
    void SetEligibleListFromFile(ifstream& inFile, int CountyIdx);
    void LoadPartiesFromFile(ifstream& inFile);

    //operators//
    const Election& operator=(const Election& other);
    
    virtual void save(const string fileName) const = 0;
    virtual void LoadElecFromFile(ifstream& inFile) ;
    
};

