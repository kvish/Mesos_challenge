#include <iostream>
#include<limits.h>
#include<cmath>
#include<fstream>
#include "Simulation.h";
#include <algorithm>


Simulation::Simulation(int elevs, int floors)
{
	cout << "Simulation Initted" << endl;
	//set parameters for simulation
	numElevators = elevs;
	numFloors = floors;

	int count = numFloors / numElevators;
	time = 0;

	int start = 0;
	for (int i = 0; i < elevs; i++)
	{
		Elevator elev;

		//evenly place the elevators to optimize sstf
		elev.currFloor = start;
		start += count;

		elev.currRequest.pickupFloor = -1;
		elev.currRequest.EndingFloor = -1;
		elev.currRequest.pickedUp = false; 

		elevators.push_back(elev);
	}
}


//print the status of all elevators in the system
void Simulation::status()
{
	for (int i = 0; i < elevators.size(); i++)
	{
		individual_status(i);
	}
}

void Simulation::individual_status(int id)
{
	if (elevators[id].currFloor == -1)
	{
		cout << "Elevator " << id << " has not started yet" << endl;
		return;
	}
	cout << "Elevator " << id << " is at floor " << elevators[id].currFloor << endl;
}

void Simulation::request(int pickup, int dropoff) 
{
	Request req;
	req.pickupFloor = pickup;
	req.EndingFloor = dropoff;
	req.pickedUp = false;


	if (pickup == dropoff) 
	{
		//person is on floor they need to go too
		cout << "You are at your floor already" << endl;
		return;
	}
	else
	{
		cout << "a person is requesting to go from " << pickup << " to " << dropoff << endl;
		int curr_max = INT_MAX;
		int idx = -1;
		for (int i = 0; i < elevators.size(); i++)
		{
			if (abs(elevators[i].currFloor - pickup) < curr_max)
			{
				curr_max = abs(elevators[i].currFloor - pickup);
				idx = i;
			}
		}

		//queue up request to elevator with shortest seek time
		elevators[idx].requests.push_back(req);
		elevators[idx].active = true;
		cout << "Elevator " << idx << " will respond to the request" << endl;
	}

}

void Simulation::move_elevators(int id)
{	
	//destination is the pickup floor
	if (elevators[id].currRequest.pickedUp == false)
	{
		//make sure -1 isnt considered a real request
		if (elevators[id].currRequest.pickupFloor < elevators[id].currFloor && elevators[id].currRequest.pickupFloor != -1)
		{
			elevators[id].currFloor--;
			for (int i = 0; i < elevators[id].requests.size(); i++)
			{
				if (elevators[id].requests[i].pickupFloor == elevators[id].currFloor)
				{
					elevators[id].requests[i].pickedUp = true;
					cout << "Elevator " << id << " is picking up someone at floor " << elevators[id].currRequest.pickupFloor;
				}
			}
		}
		else if (elevators[id].currRequest.pickupFloor > elevators[id].currFloor && elevators[id].currRequest.pickupFloor != -1)
		{
			elevators[id].currFloor++;
			for (int i = 0; i < elevators[id].requests.size(); i++)
			{
				if (elevators[id].requests[i].pickupFloor == elevators[id].currFloor)
				{
					elevators[id].requests[i].pickedUp = true;
					cout << "Elevator " << id << " is picking up someone at floor " << elevators[id].currRequest.pickupFloor;
				}
			}
		}
		else if (elevators[id].currRequest.pickupFloor == elevators[id].currFloor)
		{

			elevators[id].requests[0].pickedUp = true;
			cout << "Elevator " << id << " is picking up someone at floor " << elevators[id].currRequest.pickupFloor << endl;
		}
	}
	else
	{
		//destination is the dropoff floor
		if (elevators[id].currRequest.EndingFloor < elevators[id].currFloor)
		{
			elevators[id].currFloor--;

			for (int i = elevators[id].requests.size() - 1; i >= 0; i--)
			{
				if (elevators[id].requests[i].EndingFloor == elevators[id].currFloor)
				{
					cout << "elevator " << id << " is dropping off someone at floor " << elevators[id].currRequest.EndingFloor << endl;
					elevators[id].requests.erase(elevators[id].requests.erase(elevators[id].requests.begin() + i));
					elevators[id].currRequest.pickupFloor = -1;
					elevators[id].currRequest.EndingFloor = -1;

				}
			}
		}
		else if (elevators[id].currRequest.EndingFloor > elevators[id].currFloor)
		{
			elevators[id].currFloor++;
			for (int i = 0; i < elevators[id].requests.size(); i++)
			{
				if (elevators[id].requests[i].EndingFloor == elevators[id].currFloor)
				{
					cout << "elevator " << id << " is dropping off someone at floor " << elevators[id].currRequest.EndingFloor << endl;
					iter_swap(elevators[id].requests.begin() + i, elevators[id].requests.begin() + elevators[id].requests.size() - 1);
					elevators[id].requests.pop_back();
					elevators[id].currRequest.pickupFloor = -1;
					elevators[id].currRequest.EndingFloor = -1;
					elevators[id].currRequest.pickedUp = false;

				}
			}
		}
	}

}


