import os as os
import numpy as np
from math import *
import matplotlib.pyplot as plt

Years = 100
numTimesteps = 10000000
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

from mpl_toolkits.mplot3d import Axes3D
Mercury_GR = 2

os.system("./Project3 "+str(verlet_GR) + " " + "initial_data_mercury_perihelion.txt " + "positions_perihelion " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Mercury_GR))
##########



## Need to add array's for each planet
Planet_sunx = []
Planet_suny = []
Planet_sunz = []
Planet_mercuryx = []
Planet_mercuryy = []
Planet_mercuryz = []
Planet_mercuryr = []

file1 = open("positions_perihelion0",'r')
file1.readline()

for line in file1:
    values = line.split()
    Planet_sunx.append(float(values[0]))
    Planet_suny.append(float(values[1]))
    Planet_sunz.append(float(values[2]))

file2 = open("positions_perihelion1",'r')
file2.readline()

i = 0
minumimrzero=1
minumimrone=1
listofminimums = []
start2 = 0
for line in file2:
    values = line.split()
    Planet_mercuryx.append(float(values[0]))
    Planet_mercuryy.append(float(values[1]))
    Planet_mercuryz.append(float(values[2]))
    Planet_mercuryr.append(np.sqrt(float(values[0])**2+float(values[1])**2+float(values[2])**2))
    if (Planet_mercuryr[i]<minumimrzero):
        minumimrone=minumimrzero
        minumimrzero=Planet_mercuryr[i]
        #listofminimums.append(i)
    if (i>1000) and (Planet_mercuryr[i]<(minumimrone*1.00001)):
       listofminimums.append(i)
    i+=1
    #print(i)

file1.close()
file2.close()


os.system("rm "+"positions_perihelion0")
os.system("rm "+"positions_perihelion1")

##Minumin point of perihelon
#plt.plot(listofminimums,Planet_mercuryr[listofminimums])
#plt.show()
angles = np.zeros(len(listofminimums))
for i in range(len(listofminimums)):
    angles[i]=np.arctan(np.array(Planet_mercuryy[listofminimums[i]])/np.array(Planet_mercuryx[listofminimums[i]]))
#angles = np.arctan(np.array(Planet_mercuryy[listofminimums[:]])/np.array(Planet_mercuryx[listofminimums[:]]))
plt.plot(angles)
plt.show()



initialtheta = 0
finaltheta = np.arctan(float(Planet_mercuryy[listofminimums[-1]])/float(Planet_mercuryx[listofminimums[-1]]))
time = (listofminimums[-1])/(len(Planet_mercuryy))
thetapercenturygr = 3600*180*(finaltheta-initialtheta)/(time*pi)
print(str(thetapercenturygr)+ ' is the gr thetapercentiry')


# ##NEW RUN
# os.system("./Project3 "+str(verlet) + " " + "initial_data_mercury_perihelion.txt " + "positions_perihelion " + str(Years)+" "+str(numTimesteps)+" "+str(Sun)+" "+str(Mercury_GR))
# ##########



# ## Need to add array's for each planet
# Planet_sunx = []
# Planet_suny = []
# Planet_sunz = []
# Planet_mercuryx = []
# Planet_mercuryy = []
# Planet_mercuryz = []
# Planet_mercuryr = np.zeros(numTimesteps-1)

# file1 = open("positions_perihelion0",'r')
# file1.readline()

# for line in file1:
#     values = line.split()
#     Planet_sunx.append(float(values[0]))
#     Planet_suny.append(float(values[1]))
#     Planet_sunz.append(float(values[2]))

# file2 = open("positions_perihelion1",'r')
# file2.readline()

# i = 0
# minumimrzero=1
# minumimrone=1
# listofminimums = []
# for line in file2:
#     values = line.split()
#     Planet_mercuryx.append(float(values[0]))
#     Planet_mercuryy.append(float(values[1]))
#     Planet_mercuryz.append(float(values[2]))
#     Planet_mercuryr[i]=np.sqrt(float(values[0])**2+float(values[1])**2+float(values[2])**2)
#     if (Planet_mercuryr[i]<minumimrzero):
#         minumimrone=minumimrzero
#         minumimrzero=Planet_mercuryr[i]
#         #listofminimums.append(i)
#     if (i>1000) and (Planet_mercuryr[i]<(minumimrone*1.001)):
#        listofminimums.append(i)
#     i+=1
#     #print(i)

# os.system("rm "+"positions_perihelion0")
# os.system("rm "+"positions_perihelion1")

# ##Minumin point of perihelon
# #plt.plot(Planet_mercuryr)
# #plt.plot(listofminimums,Planet_mercuryr[listofminimums])
# #plt.show()
# angles = np.zeros(len(listofminimums))
# for i in range(len(listofminimums)):
#     angles[i]=np.arctan(np.array(Planet_mercuryy[listofminimums[i]])/np.array(Planet_mercuryx[listofminimums[i]]))
# #angles = np.arctan(np.array(Planet_mercuryy[listofminimums[:]])/np.array(Planet_mercuryx[listofminimums[:]]))
# #plt.plot(angles)
# #plt.show()



# initialtheta = 0
# finaltheta = np.arctan(float(Planet_mercuryy[listofminimums[-1]])/float(Planet_mercuryx[listofminimums[-1]]))
# time = (listofminimums[-1])/(numTimesteps-1)
# thetapercentury = 3600*180*(finaltheta-initialtheta)/(time*pi)

# print(thetapercentury+ 'is the non-gr thetapercentiry')


# ff = np.abs(np.fft.fft(Planet_mercuryr))
# fmax=ff[10:int(len(ff)/2)].argmax()
# #plt.plot(ff)
# #plt.show()
# print(fmax)





