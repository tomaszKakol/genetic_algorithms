import matplotlib.pyplot as plt
import csv
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

x = []
y = []
z = []

for line in open('plot_2_2.txt', 'r'):
  values = [float(s) for s in line.split()]
  x.append(values[0])
  y.append(values[1])
  z.append(values[2])  
#with open('plot.txt','r') as csvfile:
#    plots = csv.reader(csvfile, delimiter=' ')
#    for row in plots:
#        x.append(plots.split()[0])
 #       y.append(plots.split()[1])
 #       z.append(plots.split()[2])

# Plot the surface.
#surf = ax.plot_surface(x, y, z,cmap=cm.coolwarm,linewidth=0, antialiased=False)

# Add a color bar which maps values to colors.
#fig.colorbar(surf, shrink=0.5, aspect=5)
		
#fig = plt.figure()
#ax = fig.gca(projection='3d')
#ax.scatter3D(x, y, z, c=z, cmap='Greens');

# Create plot
fig = plt.figure()
ax = fig.gca(projection='3d')
ax.scatter3D(x, y, z, alpha=0.3, c=z,  cmap='Greens')

#fig = plt.figure()
#ax = plt.subplot(111)
#ax.plot(x,y, label='Loaded from file!')
plt.xlabel('X')
plt.ylabel('Y')
plt.title('Wartości funkcji GA_TestFunction(oś "Z") z krokiem " co 1" w osi "X" i "Y"')
#plt.legend()
plt.show()

#fig.savefig('plot2.png')