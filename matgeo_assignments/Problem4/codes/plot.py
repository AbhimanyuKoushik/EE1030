import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("perp_bisect.dat", delimiter=',',max_rows=len(list(open("./perp_bisect.dat")))-1)

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Define the points A, B, and (0,9)
A = np.array([6, 5])
B = np.array([-4, 3])
C = np.array([0, 9])

# Plot the perpendicular bisector
plt.figure()
plt.plot(x, y, label='Perpendicular Bisector', linestyle='-', color='blue')

# Plot the points A, B, and (0,9)
plt.scatter(A[0], A[1], color='red', marker='o', label='Point A (6, 5)')
plt.scatter(B[0], B[1], color='green', marker='o', label='Point B (-4, 3)')
plt.scatter(C[0], C[1], color='purple', marker='o', label='Point C (0, 9)')

# Optionally, connect A, B, and C with lines
plt.plot([A[0], B[0]], [A[1], B[1]], color='gray', linestyle='--', label='Line AB')
plt.plot([B[0], C[0]], [B[1], C[1]], color='gray', linestyle='--', label='Line BC')
plt.plot([C[0], A[0]], [C[1], A[1]], color='gray', linestyle='--', label='Line CA')

# Fill the area under the perpendicular bisector (if needed)
plt.fill(x, y, 'lightblue', alpha=0.5)

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Perpendicular Bisector of line joining points A, B, and C")
plt.grid(True)
plt.legend()
plt.savefig('../figs/fig.png')
plt.show()

