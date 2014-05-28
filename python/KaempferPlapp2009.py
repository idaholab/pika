'''***************************************
   * Calculator for Phase Field Modeling *
   * of Dry Snow Metamorphosis           *
   * (Kaempfer 2009)                     *
   *                                     *
   * Compile:                            *
   * python KaempferPlapp2009.py         *
   *                                     *
   ***************************************'''
'''
*******************************************
             NOMENCLATURE

R_da = gas constant for dry air
R_v = gas constant for water vapor

P_a = atmospheric pressure
P_vs = saturated vapor pressure over ice

K_fit = fitting coefficients
T = Temperature
X_s = humidity ratio
*******************************************
'''

#!/usr/bin/python
                                 
from sympy import *
init_printing()

T = symbols('T')

R_da = 286.9
R_v = 461.5
P_a = 1.01325e5
K_fit = [-0.5865e4, 0.2224e2, 0.1375e-1, -0.3403e-4, 0.2697e-7, 0.6918]
rho_a= 1.341 #[kg*m^-3]
#EQN 2 
P_vs = exp(K_fit[0]*T**(-1) + K_fit[1]*T**0 + K_fit[2]*T**1 + K_fit[3]*T**2 + K_fit[4]*T**3+ K_fit[5]*ln(T))

pprint(P_vs)
#Example of evaluation
#print P_vs.subs(T,273).evalf()

#EQN 1
X_s=(R_da/R_v)*(P_vs)/(P_a-P_vs)
pprint(X_s)

#EQN 3
rho_vs=rho_a*X_s
pprint(rho_vs)

#EQN 4
