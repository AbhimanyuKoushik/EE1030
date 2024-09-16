import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("points.dat", delimiter=',',max_rows=len(list(open("./points.dat")))-1)

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Plotting the points A and B
A = np.array([0, 2 * (5 ** 0.5)])
B = np.array([-2 * (5 ** 0.5), 0])

plt.figure()  # Create a new figure for the plot
plt.plot(A[0], A[1], 'ro', label='Point A')  # Red dot for point A
plt.plot(B[0], B[1], 'bo', label='Point B')  # Blue dot for point B

# Plot the triangle
plt.plot(x, y, label='Line')
plt.xlabel("x")
plt.ylabel("y")
plt.title("Line passing given points")
plt.grid(True)
plt.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()
