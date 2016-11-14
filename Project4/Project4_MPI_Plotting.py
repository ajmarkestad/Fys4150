import numpy as np
import matplotlib.pyplot as plt
import os as os

## Need to add array's for each planet
Temperature1 = []
MeanEnergy1 = []
MeanAbsoluteMagnetization1 = []
SpecificHeatCapacity1 = []
MagneticSuseptebility1 = []

Temperature2 = []
MeanEnergy2 = []
MeanAbsoluteMagnetization2 = []
SpecificHeatCapacity2 = []
MagneticSuseptebility2 = []

Temperature3 = []
MeanEnergy3 = []
MeanAbsoluteMagnetization3 = []
SpecificHeatCapacity3 = []
MagneticSuseptebility3 = []

Temperature4 = []
MeanEnergy4 = []
MeanAbsoluteMagnetization4 = []
SpecificHeatCapacity4 = []
MagneticSuseptebility4 = []




file1 = open("Gird40_Temp2.15-2.35_12Kernel.txt",'r')
file1.readline()

for line in file1:
    values = line.split()
    Temperature1.append(float(values[0]))
    MeanEnergy1.append(float(values[1]))
    MeanAbsoluteMagnetization1.append(float(values[5]))
    SpecificHeatCapacity1.append(float(values[2]))
    MagneticSuseptebility1.append(float(values[4]))



file2 = open("Gird60_Temp2.15-2.35_12Kernel.txt",'r')
file2.readline()

for line in file2:
    values = line.split()
    Temperature2.append(float(values[0]))
    MeanEnergy2.append(float(values[1]))
    MeanAbsoluteMagnetization2.append(float(values[5]))
    SpecificHeatCapacity2.append(float(values[2]))
    MagneticSuseptebility2.append(float(values[4]))




file3 = open("Gird100_Temp2.15-2.35_12Kernel.txt",'r')
file3.readline()

for line in file3:
    values = line.split()
    Temperature3.append(float(values[0]))
    MeanEnergy3.append(float(values[1]))
    MeanAbsoluteMagnetization3.append(float(values[5]))
    SpecificHeatCapacity3.append(float(values[2]))
    MagneticSuseptebility3.append(float(values[4]))




file4 = open("Gird140_Temp2.15-2.35_12Kernel.txt",'r')
file4.readline()

for line in file4:
    values = line.split()
    Temperature4.append(float(values[0]))
    MeanEnergy4.append(float(values[1]))
    MeanAbsoluteMagnetization4.append(float(values[5]))
    SpecificHeatCapacity4.append(float(values[2]))
    MagneticSuseptebility4.append(float(values[4]))






plt.figure(1)
plot1_1, =plt.plot(Temperature1,MeanEnergy1, label=("40x40 Lattice"))
plot1_2, =plt.plot(Temperature2,MeanEnergy2, label=("60x60 Lattice"))
plot1_3, =plt.plot(Temperature3,MeanEnergy3, label=("100x100 Lattice"))
plot1_4, =plt.plot(Temperature4,MeanEnergy4, label=("140x140 Lattice"))
plt.title("Mean Energy of the Isingmodel for varying grid size as fuction of temperature")
plt.xlabel('Temperature')
plt.ylabel('Mean Energy')
plt.legend(handles = [plot1_1,plot1_2,plot1_3,plot1_4])
plt.show()

plt.figure(2)
plot2_1, =plt.plot(Temperature1,MeanAbsoluteMagnetization1, label=("40x40 Lattice"))
plot2_2, =plt.plot(Temperature2,MeanAbsoluteMagnetization2, label=("60x60 Lattice"))
plot2_3, =plt.plot(Temperature3,MeanAbsoluteMagnetization3, label=("100x100 Lattice"))
plot2_4, =plt.plot(Temperature4,MeanAbsoluteMagnetization4, label=("140x140 Lattice"))
plt.title("Mean Absolute Maginetization of the Isingmodel for varying grid size as fuction of temperature")
plt.xlabel('Temperature')
plt.ylabel('Mean Absolute Magnetization')
plt.legend(handles = [plot2_1,plot2_2,plot2_3,plot2_4])
plt.show()

plt.figure(3)
plot3_1, =plt.plot(Temperature1,SpecificHeatCapacity1, label=("40x40 Lattice"))
plot3_2, =plt.plot(Temperature2,SpecificHeatCapacity2, label=("60x60 Lattice"))
plot3_3, =plt.plot(Temperature3,SpecificHeatCapacity3, label=("100x100 Lattice"))
plot3_4, =plt.plot(Temperature4,SpecificHeatCapacity4, label=("140x140 Lattice"))
plt.title("Scpecific Heat Capacity of the Isingmodel for varying grid size as fuction of temperature")
plt.xlabel('Temperature')
plt.ylabel("Specific Heat Capacity $C_v$")
plt.legend(handles = [plot3_1,plot3_2,plot3_3,plot3_4])
plt.show()


plt.figure(4)
plot4_1, =plt.plot(Temperature1,MagneticSuseptebility1, label=("40x40 Lattice"))
plot4_2, =plt.plot(Temperature2,MagneticSuseptebility2, label=("60x60 Lattice"))
plot4_3, =plt.plot(Temperature3,MagneticSuseptebility3, label=("100x100 Lattice"))
plot4_4, =plt.plot(Temperature4,MagneticSuseptebility4, label=("140x140 Lattice"))
plt.title("Magnetic Suceptebility of the Isingmodel for varying grid size as fuction of temperature")
plt.xlabel('Temperature')
plt.ylabel("Magnetic Suseptebility $\chi$")
plt.legend(handles = [plot4_1,plot4_2,plot4_3,plot4_4])
plt.show()

file1.close()
file2.close()
file3.close()
file4.close()

