#pragma once
#include"PtrCitizenArray.h"
#pragma warning(disable : 4996)

class Party
{
    private:
        string PartyName;
        static int partySerialNumber;
        int PartyId;
        int SumOfElectors=0;//update only if party won all the electors 
        Citizen* LeadCand=nullptr;//candidate id of the lead candidate        
        DynamicArray <PtrCitizenArray> repArray;// array of represenatives. every cell represent County.  
    public:
        Party();
	    Party(const string _PartyName, Citizen* _LeadCand);
        Party(ifstream& inFile, Citizen& _LeadCand);//file ctor
        ~Party();
        Party(const Party& other);//copy ctor.
        //setters//

        bool setPartyName(const string _PartyName);
        bool setPartyId(const int& _PartyId) { PartyId = _PartyId; return true; }
        bool setLeadCand(Citizen& _LeadCand) { LeadCand = &_LeadCand; return true; }
        bool addRep(Citizen* citizen, int& countyId);// set citizen as a rep of the party to specific county.
        bool SetElectors(int& electors) { SumOfElectors += electors; return true; }//update electors given by counties.
        bool SetInitToZero() { SumOfElectors = -1; return true; }
        static void resetCounter() { partySerialNumber = 0; }
        //getters//
        const string getPartyName()const { return PartyName; }
        int getPartyId()const { return PartyId; }
        Citizen& getLeadCand()const { return *(LeadCand); }
        int getSumOfElectors()const { return SumOfElectors; }
        void printRep() const;
        void pritnRepByIdx(int CountOfRep,int CountyId);//print num of rep at specific party
	  
        //operators//
        friend std::ostream& operator<<(std::ostream& os, const Party& party);//cout op.
        const Party& operator=(const Party& other);// operator =
        void save(ofstream& outFile) const;
            
};

