#pragma once
#include "Election.h"
//#include "DividedCounty.h"

class RegularElection :    public Election
{
public:
    RegularElection(int& day, int& month, int& year) : Election(day, month, year) {}// use Eletion's base ctor.
    

    virtual void PrintResultByCounty() override;
    virtual void printCitizens() override;
    virtual bool AddCitizen(Citizen& add, int& CountyNum) override;//add new citizen to specific county.

    virtual void save(const char* fileName) const;

};

