import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the points directly from the file (assuming the file has x,y,z format)
points = np.loadtxt('vector.dat', delimiter=',', max_rows=len(list(open("./vector.dat")))-1)

# Separate the points into X, Y, Z components
x_points = points[:, 0]
y_points = points[:, 1]
z_points = points[:, 2]

# Create the figure and 3D axis
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Plot the vector as an arrow using quiver
# Starting point (x_points[0], y_points[0], z_points[0])
# Arrow components (change in x, y, z)
ax.quiver(x_points[0], y_points[0], z_points[0],
          x_points[20] - x_points[0],
          y_points[20] - y_points[0],
          z_points[20] - z_points[0],
          color='b', label='Generated Vector Path 1', arrow_length_ratio=0.06)
          
ax.quiver(x_points[0], y_points[0], z_points[0],
          x_points[41] - x_points[21],
          y_points[41] - y_points[21],
          z_points[41] - z_points[21],
          color='r', label='Generated Vector Path 2', arrow_length_ratio=0.06)

# Set the limits of the plot
ax.set_xlim([min(x_points)-1, max(x_points)+1])
ax.set_ylim([min(y_points)-1, max(y_points)+1])
ax.set_zlim([min(z_points)-1, max(z_points)+1])

# Add labels for the axes
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')

# Add a title
ax.set_title('3D Vector Plot from C Generated Points')

# Show the label for the vector
ax.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()

