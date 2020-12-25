#pragma once

#include"Party.h"
#define _CRT_SECURE_NO_WARNING

class PartyArr
{
private:
    Party* parties=nullptr;
    int physical;
    int logic;

public:
    PartyArr();
    ~PartyArr();
    bool AddParty(Party& add);
    bool setLeadToParty(int& idParty, Citizen& Lead) { return parties[idParty].setLeadCand(Lead); }
    //void add_party_to_tail(Party& add);
   Party& getPartyRef(int idx) { return parties[idx]; }

    const int size() const { return logic; }
    const int length() const { return physical; }
    void printPartyByOrder();
   // bool setElectorsToParty(int& partyIdx, int& numOfElectors,int& countyIdx) { return parties[partyIdx].SetElectors(numOfElectors,countyIdx); }
   // bool InitElectorsArray(int& CountyId);
    const Party& GetWinnerParty()const ;
};

