#pragma once

#include"Party.h"
#define _CRT_SECURE_NO_WARNING

class PartyArr
{
private:
    vector<Party> parties;

public:
    PartyArr();
    ~PartyArr();
    PartyArr(const PartyArr& other) { parties = other.parties; }//copy ctor.
    //setters//
    bool AddParty(Party& add);//add new party to parties array.
    bool setLeadToParty(int& idParty, Citizen& Lead) { return parties[idParty].setLeadCand(Lead); }
  
    //getters//
    Party& getPartyRef(int idx) { return parties[idx]; }//return specific party.
    const int size() const { return parties.size(); }
    const int length() const { return parties.size(); }
    void printPartyByOrder();
    const Party& GetWinnerParty()const ;

    //operators//
    const PartyArr& operator=(const PartyArr& other);// op = 
    void save(ofstream& outFile) const;
};

