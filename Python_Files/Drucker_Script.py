import numpy as np
import matplotlib.pyplot as plt

###########################################################
################ Plotter Dimensions #######################
###########################################################

base_length = 800	# Distance between Motors
height = 1000		# Canvas height
steps_per_rev = 400	# Steps per Revolution
rotor_diameter = 18 # Diameter of Axel
pi = np.pi			# PI
ds = 0.5 			# Step length in mm

###########################################################
################ Functions ################################
###########################################################

def calc_cord_length(x,y):
	c_left = np.sqrt((height-y)**2+x**2)
	c_right = np.sqrt((height-y)**2+(base_length-x)**2)
	return (c_left, c_right)
	
def calc_num_steps(l_left, l_right):
	cord_dist_left = l_left[1:]-l_left[0:-1]
	cord_dist_right = l_right[1:]-l_right[0:-1]
	num_steps_left = cord_dist_left/(pi*rotor_diameter/steps_per_rev)
	num_steps_right = cord_dist_right/(pi*rotor_diameter/steps_per_rev)
	return (num_steps_left, num_steps_right)
	
def calc_distance(x_start,x_end,y_start,y_end):
	return np.sqrt((abs(x_start-x_end))**2+(abs(y_start-y_end))**2)
	
def calc_line_coordinates(points_x, points_y, ds):
	x = np.empty([0])
	y = np.empty([0])
	for i in np.arange(1, len(points_x)):
		length = calc_distance(points_x[i-1], points_x[i], points_y[i-1], points_y[i])
		steps_per_line = length/ds
		x = np.append(x, np.linspace(points_x[i-1], points_x[i], steps_per_line))
		y = np.append(y, np.linspace(points_y[i-1], points_y[i], steps_per_line))
	return (x,y)
		
###########################################################
################ Picture ##################################
###########################################################	

x_coordinates = np.array([200,200,400,600,600,200,600,200,600])
y_coordinates = np.array([200,600,800,600,200,200,600,600,200])

coordinates = calc_line_coordinates(x_coordinates, y_coordinates, ds)
print(coordinates)
cord_lengths = calc_cord_length(coordinates[0], coordinates[1])
num_steps = calc_num_steps(cord_lengths[0], cord_lengths[1])


###########################################################
################ Plots ####################################
###########################################################

fig, axs = plt.subplots(2, 2)
#----------------------------------------------------------
ax = axs[0,0]
ax.set_title("Canvas")
ax.set_xlim([0,base_length])
ax.set_ylim([0,height])
ax.set_xlabel("width [mm]")
ax.set_ylabel("height [mm]")
ax.plot(coordinates[0], coordinates[1])
ax.scatter(x_coordinates, y_coordinates, c = 'green')
ax.grid(ls="--")
#----------------------------------------------------------
ax = axs[0,1]
ax.set_title("Cord Lengths")
ax.set_xlim([0, len(cord_lengths[0])])
ax.set_ylim([0, np.sqrt(base_length**2+height**2)])
ax.set_xlabel("steps")
ax.set_ylabel("cord_lengths")
ax.plot(np.arange(len(cord_lengths[0])), cord_lengths[0], label = "left Motor")
ax.plot(np.arange(len(cord_lengths[1])), cord_lengths[1], label = "right Motor")
ax.legend()
ax.grid(ls="--")
#----------------------------------------------------------
ax = axs[1,0]
ax.set_title("Number of Steps between points")
ax.set_xlim([0,len(num_steps[0])])
ax.set_xlabel("step")
ax.set_ylabel("number of steps between coordinates")
ax.plot(np.arange(len(num_steps[0])), num_steps[0], ls='dotted')
ax.plot(np.arange(len(num_steps[0])), num_steps[1], ls='dotted')
ax.grid(ls="--")
#----------------------------------------------------------
ax = axs[1,1]
ax.set_title("Ratio between steps of M1 and M2")
ax.set_xlim([0, len(num_steps[0])])
ax.set_ylim([0,100])
ax.set_xlabel("step")
ax.set_ylabel("steps(M1)/steps(M2)")
ax.plot(np.arange(len(num_steps[0])), abs(num_steps[0])/abs(num_steps[1]))
ax.grid(ls="--")

plt.show()
