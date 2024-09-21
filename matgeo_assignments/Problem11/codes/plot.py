import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
def plot_triangle(filename, file_no=""):
    points = np.loadtxt(filename, delimiter=',')

    # Extract the x and y coordinates
    x = points[:, 0]
    y = points[:, 1]
    
    # Plot the triangle
    plt.figure()
    plt.plot(x, y, label='Triangle Edges')
    plt.fill(x, y, 'lightblue', alpha=0.5)
    plt.xlabel("x")
    plt.ylabel("y")
    plt.title("Triangle of side lengths " + str(round(((x[20] - x[0])**2 + (y[20] - y[0])**2)**0.5, 2)) + ", " +
              str(round(((x[41] - x[21])**2 + (y[41] - y[21])**2)**0.5, 2)) + ", " +
              str(round(((x[62] - x[42])**2 + (y[62] - y[42])**2)**0.5, 2)))
    plt.grid(True)
    plt.legend()

    # Save the plot to figs directory
    plt.savefig('../figs/fig' + str(file_no) + '.png')

plot_triangle('triangle1.dat','1')
plot_triangle('triangle2.dat','2')

