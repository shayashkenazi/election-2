#pragma once
#include "Election.h"
#include "DividedCounty.h"
class SimpleElection :    public Election
{
    private:
        int NumOfRep;
    public:
        SimpleElection(int& day, int& month, int& year, int& numOfreps);
   
        ~SimpleElection(){}
        SimpleElection(int& day, int& month, int& year, int& numOfreps, ifstream& inFile) : Election(day, month, year), NumOfRep(numOfreps)
        { LoadElecFromFile(inFile); }//file ctor
        virtual void AddCounty(County& add);
       
        virtual void AddCitizen(Citizen& add, int& CountyNum) override ;//add new citizen to specific county.
        virtual void printCitizens() override;
        virtual void printCounties() { throw noCountiesSimpleElectionException(); }
        virtual void PrintResultByCounty()override ;
        virtual void PrintElection()  override;

        virtual void save(const string fileName) const override;
       
};

