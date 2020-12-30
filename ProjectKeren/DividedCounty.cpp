#include "DividedCounty.h"
#include"PartyArr.h"

bool DividedCounty::SetElectorsToParty(PartyArr& PartyArray)
{
    for (int i = 0; i < PartyArray.size(); i++)
    {
        PartyArray.getPartyRef(i).SetElectors(ElectorsByIdx[i]); 
    }
    return true;
}
  void DividedCounty::save(ofstream& outFile) const {
	 int lenOfName = strlen(CountyName);
	 int type = dividedCounty;
	 outFile.write((const char*)&type, sizeof(int));
	 outFile.write((const char*)&lenOfName, sizeof(int));
	 outFile.write((const char*)&CountyName, sizeof(char)* lenOfName);
	 outFile.write((const char*)&voteArrayLogic, sizeof(int));
	 outFile.write((const char*)&VoteCountyArray, sizeof(int)* voteArrayLogic);
	 int NumOfCitizens = eligibleCitizen.size();
	 outFile.write((const char*)&NumOfCitizens, sizeof(int));
	 eligibleCitizen.save(outFile);
}

void DividedCounty::PrintRepByCounty(PartyArr& PartyArray)
{
    int countLoopRep;
    if (getNumOfVotes() == 0) {
	   cout << "no one has voted in this county " << endl;
	   return;
    }
    cout << "The list of lead candidates that got representative : "  << endl;
    int maxInx =0, maxReps = ElectorsByIdx[0];
    for (int i = 0; i < PartyArray.size(); i++)
    {
	   for (int k = 0; k < PartyArray.size(); k++)
	   {
		  countLoopRep = getNumOfElectors(k);
		  if (countLoopRep > maxReps)
		  {
			 maxReps = countLoopRep;
			 maxInx = i;
		  }
	   }

	   if (maxReps > 0) {
		  cout << "the lead candidate of party - "<< PartyArray.getPartyRef(maxInx).getPartyName() <<
			 " is: " << PartyArray.getPartyRef(maxInx).getLeadCand().getName() << endl;

		  cout << "the party got " << maxReps << "Representatives" << endl;
		 
	   }    
	   ElectorsByIdx[maxInx] = -1;
    }
}
