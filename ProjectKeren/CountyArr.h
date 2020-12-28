#pragma once

#include"County.h"
class DividedConty;
class UnifiedCounty;
#define _CRT_SECURE_NO_WARNING

class CountyArr
{
private:
    County** counties = nullptr;
    int physical;
    int logic;
public:
    CountyArr();
    ~CountyArr();
    //setters//
    bool addCounty(County& add, const int& curNumOfParties);
    bool updateCountyVoteArray();
    //getters//
    const int size() const { return logic; }
    County* getCounty(int idx) { return counties[idx]; }// return ptr to specific county.
    void printCounties();// print counties by order.

    //operators//
    const CountyArr& operator=(const CountyArr& other);// operator "="
};

