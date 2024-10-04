import numpy as np
import matplotlib.pyplot as plt

# Load points from the file
points = np.loadtxt('parab.dat', delimiter=',', max_rows=len(list(open("./parab.dat")))-1)

# Extract x and y values of the parabola
x = points[:, 0]
y = points[:, 1]

# Define specific points X1 and X2 (intersection points or other points)
x1 = np.array([1, 1])
x2 = np.array([0, 0])

# Plot the parabola
plt.plot(x, y, label='Parabola')

# Plot the specific points X1 and X2
plt.scatter(x1[0], x1[1], color='green', marker='o', label='Point $X_1(1,1)$')
plt.scatter(x2[0], x2[1], color='red', marker='o', label='Point $X_2(0,0)$')

# Define the line equation x = y for the same range as the parabola
line_x = np.linspace(min(x), max(x), 400)
line_y = line_x  # For x = y, they are the same

# Plot the line x = y
plt.plot(line_x, line_y, color='green', label='Line: x = y')

# Add labels for points X1 and X2
plt.text(x1[0] + 0.05, x1[1] - 0.05, '$X_1(1,1)$', color='green', fontsize=9)
plt.text(x2[0] - 0.1, x2[1] + 0.05, '$X_2(0,0)$', color='red', fontsize=9)

# Find the intersection region and shade
# Use interpolation to find y-values of the line at the parabola's x values
line_y_interp = np.interp(x, line_x, line_y)

# Shade the region between the parabola and the line where the parabola is below the line
plt.fill_between(x, y, line_y_interp, where=(y <= line_y_interp), color='blue', alpha=0.3, label='Shaded Region')

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Parabola, Line, and Points $X_1$ & $X_2$")
plt.grid(True)
plt.legend(loc='lower right')
plt.axis('equal')

# Save the plot to a file
plt.savefig('../figs/fig.png')
plt.show()

