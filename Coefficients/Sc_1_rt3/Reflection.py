#Lbraries *******************************************************************
from numpy import *
from scipy import *
from pylab import *

E0 = loadtxt('Ez900.txt', usecols=(1,), skiprows= 1, unpack =True)

M = len(E0)

for i in range(0, 5300):
        Ei = E0[:5300]
for i in range(5300, len(E0)):
        Ei =append(Ei,[0])

Er = E0[5300:8000]
for i in range (0, 5300):
        Er =insert(Er,1, [0])
for i in range (8000, len(E0)):
        Er = append(Er, [0])
Ei_fft = ifft(Ei, M-1)
Er_fft = ifft(Er, M-1)

plot(Ei)
show()
plot(Er)
show()

print len(Ei)
print len(Er)

dt =1.171191356e-17
fs = 1/dt
time = arange(0,M)*dt
f = arange(1,M)*fs/M
wavelength = ((3e8/f)*1e9)
lamb = transpose(wavelength)

plot(wavelength, (abs(Er_fft/Ei_fft)**2))
ylim(0,0.04)
xlim(500,1000)
show()
