#include <iostream>
#include "Simulation.h";
#include <string>

using namespace std;
void displayHelp(); 


int main() {
	cout << "                                             _             " << endl;
	cout << "                                            (  )           " << endl;
	cout << "             _ .                         ( `  ) . )        " << endl;
	cout << "           (  _ )_  Mesosphere         (_, _(  ,_)_)      " << endl;
	cout << "         (_  _(_ ,)                                       " << endl;
	cout << endl << endl;


	cout << "welcome to the elevator simulation CLI";
	
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

		if (cmd == "STATUS")
		{
			simulator.status();
		}
		else if (cmd == "IND_STATUS")
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
		else if (cmd == "REQUEST")
		{
			int pickup = 0;
			int dropoff = 0;
			cin >> pickup;
			cin >> dropoff;

			simulator.request(pickup, dropoff);
		}
		else if (cmd == "RUN")
		{
			string filename;
			getline(cin, filename);
			simulator.run(filename);
		}
		else if (cmd == "HELP")
		{
			displayHelp();
		}
		else if (cmd == "QUIT")
		{
			cout << "exiting simulation" << endl;
			return 0;
		}

	}

	return 0;
}


void displayHelp() {
	cout << endl;
	cout << "available commands are STATUS (gets status of all elevators), IND_STATUS <INT> (gets status of an individual elevator), REQUEST <pickup> <dropoff> (makes a pickup reqeust), RUN <filename> (runs simulation from filename, details in README), or QUIT to exit simulation" << endl;
	cout << "type HELP to see this message again" << endl;
}