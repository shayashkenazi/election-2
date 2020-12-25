#pragma once
#include"PtrCitizenArray.h"
#pragma warning(disable : 4996)

class Party
{
    private:
        char* PartyName= nullptr;
        static int partySerialNumber;
        int PartyId;
        int RepArrayPhysical = 0;
        int SumOfElectors=0;//update only if party won all the electors 
        int numOfCounties = 0;
        //int* ElectorsByCounty=nullptr;//array kol ta ze kamot atzbaot lefi metigim shel mahoz
        
        Citizen* LeadCand=nullptr;//candidate id of the lead candidate        
        PtrCitizenArray* repArray=nullptr;//reshimat netzigim// id of reppres    
    public:
	   //wrtite set,add and return specific rep at array 
        Party();
	   Party(char* _PartyName, Citizen& _LeadCand);
        ~Party();
        const char* getPartyName()const { return PartyName; }
        int getPartyId()const { return PartyId; }
        Citizen& getLeadCand()const { return *(LeadCand); }
        int getSumOfElectors()const { return SumOfElectors; }

        bool setPartyName(const char* _PartyName);
        bool setPartyId(const int& _PartyId) { PartyId = _PartyId; return true; }
        bool setLeadCand( Citizen& _LeadCand) { LeadCand = &_LeadCand; return true; }
        friend std::ostream& operator<<(std::ostream& os, const Party& party);
        bool addRep (Citizen* citizen,int& countyId) ;
        void printRep() const;
        void pritnRepByIdx(int CountOfRep,int indexOfCounty);//print num of rep at specific party
	   const Party& operator=(const Party& other);
        bool SetElectors(int& electors) { SumOfElectors += electors; return true; }
        bool SetInitToZero() { SumOfElectors = -1; return true; }
        // bool SetElectors(int& electors, int& countyIdx) { ElectorsByCounty[countyIdx] += electors; SumOfElectors += electors; return true; }
        
      //  void initElectorsArray(int& numOfCounties);//set the electors array with 0
            
};

