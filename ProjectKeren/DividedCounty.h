#pragma once
#include "County.h"


class DividedCounty :    public County
{
    private:

    public:

        DividedCounty(const char* _name, int& _numofreps) : County(_name, _numofreps) {}
        DividedCounty(County& add) : County(add) {}
        DividedCounty(istream& inFile);

        virtual bool SetElectorsToParty(PartyArr& PartyArray) override;
        virtual void PrintRepByCounty(PartyArr& PartyArray) override;

        virtual  void save(ofstream& outfile) const ;
    
};

