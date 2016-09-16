import numpy as np
import matplotlib.pyplot as plt
import os as os


##Compiles the program. Change the Project1.pro to fit your computer
os.system("make")
##Runs the program 
os.system("./Project1")
##Calculates the relative times of the algorithm and creates figures
os.system("python3 Project1_relative_time.py ")


f1 = np.loadtxt('Project_1_exact_and_computed_values_for_grid_size_10')
f2 = np.loadtxt('Project_1_exact_and_computed_values_for_grid_size_100')
f3 = np.loadtxt('Project_1_exact_and_computed_values_for_grid_size_1000')

x1 = []
computed1 = []
exact1 = []

x2 = []
computed2 = []
exact2 = []

x3 = []
computed3 =[]
exact3 = []

n1 = len(f1)
n2 = len(f2)
n3 = len(f3)

for i in range(n1):
               x1.append(f1[i][2])
               computed1.append(f1[i][0])
               exact1.append(f1[i][1])
               
for i in range(n2):
               x2.append(f2[i][2])
               computed2.append(f2[i][0])
               exact2.append(f2[i][1])

for i in range(n3):
               x3.append(f3[i][2])
               computed3.append(f3[i][0])
               exact3.append(f3[i][1])


               

plt.figure(1)
plt.plot(x1,computed1, label='Computed solution')
plt.plot(x1,exact1, label='Exact Solution')
plt.xlabel('Position in dirichlet boundary condition [x]')
plt.ylabel('Function value [u(x)]')
plt.title('Grid size n = 10')
plt.legend()
plt.savefig('n=10.png')



plt.figure(2)
plt.plot(x2,computed2, label='Computed solution')
plt.plot(x2,exact2, label='Exact Solution')
plt.xlabel('Position in dirichlet boundary condition [x]')
plt.ylabel('Function value [u(x)]')
plt.title('Grid size n = 100')
plt.legend()
plt.savefig('n=100.png')


plt.figure(3)
plt.plot(x3,computed3, label='Computed solution')
plt.plot(x3,exact3, label='Exact Solution')
plt.xlabel('Position in dirichlet boundary condition [x]')
plt.ylabel('Function value [u(x)]')
plt.title('Grid size n = 1000')
plt.legend()
plt.savefig('n=1000.png')

