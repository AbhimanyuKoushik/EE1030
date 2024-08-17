#Code by GVV Sharma
#September 12, 2023
#Revised July 21, 2024
#released under GNU GPL
#Point Vectors


import sys                                          #for path to external scripts
sys.path.insert(0, '/storage/emulated/0/EE1030/matgeo/codes/CoordGeo/')        #path to my scripts
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
from mpl_toolkits.mplot3d import Axes3D

#local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen


#if using termux
import subprocess
import shlex
#end if

#Given points
A = np.array(([2, 2,1])).reshape(-1,1) 
O = np.array(([0,0, 0])).reshape(-1,1)  



# Create a figure and a 3D Axes
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')

#Generating all lines
x_AO = line_gen(A,O)

#Generating Arrow
ax.quiver(0,0,0,A[0],A[1],A[2],color='b',arrow_length_ratio=0.05)


#Plotting all lines
ax.plot(x_AO[0,:],x_AO[1,:], x_AO[2,:],label='$AO$')

#Setting labeks, legends and titles
ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
plt.title("Given vector")
plt.legend(['vector'])

# Scatter plot
colors = np.arange(1, 3)  # Example colors
tri_coords = np.block([A, O])  # Stack A, B, C vertically
ax.scatter(tri_coords[0, :], tri_coords[1, :], tri_coords[2, :], c=colors)
vert_labels = ['A', 'B']

for i, txt in enumerate(vert_labels):
    # Annotate each point with its label and coordinates
    ax.text(tri_coords[0, i], tri_coords[1, i], tri_coords[2, i], f'{txt}\n({tri_coords[0, i]:.0f}, {tri_coords[1, i]:.0f}, {tri_coords[2, i]:.0f})',
             fontsize=12, ha='center', va='bottom')

ax.spines['top'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('zero')

'''
ax.spines['left'].set_visible(False)
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)
ax.spines['bottom'].set_visible(False)
plt.xlabel('$x$')
plt.ylabel('$y$')
plt.legend(loc='best')
'''
plt.grid() # minor
plt.axis('equal')

#if using termux
plt.savefig('/storage/emulated/0/EE1030/Problem1/figs/fig.pdf')
subprocess.run(shlex.split("termux-open /storage/emulated/0/EE1030/Problem1/figs/fig.pdf"))
#else
#plt.show()
