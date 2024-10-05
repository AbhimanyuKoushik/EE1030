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

# Define the line equation x = y for the same range as the parabola
line_x = np.linspace(min(x), max(x), 201)
line_y = line_x  # For x = y, they are the same

# Use interpolation to find y-values of the line at the parabola's x values
line_y_interp = np.interp(x, line_x, line_y)

# Create subplots: one for the full plot, one for the blue shaded region
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 6))

# First subplot
ax1.plot(x, y, label='Parabola')
ax1.plot(line_x, line_y, color='green', label='Line: x = y')
ax1.scatter(x1[0], x1[1], color='green', marker='o', label='Point $X_1(1,1)$')
ax1.scatter(x2[0], x2[1], color='red', marker='o', label='Point $X_2(0,0)$')
ax1.text(x1[0] - 0.1, x1[1], '$X_1(1,1)$', color='green', fontsize=9)
ax1.text(x2[0] -0.04 , x2[1] + 0.05, '$X_2(0,0)$', color='red', fontsize=9)

# Shade the region between the parabola and the line where the parabola is below the line
# ax1.fill_between(x, y, line_y_interp, where=(y <= line_y_interp), color='blue', alpha=0.3, label='Region A')
ax1.fill_between(line_x, line_y, 0, where=(y <= line_y_interp), color='green', alpha=0.3, label='Region A2')
ax1.fill_between(x, y, where=(x <= line_y_interp), color='red', alpha=0.3, label='Region A1')

# Customize the first subplot
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.set_title("Parabola, Line, and Points $X_1$ & $X_2$")
ax1.grid(True)
ax1.legend(loc='lower right')
ax1.axis('equal')

# Second subplot
ax2.plot(x, y, label='Parabola')
ax2.plot(line_x, line_y, color='green', label='Line: x = y')
ax2.scatter(x1[0], x1[1], color='green', marker='o', label='Point $X_1(1,1)$')
ax2.scatter(x2[0], x2[1], color='red', marker='o', label='Point $X_2(0,0)$')
ax2.text(x1[0] - 0.1, x1[1], '$X_1(1,1)$', color='green', fontsize=9)
ax2.text(x2[0] -0.04 , x2[1] + 0.05, '$X_2(0,0)$', color='red', fontsize=9)
ax2.fill_between(x, y, line_y_interp, where=(y <= line_y_interp), color='blue', alpha=0.3, label='Region A')

# Customize the second subplot
ax2.set_xlabel("x")
ax2.set_ylabel("y")
ax2.set_title("Blue Shaded Region (Region A)")
ax2.grid(True)
ax2.legend(loc='lower right')
ax2.axis('equal')

# Adjust layout and save the plot
plt.tight_layout()
plt.savefig('../figs/fig.png')
plt.show()

