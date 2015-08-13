# Mesos_challenge
elevator simulation for mesosphere challenge

# Approach
I began this simulation by trying a regular elevator algorithm in which elevators have directions and an elevator would respond to a request in the same direction, however I tried a different approach after some testing.

My approach is shortest seek time first, in which a request is given to the closest elevator and an elevator picks the closest floor to it to travel too. This approach is faster than a FCFS, because it tries to minimize "seek". However this approach isnt necesarily fair and can lead to starvation. I initially had all elevators start at floor 0, however to try and fix some of the fairness I started the elevators at equal intervals in the number of floors, this helps to engage all elevators in the system. This solution assumes that every floor in the system has an equal chance of being selected. I wanted to test waiting times of my algorithm against a general elevator algorithm however this didnt fit in the time constraints of the challenge.

# Usage

to compile run
  g++ main.cpp Simulation.cpp -std=c++11 -o elevator
to run the executable
  ./elevator

Once you have started the executable there are 4 main operations available 
- STATUS (gets the status of all elevators in the system)
- IND_STATUS [elevator_id] (gets the status of an individual elevator)
- REQUEST [pickup] [dropoff] (schedule an elevator request)
- RUN [filename] (run a timestepped simulation)

# timestep 

this section explain more about how to run the timestep simulation.

The simulation assumes that in one time interval an elevator can move one floor only. People enter and exit the elevator instantly and once an elevator gets to a requested floor all people getting on or off do so.

an input file to the simulation follows the convention  
[timestamp] [pickupFloor] [dropoffFloor]  
for each line. Lines in the file must be in ascending timestap order. An example input file can be found in test1.txt in this repository

# Author
Karan Vishwanathan
karnvish@umich.edu
email me with any questions!
