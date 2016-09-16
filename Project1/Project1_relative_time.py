import numpy as np

file = open('Results_General', 'r')
file.readline()
file.readline()
time_ratio = []
i=0
for line in file:
	times = line.split()[2:4]
	time_ratio.append((float(times[1])*100/float(times[0])))
	i+=1
file.close()

import matplotlib.pyplot as plt

a =range(1,i+1)
plt.plot(a,time_ratio)
plt.xlabel('power of 10**')
plt.ylabel('Time specified / time general %')
##plt.show()
plt.savefig('Time_relative.png')