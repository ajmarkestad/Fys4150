import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D




Years = 100
numTimesteps = 10000000000
Sun = 1 ##Always

## Entire solar system simulation (with pluto) planets are numbered by their position from the sun
## Filename for initial data "initial_data.txt "
## Includes start positions in AU and velocities in AU/day

## Numerical method that you would like to use
euler = 0
verlet = 1
verlet_GR = 2
energy_euler = 3
energy_verlet = 4



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


##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of Mercury's Perihelion precession around the sun using Verlets method with GR corrections to the Newtonian Force over 100 years.





os.system("./Project3 "+str(verlet_GR) + " " + "initial_data_mercury_perihelion.txt " + "angles_perihelion " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Mercury_GR))

## Need to add array's for each planet
Angles = []

file1 = open("angles_perihelion",'r')
file1.readline()

for line in file1:
    values = line.split()
    Angles.append((180/np.pi)*(3600)*float(values[0]))
  

time = np.linspace(0, Years, len(Angles))

print(Angles[-1])

fig2 = plt.figure(2)
Planet1, = plt.plot(time, Angles)
plt.title('Perihelion angles for Mercury orit precession with GR corection factor over '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
plt.xlabel('Time [Years]')
plt.ylabel('Perihelion Angle [arc seconds]')
#plt.savefig("Project_3"+"_Mercur_GR_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.show()
file1.close()

os.system("rm "+"angles_perihelion")

