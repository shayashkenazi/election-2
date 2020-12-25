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
    bool addCounty(County& add);

    const int size() const { return logic; }
    const int length() const { return physical; }//lo korim leze
    County* getCounty(int idx) { return counties[idx]; }
    void printCounties();
    bool updateCountyVoteArray();

};

