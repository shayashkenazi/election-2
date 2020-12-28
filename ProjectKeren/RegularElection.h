#pragma once
#include "Election.h"
#include "DividedCounty.h"

class RegularElection :    public Election
{

    RegularElection(int& day, int& month, int& year) : Election(day, month, year)// use Eletion's base ctor.
    {};
};

