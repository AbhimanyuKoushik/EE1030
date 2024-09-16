import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("circ.dat", delimiter=',')

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Define the points from the C code
A = np.array([2, -4])  # Point A
P = np.array([3, 8])   # Point P
Q1 = np.array([-10, -3])  # Point Q1 from C code
Q2 = np.array([-10, -5])  # Point Q2 from C code

# Plot the circle
plt.plot(x, y, label='Circle')

# Plot points P, A, Q1, Q2
plt.scatter(A[0], A[1], color='green', marker='o', label='Point A (2, -4)')
plt.scatter(P[0], P[1], color='red', marker='o', label='Point P (3, 8)')
plt.scatter(Q1[0], Q1[1], color='purple', marker='o', label='Point Q1 (-10, -3)')
plt.scatter(Q2[0], Q2[1], color='orange', marker='o', label='Point Q2 (-10, -5)')

# Connect points with dashed lines
plt.plot([A[0], Q1[0]], [A[1], Q1[1]], color='gray', linestyle='--', label='Line A-Q1')
plt.plot([A[0], Q2[0]], [A[1], Q2[1]], color='gray', linestyle='--', label='Line A-Q2')

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Points P, A, Q1, Q2")
plt.grid(True)
plt.legend(loc='upper right')
plt.axis('equal')

# Save the plot to a file
plt.savefig('../figs/fig.png')
plt.show()

