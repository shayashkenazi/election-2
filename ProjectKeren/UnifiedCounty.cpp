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
	    
	   cout << "the lead candidate of party is: " << endl << PartyArray.getPartyRef(MaxPartyVotesIndex).getLeadCand() << endl
		  << "the party got  " << getNumOfVotes() / (float)eligibleCitizen.size() * 100 << "%" << " of the votes " << endl;    
    int countLoopRep;
    if (getNumOfVotes() == 0) {
	   cout << "no one has voted in this county " << endl;
	   return;
    }
    for (int i = 0; i < PartyArray.size(); i++)
    {
	   cout << "The " << PartyArray.getPartyRef(i).getPartyName() << " party "  ;
	   countLoopRep = getNumOfElectors(i);
	   cout << " got " << countLoopRep << " Representatives ,with " << ((float)getVoteByIdx(i) / (float)getNumOfVotes()) * 100 << "% of the votes" << endl;
	   PartyArray.getPartyRef(i).pritnRepByIdx(countLoopRep,getCountyId());
    }

}
void UnifiedCounty::save(ofstream& outFile) const {
    int lenOfName = CountyName.size();
    int type = unifiedCounty;
    outFile.write(rcastcc(&type), sizeof(int));
    outFile.write(rcastcc(&lenOfName), sizeof(int));
    outFile.write(rcastcc(&CountyName[0]), sizeof(char) * lenOfName);
    outFile.write(rcastcc(&NumOfRep), sizeof(int));
    outFile.write(rcastcc(&numOfVotes), sizeof(int));
    int voteArrayLogic = VoteCountyArray.size();
    outFile.write(rcastcc(&voteArrayLogic), sizeof(int));
    outFile.write(rcastcc(&VoteCountyArray[0]), sizeof(int) * voteArrayLogic);
    int NumOfCitizens = eligibleCitizen.size();
    outFile.write(rcastcc(&NumOfCitizens), sizeof(int));
    eligibleCitizen.save(outFile);
}
