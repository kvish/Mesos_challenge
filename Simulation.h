#ifndef SIMULATION
#define SIMULATION

#include<queue>
#include<stack>
#include<string>

using namespace std;

//operations available to simulation user
//implementations in Simulation.cpp
class Simulation {

private:
	//Request Object
	struct Request {
		int pickupFloor;
		int EndingFloor;
		bool pickedUp;
	};

	enum Direction{UP, DOWN, NONE};

	//definition of an elevator object
	struct Elevator {
		vector<Request> requests;
		int currFloor;
		Request currRequest;
		bool active;
		int curr_idx;
	};

	int numElevators;
	int numFloors; 
	vector<Elevator> elevators;

	//at the end of each timestamp update the position of all elevators
	void update_elevators();
	void move_elevators(int elevator_id);
	bool track_active();

	//shortest seek time algorithm
	void sstf(int elevator_id);

	//keep track of request times for simulation
	int time;

public:

	//init the simulation with the number of elevators and floors
	Simulation(int elevs, int floors);
	
	//get the status of all elevators in the simulation
	void status();

	//get the status of a unique elevator
	void individual_status(int id);

	//send a request for a pickup/dropoff
	void request(int pickup, int dropoff);


	//run entire simulation given a file input
	void run(string filename);

};

#endif 