import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Define the vector components
x = np.array([2, 2, 2])

# Create the figure and 3D axis
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Define the origin
origin = np.array([0, 0, 0])

# Plot the vector
ax.quiver(origin[0], origin[1], origin[2], 
          x[0], x[1], x[2], 
          color='b', arrow_length_ratio=0.06, label='2i + 2j + 2k')

# Set the limits of the plot
ax.set_xlim([0, 3])
ax.set_ylim([0, 3])
ax.set_zlim([0, 3])

# Add labels for the axes
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')

# Add a title
ax.set_title('3D Vector Plot')

# Show the label for the vector
ax.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()
