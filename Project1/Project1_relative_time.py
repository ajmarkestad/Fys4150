import numpy as np

file = open('Results_General', 'r')
file.readline()
file.readline()
time_ratio = []
for line in file:
	times = line.split()[2:3]
	time_ratio.append(times[1]/times[0])
	print(time_ratio[-1])
file.close()