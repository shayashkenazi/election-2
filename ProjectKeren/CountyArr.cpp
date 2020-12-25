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

bool CountyArr::addCounty( County& add)
{
    counties[logic] = new County(add);

	   logic++;
    if (logic == physical - 1) {
	   physical *= 2;
	   County** tmp = new County*[physical];
	   for (int i = 0; i < logic; i++)
		  tmp[i] = counties[i];
	   delete []counties;
	   counties = tmp;
    }
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
    

