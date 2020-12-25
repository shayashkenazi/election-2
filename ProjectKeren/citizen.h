#pragma once
//#include "County.h"
#define _CRT_SECURE_NO_WARNING
#include <iostream>
using namespace std;

class County ;

class Citizen {
private:
    char* name = nullptr;
    long id;
    unsigned int yearOfBirth;
    County* county;
    bool isVoted;

public:
    Citizen(const char* _name, long _id, unsigned int _yearOfBirth) ;//, unsigned int _countyNum);
    Citizen(const Citizen& other);
    ~Citizen();
    const char* getName() const { return name; }
    const long getId() const { return id; }
    const County& getCounty() const  { return *(county); }
          County& getCounty()        { return *(county); }

    unsigned int getyearOfBirth() const { return yearOfBirth; }
    //const unsigned int getCountyNum()const {return countyNum;}
    bool getIsVoted() const{ return isVoted; }
    
    bool setCounty(County* cty) { county = cty; return true; }
    
    Citizen& operator=(const Citizen& add);
    friend std::ostream& operator<<(std::ostream& os, const Citizen& citizen);

    bool setVote();

};
