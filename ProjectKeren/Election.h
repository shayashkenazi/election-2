#pragma once
#include"PartyArr.h"
#include"CountyArr.h"
#define _CRT_SECURE_NO_WARNING


class Election
{
private:
    int day, month, year;
    int logic, physical;
    CitizenArr** eligibleCitizenList = nullptr;
    PartyArr PartyArr ;
    CountyArr CountyArr ;
public:
    Election();
    ~Election();
    Election(int _day, int _month, int _year);
    //setters//
    bool AddCounty(County& add);//num1
    bool AddCitizenList(County& add);// add list citizen to eligibleCitizenList help for num1

    bool AddCitizen(Citizen& add, int& CountyNum);//num 2
    bool addParty(Party& add);//num3
   
    bool UpdateRepArray(long& id, int& CountyNum, int& PartyId);

    bool SearchId(const long& id);
    Citizen*  PtrCitizenById( long& id);
    void printCounties();
    
    void printCitizens();

    void printParties();

    bool addVote(long& id, int PartyId);

    void PrintResultByCounty();
    void PrintListRep(County* county);
    void PrintResultByParty();
    void PrintElection();
    


    

};

