import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the points from the text file
points = np.loadtxt('points.dat', delimiter=',', usecols=(0, 1, 2))

# Extract the x, y, z coordinates
x = points[:, 0]
y = points[:, 1]
z = points[:, 2]

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the line through the points
ax.plot(x, y, z, label='Line through the points')

# Set labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Add a legend
ax.legend(loc='upper left')

# Set title
plt.title("Line passing through given points")

# Save the plot to a file
plt.savefig('../figs/fig.png')

# Show the plot
plt.show()

