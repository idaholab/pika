'''***************************************
   * Checking the dimensional scaling    *
   * Execute:                            *
   * python                              *
   * SpatialScalingChecker.py            *
   *                                     *
   ***************************************'''
#!/usr/bin/python
                                 
from sympy import *
from math import *
init_printing()


#Given Values:

gamma =1.09e-1 # J /( m^2 ) 
a = 3.19e-10 # m
K = 1.38e-23 # J / K 
T = 263.15
m = 2.99e-26 # kg
alpha = 1e-3 #kg

rho_i = 918.9 # kg / m^3
rho_a = 1.341 # kg / m^3

w = 5e-6 #Interface thickness

k_i = 2.29 # W/(m*K) ==>> kg m /( s^3 * K )
k_a = 0.02 # W/(m*K)

C_i = 1.8e6 # J/( m^3 * K ) ==>> 1 /( K * S^2 * M)
C_a = 1.4e3 # J/( m^3 * K )

D_v =2.178e-5 # m^2 / s

K_fit = [-0.58653696e4, 0.2224103300e2, 0.13749042e-1, -0.34031775e-4, 0.26967687e-7, 0.6918651]

R_da = 286.9 # J /( Kg * K )
R_v = 461.5

P_a = 1.01325e5 # N / M^2  ==>> kg / m * s^2

a1 =(5.0/8.0) * (2.0**0.5)

#Calculated Values:

P_vs = exp(K_fit[0]*T**(-1) + K_fit[1]*T**0 + K_fit[2]*T**1 + K_fit[3]*T**2 + K_fit[4]*T**3 + K_fit[5]*log(T))
x_s = (R_da / R_v) * P_vs / (P_a - P_vs)
rho_vs = rho_a * x_s

d_o = gamma*(a**3.0)/(K*T)   # m
d_o_prime = (rho_vs/rho_i)*d_o

beta =(1.0/alpha) * ((2.0*pi*m/K*T)**0.5) # s / m
beta_prime = (rho_vs/rho_i) * beta # s / m

lam = (a1 * w/d_o_prime)  # Unitless

tau = beta*lam*w/a1

scaled_values= []
values= []
scaled_names= []
convert_meters = 1000  # meters to mm

#Outputs
values.append(k_i)
scaled_values.append( k_i * (convert_meters))
scaled_names.append('K_i')

values.append(k_a)
scaled_values.append( k_a * (convert_meters))
scaled_names.append('K_a')

values.append(C_i)
scaled_values.append( C_i * (1.0/convert_meters))
scaled_names.append('C_i')

values.append(C_a)
scaled_values.append( C_a * (1.0/convert_meters))
scaled_names.append('C_a')

values.append(D_v)
scaled_values.append( D_v * (convert_meters**2.0))
scaled_names.append('D_v')

values.append(d_o)
scaled_values.append( d_o * (convert_meters))
scaled_names.append('d_o')

values.append(d_o_prime)
scaled_values.append( d_o_prime * (convert_meters))
scaled_names.append('d_o_prime')

values.append(beta)
scaled_values.append( beta * (1.0/convert_meters))
scaled_names.append('beta')

values.append(beta_prime)
scaled_values.append( beta_prime * (1.0/convert_meters))
scaled_names.append('beta_prime')

values.append(w)
scaled_values.append( w * (convert_meters))
scaled_names.append('w')

values.append(lam)
scaled_values.append( lam )
scaled_names.append('lambda')

values.append(tau)
scaled_values.append( tau )
scaled_names.append('tau')

values.append(rho_vs/rho_i)
scaled_values.append( rho_vs/rho_i )
scaled_names.append('density ratio')


print 'Original Values', ' ' , 'Values in MM'
for i in range(len(scaled_values)):
  print scaled_names[i], ' = ' , values[i], ' ', scaled_values[i] , '\n'





