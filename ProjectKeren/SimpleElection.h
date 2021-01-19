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
            string name = "divCounty";
            try {
                County* newcounty = new DividedCounty(name, numOfreps);
                CountyArr.addCounty(*newcounty, PartyArr.size());

                AddCitizenList(*newcounty);
                delete newcounty;
            }
            catch (bad_alloc& msg)
            {
                cout << msg.what() << endl;
                exit(0);
            }
            
        }
        ~SimpleElection(){}
        SimpleElection(int& day, int& month, int& year, int& numOfreps, ifstream& inFile) : Election(day, month, year), NumOfRep(numOfreps)
        { LoadElecFromFile(inFile); }//file ctor
        virtual void AddCounty(County& add);
       
        virtual void AddCitizen(Citizen& add, int& CountyNum) override ;//add new citizen to specific county.
        virtual void printCitizens() override;

        virtual void PrintResultByCounty()override ;
        virtual void PrintElection()  override;

        virtual void save(const string fileName) const override;
       
};

