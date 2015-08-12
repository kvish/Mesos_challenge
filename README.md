# Mesos_challenge
elevator simulation for mesosphere challenge


I began this simulation by trying a regular elevator algorithm in which elevators have directions and an elevator would respond to a request in the same direction, however I tried a different approach after some testing.

My approach is shortest seek time first, in which a request is given to the closest elevator and an elevator picks the closest floor to it to travel too. This approach is faster than a FCFS, because it tries to minimize "seek". However this approach isnt necesarily fair and can lead to starvation. I initially had all elevators start at floor 0, however to try and fix some of the fairness I started the elevators at equal intervals in the number of floors. 

