import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D



#Initialization test
totalruns = 10000
numberofbins = 8000
numberofagens = 800
initialcycles = 10000
transactions = 10
inputlambda = 0.25
inputgamma = 0
inputalpha = 0
normalization = 0.1000
command = "./Project5"+ " " + 'test' + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(inputlambda)+ " " + str(inputgamma)+ " " + str(inputalpha)+ " " + str(normalization)

print(command)
os.system(command)
file1 = open('testinit','r')
variance = []
for line in file1:
    variance.append(float(line))
file1.close()
plt.plot(variance)
plt.xlabel('Transactions')
plt.ylabel('Variance')
plt.savefig("testinit.png")
plt.close()
os.system("rm "+"testinit")
os.system('rm '+'test')

#Proper run for simple transactions
totalruns = 10000
numberofbins = 8000
numberofagens = 800
initialcycles = 2000
transactions = 10
lambdainput = 0.25
gammainput = 0
alphainput = 0
normalization = 0.1000
command = "./Project5"+ " " + 'propersimple' + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(inputlambda)+ " " + str(inputgamma)+ " " + str(inputalpha)+ " " + str(normalization)
print(command)
os.system(command)
file1 = open('propersimple','r')
count = []
bins = []
for line in file1:
    count.append(float(line.split()[0]))
    bins.append(float(line.split()[1]))
file1.close()
plt.plot(bins[0:30],count[0:30])
plt.xlabel('Money')
plt.ylabel('Count')
plt.savefig("Proper_simple_transaction.png")
plt.close()
os.system("rm "+"propersimpleinit")


