import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D

multiplier_bins = 10 #Increases the x-axis resolution(4-10 is fair)
plotmax = 20*multiplier_bins    #scales the length of the plot

from functions import * #functions required 




#Previous agents preferre
totalruns = 1500
numberofbins = int(2000*multiplier_bins)
numberofagens = 500
initialcycles = 1000
transactions = 10000
normalization = 3.0
handles = []
power = []
fullpower=[]
powersfile = 'historic_powers.txt'
namestem = 'gamma={}_agents={}_alpha={}_lambda={}'
file = open(powersfile,'w')




filenames = 'examplerun'
alphainput = 1.0
lambdas = [0.05, 0.7]
gamma = 1.0 
handles = []
handlesinit = []
for lambdainput in lambdas:
	name = namestem.format(gamma,numberofagens,alphainput,lambdainput)
	command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(gamma)+ " " + str(alphainput)+ " " + str(normalization)
	print(command)
	os.system(command)

	#find the distribution
	file1 = open(name,'r')
	count = []
	bins = []
	for line in file1:
	    count.append(float(line.split()[0]))
	    bins.append(float(line.split()[1]))
	file1.close()

	#find the variance	    
	file1 = open(name+'init','r')
	variance = []
	for line in file1:
	    variance.append(float(line))
	file1.close()


	[coeffs, xv, yv, errors] = findpowerlaw(bins,count)
	power.append(coeffs[1])
	power.append(errors)
	fullpower.append(coeffs[1])
	fullpower.append(errors)

	plt.figure(1)
	handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
	handles.append(handl)
	plt.figure(2)
	handles2, =plt.plot(variance)
	handlesinit.append(handles2)


plt.figure(1)
plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$\lambda = 0.05 $','$\lambda = 0.7$'),'upper right')
plt.savefig(filenames+".png")
plt.close()

plt.figure(2)
plt.xlabel('Runs')
plt.ylabel('Variance of the wealth distribution')
plt.figlegend(handlesinit,('$\lambda = 0.05 $','$\lambda = 0.7$'),'upper right')
plt.savefig(filenames+"init.png")
plt.close()

file.write("Nu: {}, {}\n".format(power[0],power[2]))
file.write("Errors: {}, {}\n".format(power[1],power[3]))
file.close()

