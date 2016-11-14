import numpy as np
import matplotlib.pyplot as plt
import os as os


Gridsize = 20

Cycles = 50000



##########################################################################################################################################################

os.system("./Project4 "+"Gird20_Temp1_ordered.txt "+str(1)+" "+str(Cycles)+" "+str(Gridsize)+" "+str(1)+" "+str(2)+" "+str(5))


cycle_1_o = []
acceptedMoves_1_o = []
E_1_o = []
E_Average_1_o = []
absM_Average_1_o = []




file1 = open("Gird20_Temp1_ordered.txt",'r')
file1.readline()

for line in file1:
    values = line.split()
    cycle_1_o.append(float(values[0]))
    acceptedMoves_1_o.append(float(values[1]))
    E_1_o.append(float(values[2]))
    E_Average_1_o.append(float(values[3]))
    absM_Average_1_o.append(float(values[4]))
    
plt.figure(1)
plot2, =plt.plot(cycle_1_o,E_Average_1_o, label=("Energy Mean"))
plt.title("Mean Energy of the Isingmodel PDF as a function cycles, with temperature 1 and ordered intitalization")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Energy')
plt.legend(handles = [plot2])
plt.show()

plt.figure(2)
plot3, =plt.plot(cycle_1_o,absM_Average_1_o, label=("Absolute Magnetization Mean"))
plt.title("Mean Absolute Maginetization of the Isingmodel PDF as a function cycles")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Absolute Magnetization')
plt.legend(handles = [plot3])
plt.show()

plt.figure(3)
plot1, =plt.plot(cycle_1_o,acceptedMoves_1_o, label=("Number Of Accepted Moves"))
plt.title("Number of accepted moves as a function cycles, with temperature 1 and ordered intitalization")
plt.xlabel('Number of cycles')
plt.ylabel("Number of accepted moves")
plt.legend(handles = [plot1])
plt.show()

plt.figure(4)
plt.hist(E_1_o[20000:-1], 10)
plt.title("Probability Distribution Function as a function of Energy, with temperature 1 and ordered intitalization ")
plt.xlabel('Energy')
plt.ylabel("Number of Occurances")
plt.show()


#plt.savefig("Project_2_Wr="+str(float(omega[i]))+"_Columb_factor="+str(float(factor2[i]))+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i])+".png")


    

file1.close()

os.system("rm "+"Gird20_Temp1_ordered.txt")


##########################################################################################################################################################

os.system("./Project4 "+"Gird20_Temp1_random.txt "+str(2)+" "+str(Cycles)+" "+str(Gridsize)+" "+str(1)+" "+str(2)+" "+str(5))


cycle_1_r = []
acceptedMoves_1_r = []
E_1_r = []
E_Average_1_r = []
absM_Average_1_r = []




file2 = open("Gird20_Temp1_random.txt",'r')
file2.readline()

for line in file2:
    values = line.split()
    cycle_1_r.append(float(values[0]))
    acceptedMoves_1_r.append(float(values[1]))
    E_1_r.append(float(values[2]))
    E_Average_1_r.append(float(values[3]))
    absM_Average_1_r.append(float(values[4]))



    
plt.figure(5)
plot2, =plt.plot(cycle_1_r,E_Average_1_r, label=("Energy Mean"))
plt.title("Mean Energy of the Isingmodel PDF as a function cycles, with temperature 1 and random ititalization")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Energy')
plt.legend(handles = [plot2])
plt.show()

plt.figure(6)
plot3, =plt.plot(cycle_1_r,absM_Average_1_r, label=("Absolute Magnetization Mean"))
plt.title("Mean Absolute Maginetization of the Isingmodel PDF as a function cycles, with temperature 1 and random ititalization")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Absolute Magnetization')
plt.legend(handles = [plot3])
plt.show()

plt.figure(7)
plot1, =plt.plot(cycle_1_r,acceptedMoves_1_r, label=("Number Of Accepted Moves"))
plt.title("Number of accepted moves as a function cycles, with temperature 1 and random ititalization, with temperature 1 and random intitalization")
plt.xlabel('Number of cycles')
plt.ylabel("Number of accepted moves")
plt.legend(handles = [plot1])
plt.show()

plt.figure(8)
plt.hist(E_1_r[20000:-1], 10)
plt.title("Probability Distribution Function as a function of Energy, with temperature 1 and random ititalization ")
plt.xlabel('Energy')
plt.ylabel("Number of Occurances")
plt.show()
    

file2.close()

os.system("rm "+"Gird20_Temp1_random.txt")


