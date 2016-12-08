import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D

multiplier_bins = 10 #Increases the x-axis resolution(4-10 is fair)
multiplier = 1    # Increases the precision on the y-axis (0.5+ for good resolution)
multiplier_initial = 1

plotmax = 20*multiplier_bins    #scales the length of the plot

from functions import *


#Savings included(lambda model)

totalruns =1050
numberofagens = 500
numberofbins = int(2000*multiplier_bins)
initialcycles = 1000
transactions = 2000
lambdainput = 0.25
inputgamma = 1
inputalpha = 1
normalization = [0.03, 0.3,3,30]
handles = []
handlesinit = []
power = []
namestem = 'gamma={}_agents={}_alpha={}_lambda={}_normalization={}'

for norm in normalization:
	name = namestem.format(inputgamma,numberofagens,inputalpha,lambdainput,norm)
	command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(inputalpha)+ " " + str(norm)
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


	[coeffs, xv, yv] = findpowerlaw(bins,count)
	power.append(coeffs[1])

	plt.figure(1)
	handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
	handles.append(handl)
	plt.figure(2)
	handles2, =plt.plot(variance)
	handlesinit.append(handles2)

plt.figure(1)
plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$norm = 0.03$','$norm = 0.3$','$norm = 3$','$norm = 30$'),'upper right')
plt.savefig("norm.png")
plt.close()

plt.figure(2)
plt.xlabel('Runs')
plt.ylabel('Variance of the wealth distribution')
plt.figlegend(handlesinit,('$norm = 0.03$','$norm = 0.3$','$norm = 3$','$norm = 30$'),'upper right')
plt.savefig('norminit.png')
plt.close()


