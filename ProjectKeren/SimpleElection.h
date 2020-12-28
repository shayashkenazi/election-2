#pragma once
#include "Election.h"
#include "DividedCounty.h"
class SimpleElection :    public Election
{
    public:
        SimpleElection(int& day,int& month,int& year, int& numOfreps) : Election(day, month, year)
        {
            char name[] = "divCounty";
            County* newcounty = new DividedCounty(name, numOfreps);
            AddCounty(*newcounty);
        }

        virtual bool AddCitizen(Citizen& add, int& CountyNum) override ;//add new citizen to specific county.
        virtual void printCitizens();
        virtual void PrintResulyByCounty() ;
};

