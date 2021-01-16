#include "RegularElection.h"

bool RegularElection::AddCitizen(Citizen& add, int& CountyNum)
{
    //check if the citizen exist
    if ((SearchId(add.getId()) == true) || CountyNum > logic || CountyNum < 1)
    {
	   return false;
    }
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum - 1)->AddCitizen(add);//check if we need to do -1
    return true;
}
void RegularElection::printCitizens()
{
    cout << "Citizen List : " << endl;
    for (int i = 0; i < logic; i++)
    {
	   cout << "Citizens of county number : " << i + 1 << endl;
	   eligibleCitizenList[i]->printList();
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
	   CountyArr.getCounty(i)->PrintRepByCounty(PartyArr);
    }
}
void RegularElection::PrintElection()
{
    printDate();
    PrintResultByCounty();
    PrintResultByParty();
}
void RegularElection::save(const string fileName) const
{
    ofstream outFile(fileName, ios::binary | ios::trunc);

    if (!outFile) {
	   cout << "error outfile" << endl;
	   return;
    }
    int type = regularElection;
    outFile.write(rcastcc(&type), sizeof(int) );//type of current election
    outFile.write(rcastcc(&day), sizeof(int));//write date of election.
    outFile.write(rcastcc(&month), sizeof(int));
    outFile.write(rcastcc(&year), sizeof(int));
    outFile.write(rcastcc(&logic), sizeof(int));/// write number of counties
    /*outFile.write((const char*)&physical, sizeof(int));*/
    
    CountyArr.save(outFile);//write counties
    PartyArr.save(outFile);//write parties to file.

    outFile.close();
}

