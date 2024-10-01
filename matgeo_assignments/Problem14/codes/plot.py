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
A = np.array([2, 3])
B = np.array([4, 5])

# Plot the circle
plt.scatter(centre[0], centre[1], color='red', marker='o', label='Centre of the Circle')
plt.plot(x, y, label=f'Circle with radius {radius:.2f} and centre at ({centre[0]:.2f}, {centre[1]:.2f})')

# Plot the line y - 4x + 3 = 0
plt.plot(line_x, line_y, color='green', label='Line: y = 4x - 3')

# Plot points A and B
plt.scatter(A[0], A[1], color='blue', label='Point A(2,3)')
plt.scatter(B[0], B[1], color='purple', label='Point B(4,5)')

# Label the axes and add a title
plt.xlabel("x")
plt.ylabel("y")
plt.title("Circle, Line, and Points A & B")
plt.grid(True)
plt.legend(loc='upper right')
plt.axis('equal')

# Save the plot to a file
plt.savefig('../figs/fig.png')
plt.show()

