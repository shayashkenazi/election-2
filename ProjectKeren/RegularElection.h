#pragma once
#include "Election.h"
//#include "DividedCounty.h"

class RegularElection :    public Election
{
public:
    RegularElection(int& day, int& month, int& year) : Election(day, month, year) {}// use Eletion's base ctor.
    RegularElection(int& day, int& month, int& year, ifstream& inFile) : Election(day, month, year) 
    { LoadElecFromFile(inFile); }// file ctor
    ~RegularElection(){}

    virtual void PrintResultByCounty() override;
    virtual void PrintElection()  override;

    virtual void printCitizens() override;
    virtual void AddCitizen(Citizen& add, int& CountyNum) override;//add new citizen to specific county.
    virtual void save(const string fileName) const;//



};

