import matplotlib.pyplot as plt
import csv
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

#,best[i],median[i],offlineMax[i],offlineMin[i],online[i]
y1 = []
y2 = []
y3 = []
y4 = []
y5 = []
popsize = np.arange(1,101)

for line in open('wyniki3.txt', 'r'):
  values = [float(s) for s in line.split()]
  y1.append(values[0])
  y2.append(values[1])
  y3.append(values[2])
  y4.append(values[3])
  y5.append(values[4])    
  
fig = plt.figure()
ax1 = fig.add_subplot(321)
ax2 = fig.add_subplot(322)
ax3 = fig.add_subplot(323)
ax4 = fig.add_subplot(324)
ax5 = fig.add_subplot(325)

ax1.plot(popsize, y1)
ax2.plot(popsize, y2)
ax3.plot(popsize, y3)
ax4.plot(popsize, y4)
ax5.plot(popsize, y5)

# Set common labels
ax1.set_xlabel('Nr Pokolenia')
ax1.set_ylabel('Best')
ax2.set_xlabel('Nr Pokolenia')
ax2.set_ylabel('Mediana')
ax3.set_xlabel('Nr Pokolenia')
ax3.set_ylabel('offline Max')
ax4.set_xlabel('Nr Pokolenia')
ax4.set_ylabel('offline Max')
ax5.set_xlabel('Nr Pokolenia')
ax5.set_ylabel('online')


plt.show()
