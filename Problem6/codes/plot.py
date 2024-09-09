import numpy as np
import matplotlib.pyplot as plt
import os

# Load the points from the text file
points = np.loadtxt("points.dat", delimiter=',')

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Plot the triangle
plt.figure()
plt.plot(x, y, label='Line')
plt.xlabel("x")
plt.ylabel("y")
plt.title("Line passing given points")
plt.grid(True)
plt.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
