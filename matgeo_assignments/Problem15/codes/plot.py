import numpy as np
import matplotlib.pyplot as plt

# Load points from the file
points = np.loadtxt('parab.dat', delimiter=',', max_rows=len(list(open("./parab.dat")))-1)

# Extract x and y values
x = points[:, 0]
y = points[:, 1]

# Define points A, B, C, D
x1 = np.array([2, 4])
x2 = np.array([2, -4])

# Plot the parabola
plt.plot(x, y, label='Parabola')

# Plot the specific points
plt.scatter(x1[0], x1[1], color='green', marker='o', label='Point $X_1(2,4)$')
plt.scatter(x2[0], x2[1], color='red', marker='o', label='Point $X_2(2,-4)$')

# Define the line equation x = 2
line_y = np.linspace(min(y), max(y), 400)
line_x = line_y * 0 + 2

# Plot the line x=2
plt.plot(line_x, line_y, color='green', label='Line: x = 2')

# Fill the closed region between the parabola and the line x=2
# We want to fill only the region where x <= 2 (parabola on the left of the line)
plt.fill_between(x, y, where=(x <= 2), color='blue', alpha=0.3, label='Shaded Region')

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Parabola, Line, and Points $X_1$ & $X_2$")
plt.grid(True)
plt.legend(loc='upper right')
plt.axis('equal')

# Save the plot to a file
plt.savefig('../figs/fig.png')
plt.show()