void Simulation::sstf(int elevator_id)
{
	int curr_min = INT_MAX;
	int idx;

	for (int i = 0; i < elevators[elevator_id].requests.size(); i++)
	{
		if (elevators[elevator_id].requests[i].pickedUp == false)
		{
			if (abs(elevators[elevator_id].currFloor - elevators[elevator_id].requests[i].pickupFloor) < curr_min)
			{
				curr_min = abs(elevators[elevator_id].currFloor - elevators[elevator_id].requests[i].pickupFloor);
				idx = i;
			}
		}
		else
		{
			if (abs(elevators[elevator_id].currFloor - elevators[elevator_id].requests[i].EndingFloor) < curr_min)
			{
				curr_min = abs(elevators[elevator_id].currFloor - elevators[elevator_id].requests[i].EndingFloor);
				idx = i;
			}
		}
	}

	elevators[elevator_id].currRequest = elevators[elevator_id].requests[idx];
	elevators[elevator_id].curr_idx = idx;
}

void Simulation::update_elevators()
{
	for (int i = 0; i < elevators.size(); i++)
	{
		Elevator curr = elevators[i];
		
		//this elevator has no requests and hasnt started
		if (!curr.requests.empty())
		{
			elevators[i].active = true;
			sstf(i);
		}
		else if (curr.currRequest.pickupFloor == -1 && curr.requests.empty())
		{
			elevators[i].active = false;
		}

		move_elevators(i);
	}
}


//track when the simulation is over
bool Simulation::track_active() {
	for (int i = 0; i < elevators.size(); i++)
	{
		if (elevators[i].active == true) {
			//there is at least one elevator with pending work
			return true;
		}
	}

	return false;
}

void Simulation::run(string filename)
{
	//file formatted TIMESTAMP, PICKUP, DROPOFF

	int timestamp;
	int pickup;
	int dropoff;

	ifstream fin;
	fin.open(filename.c_str());

	bool happened = false;
	while (fin >> timestamp >> pickup >> dropoff)
	{
		//output the status of all elevators
		if (pickup > numFloors || dropoff > numFloors)
		{
			cout << "this exceeds the number of floors in the building";
			continue;
		}
		if (!happened)
		{
			cout << "timestamp " << time << endl;
			status();
			happened = true;
		}

		//if the time has not reached the timestamp 
		while (time < timestamp)
		{
			time++;
			cout << "timestamp " << time << endl;
			update_elevators();
			status();
		}

		request(pickup, dropoff);
	}

	//all requests are over but pending requests still need to be serviced

	while (track_active())
	{
		time++;
		cout << "timestamp " << time << endl;
		update_elevators();
		status();
	}
}



