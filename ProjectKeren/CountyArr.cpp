#include "CountyArr.h"
#include"DividedCounty.h"
#include"UnifiedCounty.h"
CountyArr::CountyArr()
{
}


CountyArr::~CountyArr()
{
	for (auto county : counties)
		delete county;//copy c'tor of survivor
}

bool CountyArr::addCounty( County& add,const int& curNumOfParties)// add new county to counties array of election.
{
    if (typeid(add) == typeid(DividedCounty))
    {
	   counties.push_back( new DividedCounty(add));
    }
    else
    {
	   counties.push_back( new UnifiedCounty(add));
    }
	counties.back()->InitVoteArray(curNumOfParties);
    return true;
}

CountyArr::CountyArr(const CountyArr& other)
{
	for (auto county : other.counties)
	{
		county->getCountyType().compare("Divided County") == 0 ? counties.push_back(new DividedCounty(*county))
			: counties.push_back(new UnifiedCounty(*county));
	}
}
void CountyArr::printCounties()
{
	   cout << "The County List is : " << endl;
	   for (int i = 0; i < counties.size() ; i++)
	   {
		  cout << *counties[i] << endl;
	   }
}

bool CountyArr::updateCountyVoteArray()
{
    for (int i = 0; i < counties.size(); i++)
    {
	   counties[i]->ResizeVoteArray();
    }
    return true;
}
const CountyArr& CountyArr::operator=(const CountyArr& other)
{
	if (this != &other) {
		for (auto county : counties)
			delete county;//copy c'tor of survivor
		for (auto county : other.counties)
		{
			county->getCountyType().compare("Divided County") == 0 ? counties.push_back(new DividedCounty(*county)) 
				: counties.push_back(new UnifiedCounty(*county));
		}
		
	}

	return *this;
}

void CountyArr::save(ofstream& outFile) const
{  
    //outFile.write((const char*)&logic, sizeof(int)); // write number of counties
    for (int i = 0; i < counties.size(); i++)
    {
	   counties[i]->save(outFile); //write all the counties.
    }
}
