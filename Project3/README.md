FYS3150/FYS4150 - Project 3 
============


Code is implemented with classes vec3, ensamble, solve, and particle.

This program requires at minimum 6 commandline arguments to run:

1. Choice of method: 0 for Euler, 1 for Verlet, 2 for Verlet with GR corrections to the force, 3 for energy calculations for Euler, and 4 for energy calculatons for Verlet
2. name of file with initial positions in AU, velocities in AU/day and planet mass in solar masses.
3. Name/nameing scheme of outputfiles
4. How many years you will simulate
5. Number of timesteps
6. 0 for all planets/line in inputfile or a number 1 and up for the corresponding planet that you want in your inputfile
7. and on: the number/numbers of your other planet/planets you want to include in your simulation.

The choice of method also changes what output the program produces; 0 and 1 produces a text file for each planet involved with the positions
at each time step, 2 find the minimal radius of the orbit, i.e. the perihelion and writes to file that posistions perhileion angle in
radians, 3 and 4 produces a file with the total, kinetic and potential energy of the entire system for each timestep.
