import numpy as np
import matplotlib.pyplot as plt


f1 = np.loadtxt('Project_1_exact_and_computed_values_for_grid_size_10')
f2 = np.loadtxt('Project_1_exact_and_computed_values_for_grid_size_100')


x1 = []
computed1 = []
exact1 = []

x2 = []
computed2 = []
exact2 = []


n1 = len(f1)
n2 = len(f2)

for i in range(n1):
               x1.append(f1[i][2])
               computed1.append(f1[i][0])
               exact1.append(f1[i][1])
               
for i in range(n2):
               x2.append(f2[i][2])
               computed2.append(f2[i][0])
               exact2.append(f2[i][1])


plt.figure(1)
plt.plot(x1,computed1, label='Computed solution')
plt.plot(x1,exact1, label='Exact Solution')
plt.xlabel('Position in dirichlet boundary condition [x]')
plt.ylabel('Function value [u(x)]')
plt.legend()



plt.figure(2)
plt.plot(x2,computed2, label='Computed solution')
plt.plot(x2,exact2, label='Exact Solution')
plt.xlabel('Position in dirichlet boundary condition [x]')
plt.ylabel('Function value [u(x)]')
plt.legend()

plt.show()

