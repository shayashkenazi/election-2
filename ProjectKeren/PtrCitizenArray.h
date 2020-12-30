#pragma once

#include"citizen.h"
#define _CRT_SECURE_NO_WARNING

class PtrCitizenArray
{
private:
    Citizen** citizens;
    int logic;
    int physical;
public:
    PtrCitizenArray();
    ~PtrCitizenArray();
    //setters//
    bool addPtrToCitizen ( Citizen* add);//save existing citizen by his adress , as party's rep.
   
    //getters//
    const int size() const { return logic; }//return logic size.
    const int length() const { return physical; }// retuen physical size.
    Citizen& getCitizen(int idx) const { return *(citizens[idx]); }//get ref to specific citizen.

    //operators//
    friend std::ostream& operator<<(std::ostream& os, const PtrCitizenArray& listrep);//cout op
	const PtrCitizenArray& operator=(const PtrCitizenArray& other);
	void save(ofstream& outFile) const;

};


