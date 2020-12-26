#pragma once
#include "CitizenArr.h"

#include <iostream>
#define _CRT_SECURE_NO_WARNING

using namespace std;
class County
{
private:
    char* CountyName=nullptr;
    int NumOfRep;//represenative
    CitizenArr eligibleCitizen;//eligible citiizen for spefific county
    static int countySerialNumber;
    int countyId;
    int voteArrayLogic=0, voteArrayPhy=2, numOfVotes = 0;
    int* VoteCountyArray = nullptr; //how much votes per party
    int* HelpIntArray = nullptr;
    float* restArrayVoters = nullptr;
    int MaxPartyVotesIndex;
     //float percentvoter;
    //bool addOneRep = false;
public:
    County(char* _CountyName, int _NumOfRep);
    County();
    County(const County& other);
    ~County();
    //setters//

    bool AddCitizen(Citizen& add) { return eligibleCitizen.addCitizen(add); }
    bool setMaxPartyVotesIndex(int& PartyIdx) { MaxPartyVotesIndex = PartyIdx; return true; }
    bool setVoteById(int& idx) { VoteCountyArray[idx] = -1; return true; }//when we count the number of votes , insert -1
    bool ResizeVoteArray();// update the size of array
    bool UpdateVoteArray(int& partyIdx) { VoteCountyArray[partyIdx - 1]++; numOfVotes++; return true; }//update after vote
    bool UpdateVoteArrayToRep();
    bool UpdateRestArrayVoters();
    void MostVotedParty();

    //getters//
    const char* getName() const { return CountyName; }
    const int getNumOfRep() const { return NumOfRep; }
    int getCountyId() const { return countyId; }
    int getNumOfVotes() const { return numOfVotes; }
    int getHelperByIdx(int& idx)const { return HelpIntArray[idx]; }
    int getVoteByIdx(int& idx)const { return VoteCountyArray[idx]; }
    int getMaxPartyVotesIndex() { return MaxPartyVotesIndex; }
    int getSizeOfEligiblE()const { return eligibleCitizen.size(); }
    int FindMaxValueIdx();
    CitizenArr* getCitizenList() { return &eligibleCitizen; }
    bool InitVoteArray(const int& CurNumOfParties);

    //operators//
    friend std::ostream& operator<<(std::ostream& os, const County& county); //cout op
    const County& operator=(const County& other);// oprator "="
};

