#include "SimpleElection.h"

bool SimpleElection::AddCitizen(Citizen& add,int& CountyNum )
{
    CountyNum = 1;
    //check if the citizen exist
    if ((SearchId(add.getId()) == true) || CountyNum > logic || CountyNum < 1)
    {
	   return false;
    }
    add.setCounty(CountyArr.getCounty(CountyNum - 1));
    CountyArr.getCounty(CountyNum - 1)->AddCitizen(add);//check if we need to do -1
   
    return true;
}

void SimpleElection::printCitizens()
{
    
	   cout << "Citizen List : " << endl;
	   eligibleCitizenList[0]->printList();
}

void SimpleElection::PrintResultByCounty()
{
	   cout << "Were in simple election hence no counties ." << endl; 
}

void SimpleElection::save(const char* fileName) const
{
    ofstream outFile(fileName, ios::binary | ios::trunc);

    if (!outFile) {
	   cout << "error outfile" << endl;
	   return;
    }

    int type = simpleElection;
    outFile.write((const char*)&type, sizeof(int));//type of election	  
    outFile.write((const char*)&day, sizeof(int));//date
    outFile.write((const char*)&month, sizeof(int));
    outFile.write((const char*)&year, sizeof(int));
    outFile.write((const char*)&NumOfRep, sizeof(int));
    outFile.write((const char*)&logic, sizeof(int));//num of counties
   /* outFile.write((const char*)&physical, sizeof(int));*///physical size of countyArr

    CountyArr.save(outFile);//write counties to file
    PartyArr.save(outFile);//write parties to file

    outFile.close();//close file at the end.
}

