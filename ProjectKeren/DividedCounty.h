#pragma once
#include "County.h"


class DividedCounty :    public County
{
    private:

    public:
        virtual bool SetElectorsToParty(PartyArr& PartyArray) override ;
        virtual void PrintRepByCounty(PartyArr& PartyArray) override;

        DividedCounty(const char* _name, int& _numofreps) : County(_name, _numofreps) {};
        DividedCounty(County& county) : County(county) {};
       
        
    
};

