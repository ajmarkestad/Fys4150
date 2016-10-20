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


## Simulation of our Solar System with all the planets including pluto (LONG LIVE!!) for 300 years


os.system("./Project3"+ " " + str(verlet) + " " + "initial_data.txt"+ " " + "positions_solar_system"+ " " + str(3*Years) + " " + str(numTimesteps) + " " + str(0))

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

    
fig1 = plt.figure(1)
ax1 = fig1.gca(projection='3d')
Planet1, = ax1.plot(Planet1x, Planet1y, Planet1z, label=("Sun"))
Planet2, = ax1.plot(Planet2x, Planet2y, Planet2z, label=("Mercury"))
Planet3, = ax1.plot(Planet3x, Planet3y, Planet3z, label=("Venus"))
Planet4, = ax1.plot(Planet4x, Planet4y, Planet4z, label=("Earth"))
Planet5, = ax1.plot(Planet5x, Planet5y, Planet5z, label=("Mars"))
Planet6, = ax1.plot(Planet6x, Planet6y, Planet6z, label=("Jupiter"))
Planet7, = ax1.plot(Planet7x, Planet7y, Planet7z, label=("Saturn"))
Planet8, = ax1.plot(Planet8x, Planet8y, Planet8z, label=("Uranus"))
Planet9, = ax1.plot(Planet9x, Planet9y, Planet9z, label=("Neptune"))
Planet10, = ax1.plot(Planet10x, Planet10y, Planet10z, label=("Pluto"))

