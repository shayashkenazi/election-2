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
    bool addPtrToCitizen ( Citizen* add);
    const int size() const { return logic; }
    const int length() const { return physical; }
    Citizen& getCitizen(int idx) const { return *(citizens[idx]); }
    friend std::ostream& operator<<(std::ostream& os, const PtrCitizenArray& listrep);
	const PtrCitizenArray& operator=(const PtrCitizenArray& other);
};


