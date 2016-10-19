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

## Numerical method that you would like to use
euler = 0
verlet = 1
verlet_GR = 2



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
os.system("./Project3"+ " " + str(verlet) + " " + "initial_data.txt"+ " " + "positions_solar_system"+ " " + str(Years) + " " + str(numTimesteps) + " " + str(0))

## Need to add array's for each planet
Planet1x = []
Planet1y = []
Planet1z = []
Planet2x = []
Planet2y = []
Planet2z = []
Planet3x = []
Planet3y = []
Planet3z = []
Planet4x = []
Planet4y = []
Planet4z = []
Planet5x = []
Planet5y = []
Planet5z = []
Planet6x = []
Planet6y = []
Planet6z = []
Planet7x = []
Planet7y = []
Planet7z = []
Planet8x = []
Planet8y = []
Planet8z = []
Planet9x = []
Planet9y = []
Planet9z = []
Planet10x = []
Planet10y = []
Planet10z = []


file1 = open("positions_solar_system0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet1x.append(float(values[0]))
    Planet1y.append(float(values[1]))
    Planet1z.append(float(values[2]))

file2 = open("positions_solar_system1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet2x.append(float(values[0]))
    Planet2y.append(float(values[1]))
    Planet2z.append(float(values[2]))

file3 = open("positions_solar_system2",'r')
file3.readline()

for line in file3:
    values = line.split()
    Planet3x.append(float(values[0]))
    Planet3y.append(float(values[1]))
    Planet3z.append(float(values[2]))

file4 = open("positions_solar_system3",'r')
file4.readline()

for line in file4:
    values = line.split()
    Planet4x.append(float(values[0]))
    Planet4y.append(float(values[1]))
    Planet4z.append(float(values[2]))

file5 = open("positions_solar_system4",'r')
file5.readline()

for line in file5:
    values = line.split()
    Planet5x.append(float(values[0]))
    Planet5y.append(float(values[1]))
    Planet5z.append(float(values[2]))

file6 = open("positions_solar_system5",'r')
file6.readline()

for line in file6:
    values = line.split()
    Planet6x.append(float(values[0]))
    Planet6y.append(float(values[1]))
    Planet6z.append(float(values[2]))

file7 = open("positions_solar_system6",'r')
file7.readline()

for line in file7:
    values = line.split()
    Planet7x.append(float(values[0]))
    Planet7y.append(float(values[1]))
    Planet7z.append(float(values[2]))

file8 = open("positions_solar_system7",'r')
file8.readline()

for line in file8:
    values = line.split()
    Planet8x.append(float(values[0]))
    Planet8y.append(float(values[1]))
    Planet8z.append(float(values[2]))

file9 = open("positions_solar_system8",'r')
file9.readline()

for line in file9:
    values = line.split()
    Planet9x.append(float(values[0]))
    Planet9y.append(float(values[1]))
    Planet9z.append(float(values[2]))

file10 = open("positions_solar_system9",'r')
file10.readline()

for line in file10:
    values = line.split()
    Planet10x.append(float(values[0]))
    Planet10y.append(float(values[1]))
    Planet10z.append(float(values[2]))

    
fig = plt.figure()
ax = fig.gca(projection='3d')
Planet1, = ax.plot(Planet1x, Planet1y, Planet1z, label=("Sun"))
Planet2, = ax.plot(Planet2x, Planet2y, Planet2z, label=("Mercury"))
Planet3, = ax.plot(Planet3x, Planet3y, Planet3z, label=("Venus"))
Planet4, = ax.plot(Planet4x, Planet4y, Planet4z, label=("Earth"))
Planet5, = ax.plot(Planet5x, Planet5y, Planet5z, label=("Mars"))
Planet6, = ax.plot(Planet6x, Planet6y, Planet6z, label=("Jupiter"))
Planet7, = ax.plot(Planet7x, Planet7y, Planet7z, label=("Saturn"))
Planet8, = ax.plot(Planet8x, Planet8y, Planet8z, label=("Uranus"))
Planet9, = ax.plot(Planet9x, Planet9y, Planet9z, label=("Neptune"))
Planet10, = ax.plot(Planet10x, Planet10y, Planet10z, label=("Pluto"))

plt.title('Planets Orbits for '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax.set_ylabel('Y coordinate [AU]')
ax.set_label('X coordinate [AU]')
ax.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2,Planet3,Planet4,Planet5,Planet6,Planet7,Planet8,Planet9,Planet10])
plt.savefig("Project_3"+"_Solar_System_verlet_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.close()
file1.close()
file2.close()
file3.close()
file4.close()
file5.close()
file6.close()
file7.close()
file8.close()
file9.close()
file10.close()


os.system("rm "+"positions_solar_system0")
os.system("rm "+"positions_solar_system1")
os.system("rm "+"positions_solar_system2")
os.system("rm "+"positions_solar_system3")
os.system("rm "+"positions_solar_system4")
os.system("rm "+"positions_solar_system5")
os.system("rm "+"positions_solar_system6")
os.system("rm "+"positions_solar_system7")
os.system("rm "+"positions_solar_system8")
os.system("rm "+"positions_solar_system9")

##Runs the program which saves the positions of the planets to file
## and then open the files and makes plots
os.system("./Project3 "+str(verlet_GR) + " " + "initial_data_mercury_perihelion.txt " + "positions_perihelion " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Mercury_GR))

## Need to add array's for each planet
Planet_sunx = []
Planet_suny = []
Planet_sunz = []
Planet_mercuryx = []
Planet_mercuryy = []
Planet_mercuryz = []


file1 = open("positions_perihelion0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sunx.append(float(values[0]))
    Planet_suny.append(float(values[1]))
    Planet_sunz.append(float(values[2]))


file2 = open("positions_perihelion1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet_mercuryx.append(float(values[0]))
    Planet_mercuryy.append(float(values[1]))
    Planet_mercuryz.append(float(values[2]))
  
fig = plt.figure()
ax = fig.gca(projection='3d')
Planet1, = ax.plot(Planet_sunx, Planet_suny, Planet_sunz, label=("Sun"))
Planet2, = ax.plot(Planet_mercuryx, Planet_mercuryy, Planet_mercuryz, label=("Mercury"))
plt.title('Planets Orbits for '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax.set_ylabel('Y coordinate [AU]')
ax.set_label('X coordinate [AU]')
ax.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
plt.savefig("Project_3"+"_Mercur_GR_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.close
file1.close()
file2.close()

os.system("rm "+"positions_perihelion0")
os.system("rm "+"positions_perihelion1")

