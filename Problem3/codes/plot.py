import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("triangle_points.txt")

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Plot the triangle
plt.figure()
plt.plot(x, y, label='Triangle Edges')
plt.fill(x, y, 'lightblue', alpha=0.5)  # Fill the triangle with a light blue color
plt.xlabel("x")
plt.ylabel("y")
plt.title("Triangle formed by (0,4), (0,0), (3,0)")
plt.grid(True)
plt.legend()
plt.show()

