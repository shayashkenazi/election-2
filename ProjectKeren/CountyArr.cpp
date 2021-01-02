#include "CountyArr.h"
#include"DividedCounty.h"
#include"UnifiedCounty.h"
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
    if (typeid(add) == typeid(DividedCounty))
    {
	   counties[logic] = new DividedCounty(add);
    }
    else
    {
	   counties[logic] = new UnifiedCounty(add);
    }
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
	if (counties != nullptr)
		delete[] counties;
	counties = new County*[physical];
	for (int i = 0; i < logic; i++)
	{
		counties[i] = other.counties[i];
	}
	return *this;
}

void CountyArr::save(ofstream& outFile) const
{  
    //outFile.write((const char*)&logic, sizeof(int)); // write number of counties
    for (int i = 0; i < logic; i++)
    {
	   counties[i]->save(outFile); //write all the counties.
    }
}
