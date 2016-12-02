import numpy as np
import matplotlib.pyplot as plt
import os as os
from mpl_toolkits.mplot3d import Axes3D

multiplier_bins = 2 #Increases the x-axis resolution(4-10 is fair)
multiplier = 0.1    # Increases the precision on the y-axis (0.5+ for good resolution)
multiplier_transactions = 1
multiplier_initial = 1

plotmax = 40*multiplier_bins    #scales the length of the plot
def powerlaw(x,a,alpha,c):
    return a*np.power(x,alpha)+c

def findpowerlaw(x,y):
     from scipy.optimize import curve_fit
     start = int(np.argmax(y)+1)
     end = np.nonzero(y)[0][-1]
     xarray = np.array(x[start:end])
     yarray = np.array(y[start:end])
     guess = (100,-1,0)
     print(end)
     print(start)
     coeffs,error = curve_fit(powerlaw, xarray,yarray,  p0=guess)
     xvals = np.linspace(x[start],x[end],1000)
     yext = powerlaw(xvals,coeffs[0],coeffs[1],coeffs[2])
     #plt.plot(xarray,yarray,'ko')
     #plt.plot(xvals,yext)
     #plt.savefig('test1.png')
     #plt.close()
     return coeffs, xvals, yext


#Initialization test
totalruns = 4000
numberofbins = 2000
numberofagens = 1000
initialcycles = 4000
transactions = 10
inputlambda = 0
inputgamma = 0
inputalpha = 0
normalization = 1
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
totalruns = 10000*multiplier
numberofagens = 500
numberofbins = 2000*multiplier_bins
initialcycles = 400
transactions = 20*multiplier_transactions
gammainput = 0
alphainput = 0
normalization = 1.0
command = "./Project5"+ " " + 'propersimple' + " " + str(totalruns)+ " " + str(numberofbins) + " " + str(numberofagens) + " " + str(initialcycles)+ " " + str(transactions)+ " " + str(inputlambda)+ " " + str(inputgamma)+ " " + str(inputalpha)+ " " + str(normalization)
print(command)
os.system(command)


file2 = open('propersimpleinit','r')
variance = []
for line in file2:
    variance.append(float(line))
file2.close()
plt.plot(variance)
plt.xlabel('Transactions')
plt.ylabel('Variance')
plt.savefig('propersimpleinit.png')
plt.close()

file1 = open('propersimple','r')
count = []
bins = []
for line in file1:
    count.append(float(line.split()[0]))
    bins.append(float(line.split()[1]))
file1.close()
plt.plot(bins[0:50],count[0:50])
plt.xlabel('Money')
plt.ylabel('Count')
plt.savefig("Proper_simple_transaction.png")
plt.close()
os.system("rm "+"propersimpleinit")

#logplot
logs = np.log(count[0:50])
plt.plot(np.log(bins[0:50]),logs)
plt.xlabel('Money')
plt.ylabel('log(Count)')
plt.savefig("Proper_simple_transaction_log.png")
plt.close()


#Savings included(lambda model)

totalruns =int(10000*multiplier)
numberofagens = 500
numberofbins = int(2000*multiplier_bins)
initialcycles = 800
transactions = 20*multiplier_transactions
lambdainput = [0,0.25,0.9]
gammainput = 0
alphainput = 0
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
initialcycles = 800*multiplier_initial
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
initialcycles = 800*multiplier_initial
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



#Previous interactions
numberofbins = 4000*multiplier_bins
numberofagens = 1000
initialcycles = 800
transactions = 20
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