##########################################################################################################################################################

os.system("./Project4 "+"Gird20_Temp2.4_ordered.txt "+str(1)+" "+str(Cycles)+" "+str(Gridsize)+" "+str(2.4)+" "+str(3)+" "+str(5))


cycle_2_o = []
acceptedMoves_2_o = []
E_2_o = []
E_Average_2_o = []
absM_Average_2_o = []




file3 = open("Gird20_Temp2.4_ordered.txt",'r')
file3.readline()

for line in file3:
    values = line.split()
    cycle_2_o.append(float(values[0]))
    acceptedMoves_2_o.append(float(values[1]))
    E_2_o.append(float(values[2]))
    E_Average_2_o.append(float(values[3]))
    absM_Average_2_o.append(float(values[4]))



    
plt.figure(9)
plot2, =plt.plot(cycle_2_o,E_Average_2_o, label=("Energy Mean"))
plt.title("Mean Energy of the Isingmodel PDF as a function cycles, with temperature 2.4 and ordered intitalization")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Energy')
plt.legend(handles = [plot2])
plt.show()

plt.figure(10)
plot3, =plt.plot(cycle_2_o,absM_Average_2_o, label=("Absolute Magnetization Mean"))
plt.title("Mean Absolute Maginetization of the Isingmodel PDF as a function cycles, with temperature 2.4 and ordered intitalization")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Absolute Magnetization')
plt.legend(handles = [plot3])
plt.show()

plt.figure(11)
plot1, =plt.plot(cycle_2_o,acceptedMoves_2_o, label=("Number Of Accepted Moves"))
plt.title("Number of accepted moves as a function cycles, with temperature 2.4 and ordered intitalization")
plt.xlabel('Number of cycles')
plt.ylabel("Number of accepted moves")
plt.legend(handles = [plot1])
plt.show()

plt.figure(12)
plt.hist(E_2_o[20000:-1], 10)
plt.title("Probability Distribution Function as a function of Energy, with temperature 2.4 and ordered intitalization ")
plt.xlabel('Energy')
plt.ylabel("Number of Occurances")
plt.show()
    

file3.close()

os.system("rm "+"Gird20_Temp2.4_ordered.txt")


##########################################################################################################################################################

os.system("./Project4 "+"Gird20_Temp2.4_random.txt "+str(2)+" "+str(Cycles)+" "+str(Gridsize)+" "+str(2.4)+" "+str(3)+" "+str(5))


cycle_2_r = []
acceptedMoves_2_r = []
E_2_r = []
E_Average_2_r = []
absM_Average_2_r = []




file4 = open("Gird20_Temp2.4_random.txt",'r')
file4.readline()

for line in file4:
    values = line.split()
    cycle_2_r.append(float(values[0]))
    acceptedMoves_2_r.append(float(values[1]))
    E_2_r.append(float(values[2]))
    E_Average_2_r.append(float(values[3]))
    absM_Average_2_r.append(float(values[4]))


    
plt.figure(13)
plot2, =plt.plot(cycle_2_r,E_Average_2_r, label=("Energy Mean"))
plt.title("Mean Energy of the Isingmodel PDF as a function cycles")
plt.xlabel('Number of cycles, with temperature 2.4 and random intitalization')
plt.ylabel('Unitless Energy')
plt.legend(handles = [plot2])
plt.show()

plt.figure(14)
plot3, =plt.plot(cycle_2_r,absM_Average_2_r, label=("Absolute Magnetization Mean"))
plt.title("Mean Absolute Maginetization of the Isingmodel PDF as a function cycles, with temperature 2.4 and random intitalization")
plt.xlabel('Number of cycles')
plt.ylabel('Unitless Absolute Magnetization')
plt.legend(handles = [plot3])
plt.show()

plt.figure(15)
plot1, =plt.plot(cycle_2_r,acceptedMoves_2_r, label=("Number Of Accepted Moves"))
plt.title("Number of accepted moves as a function cycles, with temperature 2.4 and random intitalization")
plt.xlabel('Number of cycles')
plt.ylabel("Number of accepted moves")
plt.legend(handles = [plot1])
plt.show()

plt.figure(16)
plt.hist(E_2_r[20000:-1], 10)
plt.title("Probability Distribution Function as a function of Energy, with temperature 2.4 and random intitalization ")
plt.xlabel('Energy')
plt.ylabel("Number of Occurances")
plt.show()

    

file4.close()

os.system("rm "+"Gird20_Temp2.4_random.txt")

