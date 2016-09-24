import numpy as np
import matplotlib.pyplot as plt
import os as os


omega = str(3)
factor2 = str(3)
grid_size = [10,50,	100,150,200,300,400,700]
rho_stop=	[4,	4,	4,	4,	4,	4,	4,	4]

n = len(grid_size)

time = []
time_arma=[]

for i in range(n):
	##Runs the program which saves the eigenvalues/vectors to files
	## and then open the files and makes plots
	os.system("./Project2 "+str(grid_size[i])+" "+omega+" "+factor2+" "+str(rho_stop[i]))
	file = open("Project_2_Wr="+omega+"_Columb_factor="+factor2+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i]),'r')
	file.readline()
	eigvalues = file.readline().split()
	time.append(float(eigvalues[3]))
	time_arma.append(float(eigvalues[4]))
	file.close()
	os.system("rm "+"Project_2_Wr="+omega+"_Columb_factor="+factor2+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i]))

coeff = np.polyfit(np.log10(grid_size),np.log10(time),1)
coeff_arma = np.polyfit(np.log10(grid_size),np.log10(time_arma),1)
plt.figure(1)
time, =plt.plot(np.log10(grid_size),np.log10(time), label="Jacobi's method a={:.2f}".format(float(coeff[0])))
time_arma, =plt.plot(np.log10(grid_size),np.log10(time_arma), label="Divide-and-conquer a={:.2f}".format(float(coeff_arma[0])))
plt.xlabel('log10(Grid Size)')
plt.ylabel('log10(Time (s))')
plt.title("Scaling of time spent vs grid size. $T \propto n^{a}$")
plt.legend(handles = [time,time_arma])
plt.savefig("Project2_scaling_time.png")

plt.show()






