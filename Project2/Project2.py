import numpy as np
import matplotlib.pyplot as plt
import os as os


# Non-interacting case
omega = 	[0.01, 0.5, 1, 5]
factor2 = 	[0, 0, 0, 0]
rho_stop = 	[12, 5, 5, 5]
grid_size = []
precision = 3

# Interaction case varying omega
# omega = 	[0.01, 0.5, 1, 5]
# factor2 = 	[1, 1, 1, 1]
# rho_stop = 	[12, 5, 5, 5]
# grid_size = []
# precision = 2


# Interaction case varying factor2
# omega = 	[1, 1, 1, 1]
# factor2 = 	[0.1, 1, 10, 100]
# rho_stop = 	[8, 8, 8, 8]
# grid_size = []
# precision = 2


for i in range(len(rho_stop)):
	grid_size.append(int(rho_stop[i]*100*precision))


n = len(omega)

for i in range(n):
	##Runs the program which saves the eigenvalues/vectors to files
	## and then open the files and makes plots
	os.system("./Project2 "+str(grid_size[i])+" "+str(omega[i])+" "+str(factor2[i])+" "+str(rho_stop[i]))
	file = open("Project_2_Wr="+str(int(omega[i]))+"_Columb_factor="+str(int(factor2[i]))+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i]),'r')
	file.readline()

	eigvector1 = []
	eigvector2 = []
	eigvector3 = []
	eigvalues = file.readline().split()
	file.readline()
	for line in file:
		values = line.split()
		eigvector1.append(float(values[0])**2)
		eigvector2.append(float(values[1])**2)
		eigvector3.append(float(values[2])**2)
	plt.figure(i)
	x = np.linspace(0,rho_stop[i],grid_size[i])
	eig1, =plt.plot(x,eigvector1, label=("E= {:.2f}".format(float(eigvalues[0]))))
	eig2, =plt.plot(x,eigvector2, label=("E= {:.2f}".format(float(eigvalues[1]))))
	eig3, =plt.plot(x,eigvector3, label=("E= {:.2f}".format(float(eigvalues[2]))))
	plt.title('Eigenvectors with $\omega$ = '+str(int(omega[i])) + ",Columbfactor = "+str(int(factor2[i]))+", n= "+str(grid_size[i]))
	plt.ylabel('$|\psi|^2$')
	plt.xlabel('rho - dimensionless')
	plt.legend(handles = [eig1,eig2,eig3])
	plt.savefig("Project_2_Wr="+str(float(omega[i]))+"_Columb_factor="+str(float(factor2[i]))+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i])+".png")
	file.close()


	os.system("rm "+"Project_2_Wr="+str(int(omega[i]))+"_Columb_factor="+str(int(factor2[i]))+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i]))

handle=[]
plt.figure(5)
for i in range(n):
	##Runs the program which saves the eigenvalues/vectors to files
	## and then open the files and makes plots
	os.system("./Project2 "+str(grid_size[i])+" "+str(omega[i])+" "+str(factor2[i])+" "+str(rho_stop[i]))
	file = open("Project_2_Wr="+str(int(omega[i]))+"_Columb_factor="+str(int(factor2[i]))+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i]),'r')
	file.readline()

	eigvector1 = []
	eigvalues = file.readline().split()
	file.readline()
	for line in file:
		values = line.split()
		eigvector1.append(float(values[0])**2)
	x = np.linspace(0,rho_stop[i],grid_size[i])
	#Interaction varying omega
	eig1, =plt.plot(x,eigvector1, label=("Omega= {:.2f}".format(float(omega[i]))+". Eigenvalue= {:.2f}".format(float(eigvalues[0]))))
	#Interaction varying factor2
	#eig1, =plt.plot(x,eigvector1, label=("Coulomb = {:.2f}".format(float(factor2[i]))+". Eigenvalue= {:.2f}".format(float(eigvalues[0]))))
	handle.append(eig1)
	os.system("rm "+"Project_2_Wr="+str(int(omega[i]))+"_Columb_factor="+str(int(factor2[i]))+"_n="+str(grid_size[i])+"_rho_stop="+str(rho_stop[i]))

plt.title('Eigenvectors for lowest eigenvalues')
plt.ylabel('$|\psi|^2$')
plt.xlabel('rho - dimensionless')
plt.legend(handles = handle)
plt.savefig("Project_2_Wr=varying_omega.png")
file.close()