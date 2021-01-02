#pragma once
#include "County.h"
class UnifiedCounty :   public County
{    
private:       

   public:
        
       UnifiedCounty(const char* _name, int& _numofreps) : County(_name, _numofreps) {}
       UnifiedCounty(County& other) : County(other) {}
       UnifiedCounty(istream& inFile);

        virtual bool SetElectorsToParty(PartyArr& PartyArray) override;    
        virtual void PrintRepByCounty(PartyArr& PartyArray) override;
        virtual void save(ofstream& outFile) const override;
};

