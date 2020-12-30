#pragma once

#include"citizen.h"

#define _CRT_SECURE_NO_WARNING

class CitizenArr
{
private:
    Citizen** citizens=nullptr ;
    int physical;
    int logic;
public:
    CitizenArr();
    ~CitizenArr();
    bool addCitizen(Citizen& add);

    int size() const { return logic; }
    int length() const { return physical; }
    Citizen& getCitizenByInx(int idx) { return *citizens[idx]; }//return citizen by index
    const Citizen* getCitizen(long id) const;//search specific id and return referance 
    bool SearchById(const long& id) const;
    Citizen* PtrToCitizen(long& id);
    void printList() const;
	const CitizenArr & operator=(const CitizenArr& other);
	 void save(ofstream& outfile) const;
};




