#pragma once
//#include "County.h"
#define _CRT_SECURE_NO_WARNING
#include <iostream>
#include<string>
#include "dynamicArray.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include"enum.h"
#include "Exceptions.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

class County ;

class Citizen {
private:
    string name;
    long id;
    unsigned int yearOfBirth;
    County* county;
    bool isVoted;

public:
    Citizen(const string _name, long _id, unsigned int _yearOfBirth) ;
    Citizen(const Citizen& other);//cpy ctor.
    Citizen(ifstream& inFile);// file ctor
    ~Citizen();//dtor. delete name

    ///setters///
    bool setVote(); //change isVoted argument.
    bool setCounty(County* cty) { county = cty; return true; }// set ptr to the citizen's county.

    ///getters/
    const string getName() const { return name; }
    const long getId() const { return id; }
    const County& getCounty() const  { return *(county); }
          County& getCounty()        { return *(county); }
    const unsigned int getyearOfBirth() const { return yearOfBirth; }
    bool getIsVoted() const{ return isVoted; }
   
    //operators//
    Citizen& operator=(const Citizen& add); //operator =
    friend std::ostream& operator<<(std::ostream& os, const Citizen& citizen);//print op
    void save(ofstream& outfile) const;
    bool operator < (const Citizen& citizen) {
        return this->id < citizen.id;
    }
    bool operator> (const Citizen& citizen) {
        return this->id > citizen.id;
    }
    bool operator== (const Citizen& citizen) {
        return this->id == citizen.id;
    }
    bool operator < (const long& id) {
        return this->id < id;
    }
    bool operator> (const long& id) {
        return this->id > id;
    }
    bool operator== (const long& id) {
        return this->id == id;
    }
};
template<class T,class K>//pattern algoritem for binary search in stl::vector.
T* binarySearchPtr(vector <T *> arr, int l, int r, const K& value)
{
    if (r >= l) {
        int mid = l + (r - l) / 2;

        if (*arr[mid] == value)
            return arr[mid];
   
        if (*arr[mid] > value)
            return binarySearchPtr(arr, l, mid - 1, value);

        return binarySearchPtr(arr, mid + 1, r, value);
    }
    return nullptr;
}
