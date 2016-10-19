import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D




Years = 100
numTimesteps = 100000
Sun = 1 ##Always

## Entire solar system simulation (with pluto) planets are numbered by their position from the sun
## Filename for initial data "initial_data.txt "
## Includes start positions in AU and velocities in AU/day





##Earth-Sun circular orbit plus escape velocity
## Filename for initial data "initial_data_circular_earth.txt "
Earth_circular = 2
Earth_escape1 = 3
Earth_escape2 = 4
Earth_escape3 = 5
Earth_escape4 = 6
Earth_escape5 = 7
Earth_escape6 = 8
Earth_escape7 = 9
Earth_escape8 = 10



## Mercury-Sun with GR correction factor
## Filename for initial data "initial_data_mercury_perihelion.txt "
Mercury_GR = 2




##Runs the program which saves the positions of the planets to file
## and then open the files and makes plots
os.system("./Project3 "+ "initial_data_mercury_perihelion.txt " +str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Mercury_GR))
file = open("positions.txt",'r')
file.readline()
## Need to add array's for each planet
Planet1x = []
Planet1y = []
Planet1z = []
Planet2x = []
Planet2y = []
Planet2z = []

file.readline()
count = 0




## Works for mercury perihelion and circular/escape velocity but not for solar system simulation
for line in file:
    count+=1
    if count % 2 == 0: 
        values = line.split()
        Planet2x.append(float(values[0]))
        Planet2y.append(float(values[1]))
        Planet2z.append(float(values[2]))
    else:
        values = line.split()
        Planet1x.append(float(values[0]))
        Planet1y.append(float(values[1]))
        Planet1z.append(float(values[2]))

        
fig = plt.figure()
ax = fig.gca(projection='3d')
Planet1, = ax.plot(Planet1x, Planet1y, Planet1z, label=("Sun"))
Planet2, = ax.plot(Planet2x, Planet2y, Planet2z, label=("Mercury"))
plt.title('Planets Orbits for '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax.set_ylabel('Y coordinate [AU]')
ax.set_label('X coordinate [AU]')
ax.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
plt.savefig("Project_3"+"Mercur_GR"+".png")
file.close()


os.system("rm "+"positions.txt")