plt.title('Solar system simulation using Verlets method over '+str(int(3*Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax1.set_ylabel('Y coordinate [AU]')
ax1.set_xlabel('X coordinate [AU]')
ax1.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2,Planet3,Planet4,Planet5,Planet6,Planet7,Planet8,Planet9,Planet10])
#plt.savefig("Project_3"+"_Solar_System_verlet_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.show()
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




##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of Mercury's Perihelion precession around the sun using Verlets method with GR corrections to the Newtonian Force over 100 years.





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
  
fig2 = plt.figure(2)
ax2 = fig2.gca(projection='3d')
Planet1, = ax2.plot(Planet_sunx, Planet_suny, Planet_sunz, label=("Sun"))
Planet2, = ax2.plot(Planet_mercuryx, Planet_mercuryy, Planet_mercuryz, label=("Mercury"))
plt.title('Sun Mercury system with GR corection factor over '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax2.set_ylabel('Y coordinate [AU]')
ax2.set_xlabel('X coordinate [AU]')
ax2.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
#plt.savefig("Project_3"+"_Mercur_GR_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.show()
file1.close()
file2.close()

os.system("rm "+"positions_perihelion0")
os.system("rm "+"positions_perihelion1")


##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system for perfect circular orbit initial conditions using Verlets method.


os.system("./Project3 "+str(verlet) + " " + "initial_data_circular_earth.txt " + "positions_circular_earth " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Earth_circular))

## Need to add array's for each planet
Planet_sun_circ_verlet_x = []
Planet_sun_circ_verlet_y = []
Planet_sun_circ_verlet_z = []
Planet_earth_circ_verlet_x = []
Planet_earth_circ_verlet_y = []
Planet_earth_circ_verlet_z = []


file1 = open("positions_circular_earth0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sun_circ_verlet_x.append(float(values[0]))
    Planet_sun_circ_verlet_y.append(float(values[1]))
    Planet_sun_circ_verlet_z.append(float(values[2]))


file2 = open("positions_circular_earth1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet_earth_circ_verlet_x.append(float(values[0]))
    Planet_earth_circ_verlet_y.append(float(values[1]))
    Planet_earth_circ_verlet_z.append(float(values[2]))
  
fig3 = plt.figure(3)
ax3 = fig3.gca(projection='3d')
Planet1, = ax3.plot(Planet_sun_circ_verlet_x, Planet_sun_circ_verlet_y, Planet_sun_circ_verlet_z, label=("Sun"))
Planet2, = ax3.plot(Planet_earth_circ_verlet_x, Planet_earth_circ_verlet_y, Planet_earth_circ_verlet_z, label=("Earth"))
plt.title('Earth sun circular orbit using Verlets method over '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax3.set_ylabel('Y coordinate [AU]')
ax3.set_xlabel('X coordinate [AU]')
ax3.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
#plt.savefig("Project_3"+"_Circ_Earth_verlet_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.show()
file1.close()
file2.close()

os.system("rm "+"positions_circular_earth0")
os.system("rm "+"positions_circular_earth1")



##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system for perfect circular orbit initial conditions using Eulers method.




os.system("./Project3 "+str(euler) + " " + "initial_data_circular_earth.txt " + "positions_circular_earth " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Earth_circular))

## Need to add array's for each planet
Planet_sun_circ_euler_x = []
Planet_sun_circ_euler_y = []
Planet_sun_circ_euler_z = []
Planet_earth_circ_euler_x = []
Planet_earth_circ_euler_y = []
Planet_earth_circ_euler_z = []


file1 = open("positions_circular_earth0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sun_circ_euler_x.append(float(values[0]))
    Planet_sun_circ_euler_y.append(float(values[1]))
    Planet_sun_circ_euler_z.append(float(values[2]))


file2 = open("positions_circular_earth1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet_earth_circ_euler_x.append(float(values[0]))
    Planet_earth_circ_euler_y.append(float(values[1]))
    Planet_earth_circ_euler_z.append(float(values[2]))
  
fig4 = plt.figure(4)
ax4 = fig4.gca(projection='3d')
Planet1, = ax4.plot(Planet_sun_circ_euler_x, Planet_sun_circ_euler_y, Planet_sun_circ_euler_z, label=("Sun"))
Planet2, = ax4.plot(Planet_earth_circ_euler_x, Planet_earth_circ_euler_y, Planet_earth_circ_euler_z, label=("Earth"))
plt.title('Earth sun circular orbit using Eulers method over '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
ax4.set_ylabel('Y coordinate [AU]')
ax4.set_xlabel('X coordinate [AU]')
ax4.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
#plt.savefig("Project_3"+"_Circ_Earth_euler_"+str(Years)+"_"+str(numTimesteps)+".png")
plt.show()
file1.close()
file2.close()

os.system("rm "+"positions_circular_earth0")
os.system("rm "+"positions_circular_earth1")

##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system with initial velocity of earth of 0.0240 AU/day in y direction starting at 1 AU in x direction. Sun at rest in origo.



os.system("./Project3 "+str(verlet) + " " + "initial_data_circular_earth.txt " + "positions_circular_earth " + str(Years*10)+" "+str(numTimesteps*10)+" "+str(Sun)+" "+str(Earth_escape1))

## Need to add array's for each planet
Planet_sun_escape1_verlet_x = []
Planet_sun_escape1_verlet_y = []
Planet_sun_escape1_verlet_z = []
Planet_earth_escape1_verlet_x = []
Planet_earth_escape1_verlet_y = []
Planet_earth_escape1_verlet_z = []


file1 = open("positions_circular_earth0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sun_escape1_verlet_x.append(float(values[0]))
    Planet_sun_escape1_verlet_y.append(float(values[1]))
    Planet_sun_escape1_verlet_z.append(float(values[2]))


file2 = open("positions_circular_earth1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet_earth_escape1_verlet_x.append(float(values[0]))
    Planet_earth_escape1_verlet_y.append(float(values[1]))
    Planet_earth_escape1_verlet_z.append(float(values[2]))
  
fig5 = plt.figure(5)
ax5 = fig5.gca(projection='3d')
Planet1, = ax5.plot(Planet_sun_escape1_verlet_x, Planet_sun_escape1_verlet_y, Planet_sun_escape1_verlet_z, label=("Sun"))
Planet2, = ax5.plot(Planet_earth_escape1_verlet_x, Planet_earth_escape1_verlet_y, Planet_earth_escape1_verlet_z, label=("Earth"))
plt.title('Earth sun Escape with 0.0240 AU/day initial velocity over '+str(int(Years*10))+' Years with '+str(int(numTimesteps*10))+' timesteps')
ax5.set_ylabel('Y coordinate [AU]')
ax5.set_xlabel('X coordinate [AU]')
ax5.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
#plt.savefig("Project_3"+"_Escape6_Earth_verlet_"+str(Years*10)+"_"+str(numTimesteps*10)+".png")
plt.show()
file1.close()
file2.close()

os.system("rm "+"positions_circular_earth0")
os.system("rm "+"positions_circular_earth1")





##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system with initial velocity of earth of 0.0242 AU/day in y direction starting at 1 AU in x direction. Sun at rest in origo.


os.system("./Project3 "+str(verlet) + " " + "initial_data_circular_earth.txt " + "positions_circular_earth " + str(Years*10)+" "+str(numTimesteps*10)+" "+str(Sun)+" "+str(Earth_escape2))

## Need to add array's for each planet
Planet_sun_escape2_verlet_x = []
Planet_sun_escape2_verlet_y = []
Planet_sun_escape2_verlet_z = []
Planet_earth_escape2_verlet_x = []
Planet_earth_escape2_verlet_y = []
Planet_earth_escape2_verlet_z = []


file1 = open("positions_circular_earth0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sun_escape2_verlet_x.append(float(values[0]))
    Planet_sun_escape2_verlet_y.append(float(values[1]))
    Planet_sun_escape2_verlet_z.append(float(values[2]))


file2 = open("positions_circular_earth1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet_earth_escape2_verlet_x.append(float(values[0]))
    Planet_earth_escape2_verlet_y.append(float(values[1]))
    Planet_earth_escape2_verlet_z.append(float(values[2]))
  
fig6 = plt.figure(6)
ax6 = fig6.gca(projection='3d')
Planet1, = ax6.plot(Planet_sun_escape2_verlet_x, Planet_sun_escape2_verlet_y, Planet_sun_escape2_verlet_z, label=("Sun"))
Planet2, = ax6.plot(Planet_earth_escape2_verlet_x, Planet_earth_escape2_verlet_y, Planet_earth_escape2_verlet_z, label=("Earth"))
plt.title('Earth sun Escape with 0.0242 AU/day initial velocity over '+str(int(Years*10))+' Years with '+str(int(numTimesteps*10))+' timesteps')
ax6.set_ylabel('Y coordinate [AU]')
ax6.set_xlabel('X coordinate [AU]')
ax6.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
#plt.savefig("Project_3"+"_Escape5_Earth_verlet_"+str(Years*10)+"_"+str(numTimesteps*10)+".png")
plt.show()
file1.close()
file2.close()

os.system("rm "+"positions_circular_earth0")
os.system("rm "+"positions_circular_earth1")



##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system with initial velocity of earth of 0.0244 AU/day in y direction starting at 1 AU in x direction. Sun at rest in origo.


os.system("./Project3 "+str(verlet) + " " + "initial_data_circular_earth.txt " + "positions_circular_earth " + str(Years*10)+" "+str(numTimesteps*10)+" "+str(Sun)+" "+str(Earth_escape3))

## Need to add array's for each planet
Planet_sun_escape3_verlet_x = []
Planet_sun_escape3_verlet_y = []
Planet_sun_escape3_verlet_z = []
Planet_earth_escape3_verlet_x = []
Planet_earth_escape3_verlet_y = []
Planet_earth_escape3_verlet_z = []


file1 = open("positions_circular_earth0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sun_escape3_verlet_x.append(float(values[0]))
    Planet_sun_escape3_verlet_y.append(float(values[1]))
    Planet_sun_escape3_verlet_z.append(float(values[2]))


file2 = open("positions_circular_earth1",'r')
file2.readline()

for line in file2:
    values = line.split()
    Planet_earth_escape3_verlet_x.append(float(values[0]))
    Planet_earth_escape3_verlet_y.append(float(values[1]))
    Planet_earth_escape3_verlet_z.append(float(values[2]))
  
fig7 = plt.figure(7)
ax7 = fig7.gca(projection='3d')
Planet1, = ax7.plot(Planet_sun_escape3_verlet_x, Planet_sun_escape3_verlet_y, Planet_sun_escape3_verlet_z, label=("Sun"))
Planet2, = ax7.plot(Planet_earth_escape3_verlet_x, Planet_earth_escape3_verlet_y, Planet_earth_escape3_verlet_z, label=("Earth"))
plt.title('Earth sun Escape with 0.0244 AU/day initial velocity over '+str(int(Years*10))+' Years with '+str(int(numTimesteps*10))+' timesteps')
ax7.set_ylabel('Y coordinate [AU]')
ax7.set_xlabel('X coordinate [AU]')
ax7.set_zlabel('Z coordinate [AU]')
plt.legend(handles = [Planet1,Planet2])
#plt.savefig("Project_3"+"_Escape5_Earth_verlet_"+str(Years*10)+"_"+str(numTimesteps*10)+".png")
plt.show()
file1.close()
file2.close()

os.system("rm "+"positions_circular_earth0")
os.system("rm "+"positions_circular_earth1")


##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system with circular orbit. Plots only the energies involved. Sun starts at rest in origo.


os.system("./Project3 "+str(energy_euler) + " " + "initial_data_circular_earth.txt " + "energies " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Earth_circular))

## Need to add array's for each planet
Total_Energy_E = []
Potential_energy_E = []
Kinetic_energy_E = []


file1 = open("energies",'r')
file1.readline()

for line in file1:
    values = line.split()
    Total_Energy_E.append(float(values[0]))
    Kinetic_energy_E.append(float(values[1]))
    Potential_energy_E.append(float(values[2]))


x = np.linspace(0,Years,numTimesteps-2)
    
plt.figure(8)
Tot, = plt.plot(x, Total_Energy_E, label=("Total Energy"))
Pot, = plt.plot(x, Potential_energy_E, label=("Potential Energy"))
Kin, = plt.plot(x, Kinetic_energy_E, label=("Kinetic Energy"))
plt.title('Energies of the Earth-Sun system with circular orbit using Eulers method over '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
plt.xlabel('Time [Years]')
plt.ylabel('Energy')
plt.legend(handles = [Tot,Kin,Pot])
#plt.savefig("Project_3"+"_Escape5_Earth_verlet_"+str(Years*10)+"_"+str(numTimesteps*10)+".png")
plt.show()
file1.close()

os.system("rm "+"energies")


##################################################################################################################################################################################################
##################################################################################################################################################################################################


## Simulation of earth sun system with circular orbit. Plots only the energies involved. Sun starts at rest in origo.


os.system("./Project3 "+str(energy_verlet) + " " + "initial_data_circular_earth.txt " + "energies " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Earth_circular))

## Need to add array's for each planet
Total_Energy_V = []
Potential_energy_V = []
Kinetic_energy_V = []


file1 = open("energies",'r')
file1.readline()

for line in file1:
    values = line.split()
    Total_Energy_V.append(float(values[0]))
    Kinetic_energy_V.append(float(values[1]))
    Potential_energy_V.append(float(values[2]))



    
plt.figure(9)
Tot, = plt.plot(x, Total_Energy_V, label=("Total Energy"))
Pot, = plt.plot(x, Potential_energy_V, label=("Potential Energy"))
Kin, = plt.plot(x, Kinetic_energy_V, label=("Kinetic Energy"))
plt.title('Energies of the Earth-Sun system with circular orbit using Verlets method over '+str(int(Years))+' Years with '+str(int(numTimesteps))+' timesteps')
plt.xlabel('Time [Years]')
plt.ylabel('Energy')
plt.legend(handles = [Tot,Kin,Pot])
#plt.savefig("Project_3"+"_Escape5_Earth_verlet_"+str(Years*10)+"_"+str(numTimesteps*10)+".png")
plt.show()
file1.close()

os.system("rm "+"energies")


