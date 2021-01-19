#include "SimpleElection.h"

void SimpleElection::AddCitizen(Citizen& add,int& CountyNum )
{
    CountyNum = 1;
    //check if the citizen exist
    if (SearchId(add.getId()) == true)
	   throw ExceptionCitizenAlreadyExists();
    if (CountyNum > eligibleCitizenList.size() || CountyNum < 1)
    {
	   throw  ExceptionWrongCountyNum();
    }
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum - 1)->AddCitizen(add);//check if we need to do -1
   
   
}

void SimpleElection::printCitizens()
{
    
	   cout << "Citizen List : " << endl;
	   eligibleCitizenList[0]->printList();
}

void SimpleElection::PrintResultByCounty()
{	  
    int  numOfRepByCounty;
    for (int i = 0; i < CountyArr.size(); i++)
    {
	   numOfRepByCounty = CountyArr.getCounty(i)->getNumOfRep();
	   cout << "the state  have "<< numOfRepByCounty <<" Representatives"<< endl;
	   CountyArr.getCounty(i)->SetElectorsToParty(PartyArr);
	   CountyArr.getCounty(i)->PrintRepByCounty(PartyArr);
    }
	
}

void SimpleElection::PrintElection()
{
    printDate();
    PrintResultByCounty();
}

void SimpleElection::save(const string fileName) const
{
    ofstream outFile(fileName, ios::binary | ios::trunc);

    if (!outFile) {
	   cout << "error outfile" << endl;
	   return;
    }

    int type = simpleElection;
    outFile.write(rcastcc(&type), sizeof(int));//type of election	  
    outFile.write(rcastcc(&day), sizeof(int));//date
    outFile.write(rcastcc(&month), sizeof(int));
    outFile.write(rcastcc(&year), sizeof(int));
    outFile.write(rcastcc(&NumOfRep), sizeof(int));
    int logicSize = eligibleCitizenList.size();
    outFile.write(rcastcc(&logicSize), sizeof(int));//num of counties
   /* outFile.write((const char*)&physical, sizeof(int));*///physical size of countyArr

    CountyArr.save(outFile);//write counties to file
    PartyArr.save(outFile);//write parties to file

    outFile.close();//close file at the end.
}

