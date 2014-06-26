'''***************************************
   * Checking the values produced by the *
   * U_eq function                       *
   * Compile:                            *
   * python                              *
   * PhaseTransitionChecker.py           *
   *                                     *
   ***************************************'''
#!/usr/bin/python
                                 
from sympy import *
from math import *
init_printing()

#User Inputs
temperature =[ 260, 261]

#Constants
rho_a =1.341 #kg/m^3 
rho_i =918.9 #kg/m^3 
T_ref =263.15

R_da = 286.9 
R_v = 461.5 
P_a = 1.01325e5 
K_fit = [-0.58653696e4, 0.2224103300e2, 0.13749042e-1, -0.34031775e-4, 0.26967687e-7, 0.6918651] 

a = 3.19e-10
alpha =  
 
# Eq. (2) 
P_vs = exp(K_fit[0]*T_ref**(-1.0) + K_fit[1]*T_ref**0.0 + K_fit[2]*T_ref**1.0 + K_fit[3]*T_ref**2.0 + K_fit[4]*T_ref**3.0 + K_fit[5]*log(T_ref)) 

# Eq. (1) 
x_s = (R_da / R_v) * P_vs / (P_a - P_vs) 
rho_vs_T0 = rho_a*x_s;


#Calculate the Equilibrium Concentration
print '-----U_eq------\n'
print 'Temp.   U_eq'
for T in temperature:
  # Eq. (2) 
  P_vs = exp(K_fit[0]*T**(-1.0) + K_fit[1]*T**0.0 + K_fit[2]*T**1.0 + K_fit[3]*T**2.0 + K_fit[4]*T**3.0 + K_fit[5]*log(T)) 
  # Eq. (1) 
  x_s = (R_da / R_v) * P_vs / (P_a - P_vs) 
  rho_vs_T = x_s*rho_a
  U_eq = (rho_vs_T-rho_vs_T0)/rho_i


  d_o_prime = (rho_vs/rho_i) * gamma*(a**3.0)/(k*T)
  beta_o_prime = (1.0/alpha)*((2*pi*m/(k*T))**0.5)
  print T,' ', U_eq
