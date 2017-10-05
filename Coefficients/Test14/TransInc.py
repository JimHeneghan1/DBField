#libraries *******************************************************************
from numpy import *
from scipy import *
from pylab import *

Ez = loadtxt('Ez900.txt', usecols=(1,), skiprows=1, unpack = True)

plot(Ez)
show()
