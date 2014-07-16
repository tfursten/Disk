import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import colors
from matplotlib import cm

infile = open("sigma100.txt",'r')


maxX = 100
maxY = 100
X = 0.5*maxX
Y = 0.5*maxY
pop = np.zeros((maxX*maxY))

def xy2i(x,y,mx,my):
	return x*my+y

def i2xy(i,mx,my):
	return (i/my,i%my)

def wrap_around(x,w):
	return ((x%w)+w)%w

def disperse(x,y,nx,ny,mx,my):
	dx = x+nx
	dy = y+ny
	newX = wrap_around(dx,mx)
	newY = wrap_around(dy,my)
	return xy2i(newX,newY,mx,my)

for line in infile:
	xy = line.strip().split(' ')
	x = int(xy[0])
	y = int(xy[1])
	i = disperse(X,Y,x,y,maxX,maxY)
	pop[i] += 1
s = pop.sum()
print s

pop = np.array([i/float(s) for i in pop])

pop = pop.reshape((maxX,maxY))

fig,ax = plt.subplots(figsize=(5,5))
cax = ax.imshow(pop, interpolation='nearest',cmap=cm.binary)
ax.spines['right'].set_visible(False)
ax.spines['top'].set_visible(False)
ax.spines['left'].set_visible(False)
ax.spines['bottom'].set_visible(False)
plt.tick_params(axis='x',which='both',bottom='off',top='off',labelbottom='off',labelsize=6)
plt.tick_params(axis='y',which='both',right='off',left='off',labelleft='off',labelsize=6)
#cbar = fig.colorbar(cax)
#plt.savefig("map_"+fn+".png", dpi=200)
plt.show()




