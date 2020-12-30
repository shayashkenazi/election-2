#include "UnifiedCounty.h"

#include"PartyArr.h"


bool UnifiedCounty::SetElectorsToParty(PartyArr& PartyArray)
{
    MostVotedParty(); // update the index of most voted party at the county
    PartyArray.getPartyRef(MaxPartyVotesIndex).SetElectors(NumOfRep); // set all the electors to specific county                   
    return true;
}

void UnifiedCounty::PrintRepByCounty(PartyArr& PartyArray)
{
    cout << "the lead candidate of party is" << endl << PartyArray.getPartyRef(MaxPartyVotesIndex).getLeadCand() << endl
	   << "the percent of voters is " << getNumOfVotes() /(float)eligibleCitizen.size() * 100 << "%" << endl;
    int countLoopRep;
    if (getNumOfVotes() == 0) {
	   cout << "no one has voted in this county " << endl;
	   return;
    }
    for (int i = 0; i < PartyArray.size(); i++)
    {
	   cout << "The " << PartyArray.getPartyRef(i).getPartyName() << "party "  ;
	   countLoopRep = getNumOfElectors(i);
	   cout << " get " << countLoopRep << "Representatives , that mean as " << ((float)getVoteByIdx(i) / (float)getNumOfVotes()) * 100 << "%" << endl;
	   PartyArray.getPartyRef(i).pritnRepByIdx(countLoopRep,getCountyId());
    }

}
void UnifiedCounty::save(ofstream& outFile) const {
    int lenOfName = strlen(CountyName);
    int type = unifiedCounty;
    outFile.write((const char*)&type, sizeof(int));
    outFile.write((const char*)&lenOfName, sizeof(int));
    outFile.write((const char*)&CountyName, sizeof(char) * lenOfName);
    outFile.write((const char*)&NumOfRep, sizeof(int));
    outFile.write((const char*)&voteArrayLogic, sizeof(int));
    outFile.write((const char*)&VoteCountyArray, sizeof(int) * voteArrayLogic);
    int NumOfCitizens = eligibleCitizen.size();
    outFile.write((const char*)&NumOfCitizens, sizeof(int));
    eligibleCitizen.save(outFile);
}