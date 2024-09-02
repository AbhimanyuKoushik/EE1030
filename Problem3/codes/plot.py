import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("triangle_points.txt", delimiter=',',max_rows=len(list(open("./triangle_points.txt")))-1)

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Since your C code generates points along one edge of the triangle, 
# we need to manually add the other two vertices to form the triangle.
x_full = np.append(x, [x[0]])
y_full = np.append(y, [y[0]])

# Plot the triangle
plt.figure()
plt.plot(x_full, y_full, label='Triangle Edges')
plt.fill(x_full, y_full, 'lightblue', alpha=0.5)
plt.xlabel("x")
plt.ylabel("y")
plt.title("Triangle formed by (0,4), (0,0), (3,0)")
plt.grid(True)
plt.legend()
plt.show()

