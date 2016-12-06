import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D

multiplier_bins = 2 #Increases the x-axis resolution(4-10 is fair)
multiplier = 0.1    # Increases the precision on the y-axis (0.5+ for good resolution)
multiplier_transactions = 1
multiplier_initial = 1

plotmax = 40*multiplier_bins    #scales the length of the plot

from functions import * #functions required 





#Savings included(lambda model)

totalruns =int(10000*multiplier)
numberofagens = 500
numberofbins = int(2000*multiplier_bins)
initialcycles = 800
transactions = 20*multiplier_transactions
lambdainput = [0,0.25,0.9]
inputgamma = 0
inputalpha = 0
normalization = 1.0
handles = []
power = []
for lambdaint in lambdainput:
    command = "./Project5"+ " " + 'saving' + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdaint)+ " " + str(inputgamma)+ " " + str(inputalpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open('saving','r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    #plt.plot(xv,yv)
    os.system("rm "+"saving")
    os.system("rm "+"savinginit")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$\lambda = 0.0$','$\lambda = 0.25$','$\lambda = 0.9$'),'upper right')
plt.savefig("Saving.png")
plt.close()
print("Saving: Alphas: {}, {}, {}".format(power[0],power[1],power[2]))
file = open("saving.txt",'w')
file.write("Alphas: {}, {}, {}".format(power[0],power[1],power[2]))
file.close()



#
#nearest neighbour interactions (alpha model) N=500
totalruns = 20000*multiplier
numberofbins = 2000*multiplier_bins
numberofagens = 500
initialcycles = 800
transactions = 20*multiplier_transactions
gammainput = 0
alphainput = [0.5,1.0,1.5,2.0]
normalization = 10.0
handles = []
power = []
namestem = 'agents={}_alpha={}_lambda={}'

lambdainput = 0.5
for alpha in alphainput:
    name = namestem.format(numberofagens,alpha,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(alpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$alpha = 0.5$','$alpha = 1.0$','$alpha = 1.5$','$alpha = 2.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file.close()

lambdainput = 0.25
handles = []
power = []
for alpha in alphainput:
    name = namestem.format(numberofagens,alpha,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(alpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$alpha = 0.5$','$alpha = 1.0$','$alpha = 1.5$','$alpha = 2.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file.close()

lambdainput = 0.9
handles = []
power = []
for alpha in alphainput:
    name = namestem.format(numberofagens,alpha,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(alpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$alpha = 0.5$','$alpha = 1.0$','$alpha = 1.5$','$alpha = 2.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file.close()



#N=1000
numberofbins = 4000*multiplier_bins
numberofagens = 1000
initialcycles = 800
transactions = 20*multiplier_transactions
gammainput = 0
alphainput = [0.5,1.0,1.5,2.0]
normalization = 10.0
handles = []
power = []
namestem = 'agents={}_alpha={}_lambda={}'

lambdainput = 0.5
for alpha in alphainput:
    name = namestem.format(numberofagens,alpha,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(alpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$alpha = 0.5$','$alpha = 1.0$','$alpha = 1.5$','$alpha = 2.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file.close()

lambdainput = 0.25
handles = []
power = []
for alpha in alphainput:
    name = namestem.format(numberofagens,alpha,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(alpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$alpha = 0.5$','$alpha = 1.0$','$alpha = 1.5$','$alpha = 2.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file.close()

lambdainput = 0.9
handles = []
power = []
for alpha in alphainput:
    name = namestem.format(numberofagens,alpha,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(inputgamma)+ " " + str(alpha)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$alpha = 0.5$','$alpha = 1.0$','$alpha = 1.5$','$alpha = 2.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}".format(power[0],power[1],power[2],power[3]))
file.close()



#Previous agents preferred
numberofbins = 4000*multiplier_bins
numberofagens = 1000
initialcycles = 800*multiplier_initial
transactions = 20*multiplier_transactions
gammainput = [0.0,1.0,2.0,3.0,4.0]
normalization = 10.0
handles = []
power = []
namestem = 'gamma={}_agents={}_alpha={}_lambda={}'

alphainput = 1.0
lambdainput = 0.0
for gamma in gammainput:
    name = namestem.format(gamma,numberofagens,alphainput,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(gamma)+ " " + str(alphainput)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$\gamma = 0.0$','$\gamma = 1.0$','$\gamma = 2.0$','$\gamma = 3.0$','$\gamma = 4.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file.close()


alphainput = 2.0
lambdainput = 0.0
for gamma in gammainput:
    name = namestem.format(gamma,numberofagens,alphainput,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(gamma)+ " " + str(alphainput)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$\gamma = 0.0$','$\gamma = 1.0$','$\gamma = 2.0$','$\gamma = 3.0$','$\gamma = 4.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file.close()


alphainput = 1.0
lambdainput = 0.5
for gamma in gammainput:
    name = namestem.format(gamma,numberofagens,alphainput,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(gamma)+ " " + str(alphainput)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$\gamma = 0.0$','$\gamma = 1.0$','$\gamma = 2.0$','$\gamma = 3.0$','$\gamma = 4.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file.close()


alphainput = 2.0
lambdainput = 0.5
for gamma in gammainput:
    name = namestem.format(gamma,numberofagens,alphainput,lambdainput)
    command = "./Project5"+ " " + name + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(lambdainput)+ " " + str(gamma)+ " " + str(alphainput)+ " " + str(normalization)
    print(command)
    os.system(command)
    file1 = open(name,'r')
    count = []
    bins = []
    for line in file1:
        count.append(float(line.split()[0]))
        bins.append(float(line.split()[1]))
    file1.close()
    [coeffs, xv, yv] = findpowerlaw(bins,count)
    power.append(coeffs[1])
    handl, = plt.plot(bins[0:plotmax],count[0:plotmax])
    handles.append(handl)
    os.system("rm "+name)
    os.system("rm "+name+"init")

plt.xlabel('Money')
plt.ylabel('Count')
plt.figlegend(handles,('$\gamma = 0.0$','$\gamma = 1.0$','$\gamma = 2.0$','$\gamma = 3.0$','$\gamma = 4.0$'),'upper right')
plt.savefig(name+".png")
plt.close()
print(name+"Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file = open(name+".txt",'w')
file.write("Alphas: {}, {}, {}, {}, {}".format(power[0],power[1],power[2],power[3], power[4]))
file.close()



