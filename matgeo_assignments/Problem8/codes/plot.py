import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the points directly from the file (assuming the file has x,y,z format)
points = np.loadtxt('vector.dat', delimiter=',', max_rows=len(list(open("./vector.dat")))-3)

# Separate the points into X, Y, Z components
x_points = points[:, 0]
y_points = points[:, 1]
z_points = points[:, 2]

# Create the figure and 3D axis
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Calculate vector components for the path (20th point relative to the first point)
vector1 = np.array([x_points[20] - x_points[0],
                    y_points[20] - y_points[0],
                    z_points[20] - z_points[0]])

# Define unit vectors for the x, y, and z axes
x_axis = np.array([1, 0, 0])
y_axis = np.array([0, 1, 0])
z_axis = np.array([0, 0, 1])

# Function to calculate the angle between two vectors
def calculate_angle(v1, v2):
    cos_theta = np.dot(v1, v2) / (np.linalg.norm(v1) * np.linalg.norm(v2))
    angle = np.arccos(np.clip(cos_theta, -1.0, 1.0))
    return np.degrees(angle)

# Function to draw an angle arc between a vector and an axis
def draw_angle_arc(ax, origin, vector, axis_vector, angle, color='gray'):
    # Normalize the vectors
    vector = vector / np.linalg.norm(vector)
    axis_vector = axis_vector / np.linalg.norm(axis_vector)

    # Use spherical interpolation (slerp) to create the arc
    theta = np.linspace(0, np.radians(angle), 100)
    arc = np.outer(np.sin(theta), vector) + np.outer(np.cos(theta), axis_vector)
    
    # Scale and translate the arc to the origin point
    arc = arc * 0.5  # scaling to make the arc visible, adjust as needed
    arc_x = origin[0] + arc[:, 0]
    arc_y = origin[1] + arc[:, 1]
    arc_z = origin[2] + arc[:, 2]
    
    ax.plot(arc_x, arc_y, arc_z, color=color, linestyle='--')

# Calculate angles with respect to the x, y, and z axes
angles1 = [calculate_angle(vector1, x_axis), calculate_angle(vector1, y_axis), calculate_angle(vector1, z_axis)]

# Plot the vectors as arrows using quiver
ax.quiver(x_points[0], y_points[0], z_points[0],
          vector1[0], vector1[1], vector1[2],
          color='b', label='Vector B', arrow_length_ratio=0.06)

# Draw the x, y, z axes
ax.quiver(0, 0, 0, 1, 0, 0, color='black', arrow_length_ratio=0.1)
ax.quiver(0, 0, 0, 0, 1, 0, color='black', arrow_length_ratio=0.1)
ax.quiver(0, 0, 0, 0, 0, 1, color='black', arrow_length_ratio=0.1)

# Plot the XY, YZ, and ZX planes with transparency
xx, yy = np.meshgrid(np.linspace(min(x_points)-1, max(x_points)+1, 10),
                     np.linspace(min(y_points)-1, max(y_points)+1, 10))
zz = np.zeros_like(xx)
ax.plot_surface(xx, yy, zz, color='cyan', alpha=0.3, rstride=100, cstride=100)

yy, zz = np.meshgrid(np.linspace(min(y_points)-1, max(y_points)+1, 10),
                     np.linspace(min(z_points)-1, max(z_points)+1, 10))
xx = np.zeros_like(yy)
ax.plot_surface(xx, yy, zz, color='magenta', alpha=0.3, rstride=100, cstride=100)

xx, zz = np.meshgrid(np.linspace(min(x_points)-1, max(x_points)+1, 10),
                     np.linspace(min(z_points)-1, max(z_points)+1, 10))
yy = np.zeros_like(xx)
ax.plot_surface(xx, yy, zz, color='yellow', alpha=0.3, rstride=100, cstride=100)

# Draw angle arcs and labels
origin = np.array([x_points[0], y_points[0], z_points[0]])

# For Vector 1
draw_angle_arc(ax, origin, vector1, x_axis, angles1[0], color='blue')
draw_angle_arc(ax, origin, vector1, y_axis, angles1[1], color='blue')
draw_angle_arc(ax, origin, vector1, z_axis, angles1[2], color='blue')

# Annotate the angles in the upper left corner of the plot
def annotate_angles(ax, angles, color):
    annotation_text = f'Angle with X: {angles[0]:.2f}°\nAngle with Y: {angles[1]:.2f}°\nAngle with Z: {angles[2]:.2f}°'
    ax.text2D(0.05, 0.95, annotation_text, transform=ax.transAxes, color=color,
              fontsize=8, weight='normal', verticalalignment='top')

# Annotate angles for Vector 1 in the upper left corner
annotate_angles(ax, angles1, color='blue')

# Set the limits of the plot
ax.set_xlim([min(x_points)-1, max(x_points)+1])
ax.set_ylim([min(y_points)-1, max(y_points)+1])
ax.set_zlim([min(z_points)-1, max(z_points)+1])

# Add labels for the axes
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')

# Add a title
ax.set_title('3D Vector Plot with Angles Between Vector and Axes')
# Show the label for the vector
ax.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()

