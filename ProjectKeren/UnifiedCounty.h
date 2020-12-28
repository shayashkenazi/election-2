#pragma once
#include "County.h"
class UnifiedCounty :    public County
{    

    public:
        virtual bool SetElectorsToParty(PartyArr& PartyArray) override;    
        virtual void PrintRepByCounty(PartyArr& PartyArray) override;

};

