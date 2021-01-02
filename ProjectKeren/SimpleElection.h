#pragma once
#include "Election.h"
#include "DividedCounty.h"
class SimpleElection :    public Election
{
    private:
        int NumOfRep;
    public:
        SimpleElection(int& day,int& month,int& year, int& numOfreps) : Election(day, month, year)
        {
            NumOfRep = numOfreps;
            char name[] = "divCounty";
            County* newcounty = new DividedCounty(name, numOfreps);
            AddCounty(*newcounty);
        }
        SimpleElection(int& day, int& month, int& year, int& numOfreps, ifstream& inFile) : Election(day, month, year)
        { LoadElecFromFile(inFile); }//file ctor
        virtual bool AddCitizen(Citizen& add, int& CountyNum) override ;//add new citizen to specific county.
        virtual void printCitizens() override;

        virtual void PrintResultByCounty()override ;
        virtual void PrintElection()  override;

        virtual void save(const char* fileName) const override;
       
};

