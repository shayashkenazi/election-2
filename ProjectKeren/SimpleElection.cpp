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

void SimpleElection::PrintResulyByCounty()
{
	   cout << "Were in simple election hence no counties ." << endl; 
}
