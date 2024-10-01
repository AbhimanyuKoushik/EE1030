import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("circ.dat", delimiter=',')

# Extract the x and y coordinates
x = points[:, 0]
y = points[:, 1]

# Calculate the centre and radius of the circle
centre = np.array([(points[0,0]+points[50,0])/2, (points[0,1]+points[50,1])/2])
radius = ((points[0,0] - centre[0])**2 + (points[0,1] - centre[1])**2)**(1/2)

# Define the line equation y = 4x - 3
line_x = np.linspace(min(x), max(x), 400)
line_y = 4*line_x - 3

# Define points A(2,3) and B(4,5)
x1 = np.array([2, 3])
x2 = np.array([4, 5])

# Plot the circle
plt.scatter(centre[0], centre[1], color='red', marker='o', label='Centre of the Circle')
plt.plot(x, y, label=f'Circle with radius {radius:.2f} and centre at ({centre[0]:.2f}, {centre[1]:.2f})')

# Plot the line y - 4x + 3 = 0
plt.plot(line_x, line_y, color='green', label='Line: y = 4x - 3')

# Plot points A and B
plt.scatter(x1[0], x1[1], color='blue', label='Point $X_1(2,3)$')
plt.scatter(x2[0], x2[1], color='purple', label='Point $X_2(4,5)$')

# Label point A on the plot
plt.text(x1[0] + 0.2, x1[1] - 0.3, '$X_1(2,3)$', color='blue', fontsize=9)
plt.text(x2[0] + 0.2, x2[1] - 0.3, '$X_2(4,5)$', color='purple', fontsize=9)
plt.text(centre[0] + 0.2, centre[1] - 0.7, '$C(4,5)$', color='red', fontsize=9)

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Circle, Line, and Points $X_1$ & $X_2$")
plt.grid(True)
plt.legend(loc='upper right')
plt.axis('equal')

# Save the plot to a file
plt.savefig('../figs/fig.png')
plt.show()

