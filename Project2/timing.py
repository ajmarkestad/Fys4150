import numpy as np
import matplotlib.pyplot as plt
import os as os


omega = str(3)
factor2 = str(3)
grid_size = [10,50,100,150,200,250,300,400,600,1000]

n = len(grid_size)

time = []


for i in range(n):
	##Runs the program which saves the eigenvalues/vectors to files
	## and then open the files and makes plots
	os.system("./Project2 "+str(grid_size[i])+" "+omega+" "+factor2)
	file = open("Project_2_Wr="+omega+"_Columb_factor="+factor2+"_n="+str(grid_size[i]),'r')
	file.readline()
	eigvalues = file.readline().split()
	time.append(float(eigvalues[3]))
	file.close()
	os.system("rm "+"Project_2_Wr="+omega+"_Columb_factor="+factor2+"_n="+str(grid_size[i]))

coeff = np.polyfit(np.log10(grid_size),np.log10(time),1)
plt.figure(1)
plt.plot(np.log10(grid_size),np.log10(time))
plt.xlabel('log10(Grid Size)')
plt.ylabel('log10(Time (s))')
print(coeff[0])
print(coeff[1])
plt.title("Scaling of time spent vs grid size. $T \propto n^{a}, a$ ="+str(round(coeff[0],3)))
plt.savefig("Project2_scaling_time.png")

plt.show()






