#include <iostream>
#include <string>
#include "Simulation.h"

using namespace std;
void displayHelp(); 


int main() {
	cout << "                                             _             " << endl;
	cout << "                                            (  )           " << endl;
	cout << "             _ .                         ( `  ) . )        " << endl;
	cout << "           (  _ )_  Mesosphere         (_, _(  ,_)_)      " << endl;
	cout << "         (_  _(_ ,)                                       " << endl;
	cout << endl << endl;


	cout << "welcome to the elevator simulation CLI" << endl;
	
	//get number of elevators
	cout << "enter the number of elevators: ";
	int elevs;
	cin >> elevs;

	cout << "enter the number of floors: ";
	int floors;
	cin >> floors;

	//init simulation with number of elevators
	Simulation simulator(elevs, floors);

	displayHelp();
	
	while (1)
	{
		string cmd;
		cout << "input a command: ";
		getline(cin, cmd);

		if (cmd == "status")
		{
			simulator.status();
		}
		else if (cmd == "ind_status")
		{
			int id;
			cin >> id;

			while (id > elevs) 
			{
				cout << "there arent that many elevators! " << endl;
				cout << "please re-enter the elevator you want to query: " << endl;
				cin >> id;
			}

			simulator.individual_status(id);
		}
		else if (cmd == "request")
		{
			int pickup = 0;
			int dropoff = 0;
			cin >> pickup;
			cin >> dropoff;

			simulator.request(pickup, dropoff);
		}
		else if (cmd == "run")
		{
			string filename;
			getline(cin, filename);
			simulator.run(filename);
		}
		else if (cmd == "help")
		{
			displayHelp();
		}
		else if (cmd == "quit")
		{
			cout << "exiting simulation" << endl;
			return 0;
		}

	}

	return 0;
}


void displayHelp() {
	cout << endl;
	cout << "available commands are status (gets status of all elevators), ind_status <INT> (gets status of an individual elevator), request <pickup_floor> <dropoff_floor> (makes a pickup reqeust), run <filename> (runs simulation from filename, details in README), or QUIT to exit simulation" << endl;
	cout << "type help to see this message again or quit to exit" << endl;
}
