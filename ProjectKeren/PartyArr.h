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

    //setters//
    bool AddParty(Party& add);//add new party to parties array.
    bool setLeadToParty(int& idParty, Citizen& Lead) { return parties[idParty].setLeadCand(Lead); }
  
    //getters//
    Party& getPartyRef(int idx) { return parties[idx]; }//return specific party.
    const int size() const { return logic; }
    const int length() const { return physical; }
    void printPartyByOrder();
    const Party& GetWinnerParty()const ;

    //operators//
    const PartyArr& operator=(const PartyArr& other);// op = 
    void save(ofstream& outFile) const;
};

