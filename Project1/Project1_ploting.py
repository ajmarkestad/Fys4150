import numpy as np
import matplotlib.pyplot as plt


f1 = np.loadtxt('Project_1_exact_and_computed_values_for_grid_size_10')

x1 = []
computed1 = []
exact1 = []

n = len(f1)

for i in range(n):
               x1.append(f1[i][2])
               computed1.append(f1[i][0])
               exact1.append(f1[i][1])
               



plt.figure(1)
plt.plot(x1,computed1)
plt.plot(x1,exact1)

plt.show()



