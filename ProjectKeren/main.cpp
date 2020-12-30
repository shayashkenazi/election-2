
#include"SimpleElection.h"
#include"UnifiedCounty.h"
#include"DividedCounty.h"
#include"RegularElection.h"

#pragma warning(disable : 4996)

const int EXIT = 10;
const int MAXSIZE_NAME = 20;



void electionMenu1(Election *elec,int InitElec) {

    int input = 0;
    system("cls");
    cout << "please choose one of the actions: (party and county indexes start from 1" << endl;
    cout << "1-to add a county" << endl;
    cout << "2- to add a citizen" << endl;
    cout << "3- to add a party" << endl;
    cout << "4- set existing citizen as a candidate" << endl;
    cout << "5- to show counties" << endl;
    cout << "6- to show citizens" << endl;
    cout << "7- to show parties" << endl;
    cout << "8- to vote" << endl;
    cout << "9- to show results" << endl;
    cout << "10. exit" << endl;
    cout << "11. save election" << endl;
    cout << "12. load election" << endl;

    while (input != EXIT) {
	   cout << "please choose an action (10 to exit): " << endl;
	   cin >> input;

	   if (input == AddCounty) // add province
	   {
		  if (typeid(*elec) == typeid(RegularElection)) {
			 char CountyName[MAXSIZE_NAME];
			 int numOfRep, CountyType;
			 cout << " Enter the name of the county :" << endl;
			 cin >> CountyName;
			 cout << "Enter number of reps: " << endl;
			 cin >> numOfRep;
			 cout << "Enter 1 for unified County or 2 for Divided County: " << endl;
			 cin >> CountyType;
			 if (CountyType == 1) {
				UnifiedCounty county(CountyName, numOfRep);
				elec->AddCounty(county);
			 }
			 else if (CountyType == 2) {
				DividedCounty county(CountyName, numOfRep);
				elec->AddCounty(county);
			 }
			 else //user not entered 1 or 2.
				cout << "wrong input" << endl;
		  }
		  else
			 cout << "This is simple election, hence its not possible to add County."<<endl;
	   }

	   if (input == AddCitizen) // add citizen 
	   {
		  char CitizenName[MAXSIZE_NAME];
		  int  birthyear, countySerial;
		  long id;
		  cout << "Citizen name: " << endl;
		  cin >> CitizenName;
		  cout << "Citizen id: " << endl;
		  cin >> id;
		  cout << "Citizen year of birth : "<< endl;
		  cin >> birthyear;
		  if (typeid(*elec) == typeid(RegularElection)) {//if its a simple eletion ne need of choosing county id.
			 cout << "County serial number: " << endl;
			 cin >> countySerial;
		  }

		  Citizen addCitizen( CitizenName, id, birthyear);
		  if (elec->AddCitizen(addCitizen, countySerial) == false)
			 cout << "a wrong citizen input " << endl;
	   }

	   if (input == AddParty) // add party
	   {
		  char partyName[MAXSIZE_NAME];
		  long LeadCandId;

		  cout << "Party name: " << endl;
		  cin >> partyName;
		  cout << "President candidate ID: " << endl;
		  cin >> LeadCandId;
		  Citizen* ptrToLeadCand = elec->PtrCitizenById(LeadCandId);
		  if (ptrToLeadCand == nullptr)
			 cout << "the lead cand id is not exist" << endl;
		  else
		  {
			 Party addParty(partyName, *ptrToLeadCand);
			 elec->addParty(addParty);
		  }
	   
	   }
	   if (input == SetRepresentative) // add candidate
	   {		  
		  int  partySerial, CountySerial;
		  long id;
		  cout << "Candidate ID: " << endl ;
		  cin >> id;
		  cout << "Party Serial: " << endl ;
		  cin >> partySerial;
		  if (typeid(*elec) == typeid(RegularElection)) {
			 cout << "County Serial: " << endl;
			 cin >> CountySerial;
		  }
		  else //simple election only one county.
			 CountySerial = 1;

		  if(! elec->UpdateRepArray(id,CountySerial,partySerial))
			 cout << "you entered invalid details" << endl;
	   }

	   if (input == DisplayCounties) { // show all Counties	 - 
		  if (typeid(*elec) == typeid(RegularElection))
			 elec->printCounties();
		  else
			 cout << "this is simple election, hence no counties" << endl;
	   }

	   if (input == DisplayCitizens) // show citizen
		  elec->printCitizens();

	   if (input == DisplayParties) // show parties  // error candidates list
		  elec->printParties();
	   if (input == SetVote)
	   {
		  int  partySerial;
		  long id;
		  cout << "Voter ID : " << endl;
		  cin >> id;
		  cout << "Party Serial: " << endl;
		  cin >> partySerial;
		  elec->addVote(id, partySerial);
	   }
	   if (input == DisplayElectionResult)
		  elec->PrintElection();
	   if (input == Exit)
	   {
		  delete elec;
		  exit(0);
	   }
    }
}
void getdate(int& d, int& m, int& y)
{
    int stop=0;
    cout << "welcome to Elections system! please enter the Elections Date: " << endl;

    while (!stop) {
	   cout << "select date" << endl;
	   cout << "choose year: ", cin >> y;
	   cout << "choose month: ", cin >> m;
	   if (m < 1 || m > 12) {
		  cout << "invalid month. please select month between 1-12" << endl << endl;
		  continue;
	   }
	   cout << "choose day: ", cin >> d;
	   if (d < 1 || 31 < d) {
		  cout << "invalid day. please select day between 1-31" << endl << endl;
		  continue;
	   }
	   stop = 1;
    }
}
void SelectElection(int& d, int& m, int& y)
{
    Election* elec =nullptr;
    cout << "choose election type: " << endl;
    cout << "1. regular election" << endl;
    cout << "2. simple election" << endl;
    int InitElec;
    while (true) {
	   cin >> InitElec;
	   if (InitElec < 1 || InitElec >2) {
		  cout << "you may enter 1 or 2 only. please try again:";
			 cin >> InitElec;
	   }
	   else
		  break;
    }
    if (InitElec == regularElection) {
	   elec = new RegularElection(d,m,y);
    }
    

    else if (InitElec == simpleElection) {
	   int reps;
	   cout << "Enter number of representatives: ", cin >> reps, cout << endl;
	 elec = new SimpleElection(d,m,y,reps);
    }
    electionMenu1(elec, InitElec);

}
void InitElectionMenu()
{
    int day, month, year;
    int InitElection;
    cout << "Choose from the following:" << endl;
    cout << "1. create new election round" << endl;
    cout << "2. load an existing eleciton file" << endl;
    cout << "3. exit" << endl;
    cin >> InitElection;
    switch (InitElection) {
    case CreateNewElection:
	   getdate(day, month, year);
	   SelectElection(day, month, year);

	   break;
    case LoadFromFile:
	   // initialMenu2();
	   break;
    default:
	   //  run = false;
	   break;
    }
}
int main() {
    
   
    cout << "----------------------------------------------" << endl;
    InitElectionMenu();


    
    cout << " ----- the Elections are OVER  :) ----- "  << endl;
}


