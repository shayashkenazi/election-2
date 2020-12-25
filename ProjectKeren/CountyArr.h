#pragma once

#include"County.h"
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
    bool addCounty(County& add);
    bool updateCountyVoteArray();
    //getters//
    const int size() const { return logic; }
    County* getCounty(int idx) { return counties[idx]; }// return ptr to specific county.
    void printCounties();// print counties by order.

};

