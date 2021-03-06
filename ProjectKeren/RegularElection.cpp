#include "RegularElection.h"

void RegularElection::AddCitizen(Citizen& add, int& CountyNum)
{
    //check if the citizen is less than 18 years old
    if ((year - (int)add.getyearOfBirth()) < 18)
	   throw  InvalidYearOfBirthException();
    //check if the citizen exist
    if (SearchId(add.getId()) == true)
	   throw CitizenAlreadyExistsException();
    if (CountyNum > eligibleCitizenList.size() || CountyNum < 1)
    {
	   throw  WrongCountyNumException();
    }
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum - 1)->AddCitizen(add);//check if we need to do -1
   
}
void RegularElection::printCitizens()
{  
    if (eligibleCitizenList.size() == 0)
	   throw NoCitizensException();
    cout << "Citizen List : " << endl;
     
    for (int i = 0; i < eligibleCitizenList.size(); i++)
    {
	   cout << "Citizens of county number : " << i + 1 << endl;
	   try {
		  eligibleCitizenList[i]->printList();
	   }
	   catch (logic_error& error)
	   {
		  cout << error.what() << endl;
	   }
    }
}
void RegularElection::PrintResultByCounty()
{
    int  numOfRepByCounty;
    for (int i = 0; i < CountyArr.size(); i++)
    {
	   numOfRepByCounty = CountyArr.getCounty(i)->getNumOfRep();
	   cout << "County number :" << i + 1 << endl
		  << "have  number of Representatives  : " << numOfRepByCounty << endl;
	   CountyArr.getCounty(i)->SetElectorsToParty(PartyArr);
	   try {
		  CountyArr.getCounty(i)->PrintRepByCounty(PartyArr);
	   }
	   catch (logic_error& error)
	   {
		  cout << error.what() << endl;
	   }
	}
}
void RegularElection::PrintElection()
{
    if (CountyArr.size() == 0 || PartyArr.size() == 0)
	   throw ShowResultException();

    if (CountyArr.getTotalNumOfVotes() == 0)
	   throw NoVotesException();

    printDate();
    PrintResultByCounty();
    PrintResultByParty();
}
void RegularElection::AddCounty(County& add)
{
    CountyArr.addCounty(add, PartyArr.size());
      
     AddCitizenList(add);
}
void RegularElection::save(const string fileName) const
{
    ofstream outFile(fileName, ios::binary | ios::trunc);

    if (!outFile.good()) {
        throw OpenFileException();
    }
    int type = regularElection;
    outFile.write(rcastcc(&type), sizeof(int) );//type of current election
    outFile.write(rcastcc(&day), sizeof(int));//write date of election.
    outFile.write(rcastcc(&month), sizeof(int));
    outFile.write(rcastcc(&year), sizeof(int));
    int logicSize = eligibleCitizenList.size();
    outFile.write(rcastcc(&logicSize), sizeof(int));/// write number of counties
    
    CountyArr.save(outFile);//write counties
    PartyArr.save(outFile);//write parties to file.

    outFile.close();
}

