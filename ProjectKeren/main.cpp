


#include"Election.h"
#pragma warning(disable : 4996)

const int EXIT = 10;
const int MAXSIZE_NAME = 20;

void electionMenu(Election elec) {

    int input = 0;

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

    while (input != EXIT) {
	   cout << "please choose an action (10 to exit): " << endl;
	   cin >> input;

	   if (input == 1) // add province
	   {
		  char CountyName[MAXSIZE_NAME];
		  int numOfRep;
		  cout  << " Enter the name of the county :" << endl;
		  cin >> CountyName;		 
		  cout << "Enter number of reps: " << endl;
		  cin >> numOfRep;

		  County c(CountyName , numOfRep );
		  elec.AddCounty(c);
		  
	   }

	   if (input == 2) // add citizen 
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
		  cout << "County serial number: "<< endl;
		  cin >> countySerial;

		  Citizen addCitizen( CitizenName, id, birthyear);
		  if (elec.AddCitizen(addCitizen, countySerial) == false)
			 cout << "a wrong citizen input " << endl;
	   }

	   if (input == 3) // add party
	   {
		  char partyName[MAXSIZE_NAME];
		  long LeadCandId;

		  cout << "Party name: " << endl;
		  cin >> partyName;
		  cout << "President candidate ID: " << endl;
		  cin >> LeadCandId;
		  Citizen* ptrToLeadCand = elec.PtrCitizenById(LeadCandId);
		  if (ptrToLeadCand == nullptr)
			 cout << "the lead cand id is not exist" << endl;
		  else
		  {
			 Party addParty(partyName, *ptrToLeadCand);
			 elec.addParty(addParty);
		  }
	   
	   }
	   if (input == 4) // add candidate
	   {		  
		  int  partySerial, CountySerial;
		  long id;
		  cout << "Candidate ID: " << endl ;
		  cin >> id;
		  cout << "Party Serial: " << endl ;
		  cin >> partySerial;
		  cout << "County Serial: " << endl ;
		  cin >> CountySerial;

		  if(! elec.UpdateRepArray(id,CountySerial,partySerial))
			 cout << "you entered invalid details" << endl;
	   }

	   if (input == 5) // show all Counties	 - 
		  elec.printCounties();

	   if (input == 6) // show citizen
		  elec.printCitizens();

	   if (input == 7) // show parties  // error candidates list
		  elec.printParties();
	   if (input == 8)
	   {
		  int  partySerial;
		  long id;
		  cout << "Voter ID : " << endl;
		  cin >> id;
		  cout << "Party Serial: " << endl;
		  cin >> partySerial;
		  elec.addVote(id, partySerial);
	   }
	   if (input == 9)
		  elec.PrintElection();
	   if (input == 10)
		  exit(0);
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
int main() {
    
    int d, m, y;
    getdate(d, m, y);
    Election elec (d, m, y);
    cout << "----------------------------------------------" << endl;
    electionMenu(elec);

    cout << " ----- the Elections are OVER  :) ----- "  << endl;
}
