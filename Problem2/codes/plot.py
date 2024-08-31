import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the points from the text file
points = np.loadtxt('points.txt', delimiter=',', usecols=(0,1,2))

# Extract the x, y, z coordinates
x = points[:, 0]
y = points[:, 1]
z = points[:, 2]

# Create a 3D plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the points
ax.plot(x, y, z, marker='o')

# Set labels
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
plt.legend(["Line through the points"])
plt.title("Line passing through given points")
# Show the plot
plt.show()

