#include "CountyArr.h"

CountyArr::CountyArr()
{
	   counties = new County*[2];
	   logic = 0;
	   physical = 2; 
}


CountyArr::~CountyArr()
{
    delete[] counties;
}

bool CountyArr::addCounty( County& add,const int& curNumOfParties)// add new county to counties array of election.
{
  
    if (logic == physical) {
	   physical *= 2;
	   County** tmp = new County*[physical];
	   for (int i = 0; i < logic; i++)
		  tmp[i] = counties[i];
	   delete []counties;
	   counties = tmp;
    }
	counties[logic] = new County(add);
	counties[logic]->InitVoteArray(curNumOfParties);
	logic++;
	
    return true;
}

void CountyArr::printCounties()
{
	   cout << "The County List is : " << endl;
	   for (int i = 0; i < logic ; i++)
	   {
		  cout << *counties[i] << endl;
	   }
}

bool CountyArr::updateCountyVoteArray()
{
    for (int i = 0; i < logic; i++)
    {
	   counties[i]->ResizeVoteArray();
    }
    return true;
}
const CountyArr& CountyArr::operator=(const CountyArr& other)
{
	logic = other.logic;
	physical = other.physical;
	counties = new County*[physical];
	for (int i = 0; i < logic; i++)
	{
		counties[i] = other.counties[i];
	}
	return *this;
}

    

