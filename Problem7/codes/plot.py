import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Load the points directly from the file (assuming the file has x,y,z format)
points = np.loadtxt('vector.dat', delimiter=',', max_rows=len(list(open("./vector.dat")))-1)

# Separate the points into X, Y, Z components
x_points = points[:, 0]
y_points = points[:, 1]
z_points = points[:, 2]

# Create the figure and 3D axis
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# Calculate vector components for the two paths
vector1 = np.array([x_points[20] - x_points[0],
                    y_points[20] - y_points[0],
                    z_points[20] - z_points[0]])

vector2 = np.array([x_points[41] - x_points[21],
                    y_points[41] - y_points[21],
                    z_points[41] - z_points[21]])

# Define unit vectors for the x, y, and z axes
x_axis = np.array([1, 0, 0])
y_axis = np.array([0, 1, 0])
z_axis = np.array([0, 0, 1])

# Function to calculate the angle between two vectors
def calculate_angle(v1, v2):
    cos_theta = np.dot(v1, v2) / (np.linalg.norm(v1) * np.linalg.norm(v2))
    angle = np.arccos(np.clip(cos_theta, -1.0, 1.0))
    return np.degrees(angle)

# Function to draw an angle arc
def draw_angle_arc(ax, origin, vector, axis_vector, angle, color='gray'):
    # Find a perpendicular vector to the plane formed by `vector` and `axis_vector`
    perp_vector = np.cross(vector, axis_vector)
    if np.linalg.norm(perp_vector) == 0:  # if the vectors are parallel
        perp_vector = np.cross(vector, [1, 0, 0])  # use any vector not parallel

    perp_vector /= np.linalg.norm(perp_vector)
    
    # Create points for the arc
    theta = np.linspace(0, np.radians(angle), 100)
    arc = np.outer(np.cos(theta), vector / np.linalg.norm(vector)) + np.outer(np.sin(theta), perp_vector)
    
    # Scale and translate the arc to the origin point
    arc = arc * 0.5  # scaling to make the arc visible, adjust as needed
    arc_x = origin[0] + arc[:, 0]
    arc_y = origin[1] + arc[:, 1]
    arc_z = origin[2] + arc[:, 2]
    
    ax.plot(arc_x, arc_y, arc_z, color=color, linestyle='--')

# Calculate angles with respect to the x, y, and z axes
angles1 = [calculate_angle(vector1, x_axis), calculate_angle(vector1, y_axis), calculate_angle(vector1, z_axis)]
angles2 = [calculate_angle(vector2, x_axis), calculate_angle(vector2, y_axis), calculate_angle(vector2, z_axis)]

# Plot the vectors as arrows using quiver
# Vector 1
ax.quiver(x_points[0], y_points[0], z_points[0],
          vector1[0], vector1[1], vector1[2],
          color='b', label='Vector Path 1', arrow_length_ratio=0.1)

# Vector 2
ax.quiver(x_points[0], y_points[0], z_points[0],
          vector2[0], vector2[1], vector2[2],
          color='r', label='Vector Path 2', arrow_length_ratio=0.1)

# Draw the x, y, z axes
ax.quiver(0, 0, 0, 1, 0, 0, color='black', arrow_length_ratio=0.1)
ax.quiver(0, 0, 0, 0, 1, 0, color='black', arrow_length_ratio=0.1)
ax.quiver(0, 0, 0, 0, 0, 1, color='black', arrow_length_ratio=0.1)

# Plot the XY, YZ, and ZX planes with transparency
# Define the grid
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

# For Vector 2
draw_angle_arc(ax, origin, vector2, x_axis, angles2[0], color='red')
draw_angle_arc(ax, origin, vector2, y_axis, angles2[1], color='red')
draw_angle_arc(ax, origin, vector2, z_axis, angles2[2], color='red')

# Annotate the angles on the plot
def annotate_angles(ax, origin, vector, angles, color):
    ax.text(origin[0], origin[1], origin[2], f'{angles[0]:.2f}°', color=color, fontsize=6, weight='bold')
    ax.text(origin[0] + vector[0] * 0.5, origin[1] + vector[1] * 0.5, origin[2] + vector[2] * 0.5,
            f'{angles[1]:.2f}°', color=color, fontsize=6, weight='bold')
    ax.text(origin[0] + vector[0] * 0.5, origin[1] + vector[1] * 0.5, origin[2],
            f'{angles[2]:.2f}°', color=color, fontsize=6, weight='bold')

# Annotate angles for Vector 1
annotate_angles(ax, origin, vector1, angles1, color='blue')

# Annotate angles for Vector 2
annotate_angles(ax, origin, vector2, angles2, color='red')

# Set the limits of the plot
ax.set_xlim([min(x_points)-1, max(x_points)+1])
ax.set_ylim([min(y_points)-1, max(y_points)+1])
ax.set_zlim([min(z_points)-1, max(z_points)+1])

# Add labels for the axes
ax.set_xlabel('X axis')
ax.set_ylabel('Y axis')
ax.set_zlabel('Z axis')

# Add a title
ax.set_title('3D Vector Plot of vector which has equal angles to all axes')
# Show the label for the vector
ax.legend()

# Save the plot to figs directory
plt.savefig('../figs/fig.png')
plt.show()

