##################################################################################
#                  Pika: Phase field snow micro-structure model                  #
#                                                                                #
#                     (C) 2014 Battelle Energy Alliance, LLC                     #
#                              ALL RIGHTS RESERVED                               #
#                                                                                #
#                   Prepared by Battelle Energy Alliance, LLC                    #
#                      Under Contract No. DE-AC07-05ID14517                      #
#                      With the U. S. Department of Energy                       #
##################################################################################

'''***************************************
   * Generating Method of MFG-ed         *
   * Solutions applied to the Phase      *
   * Evolution eq. (33) in Kaempfer 2009 *
   *                                     *
   * Compile:                            *
   * python PhaseEvolutionMMS.py         *
   *                                     *
   ***************************************'''

#!/usr/bin/python

from sympy import *
from sympy.utilities.codegen import codegen
init_printing()

x = symbols('x')
y = symbols('y')
t = symbols('t')

#auxVariables
u = symbols('_u[_qp]')
T = symbols('_T[_qp]')
#variables
phi =t*((x-0.50)*(x-0.5)+(y-0.5)*(y-0.5) -.125)

print '\n'
print 'T =\n '
pprint(T)
print '\n'

print '\n'
print 'U =\n '
pprint(u)
print '\n'

print '\n'
print 'phi =\n '
pprint(phi)
print '\n'


#Interface thicknesss
w = symbols('w')
#phase relaxtation time constant
tau = symbols('tau')

#phase coupling constant related to capillary length
lam = symbols('lambda')

#Gas Constants
R_da = symbols('R_da')
R_v = symbols('R_v')

#Air
P_a = symbols('P_a')
rho_a = symbols('rho_a')

#Ice
rho_i = symbols('rho_i')

#Chemical equivalent
u_eq = symbols('u_eq')

#Simplifying Math terms
grad_phi = [diff(phi,x), diff(phi,y)]

lapl_phi = diff(grad_phi[0],x) + diff(grad_phi[1],y)

dPhi_dt = diff(phi,t)

#Equation 33:

#Phi time derivative
term1 = tau*dPhi_dt

#Square of the gradient
term2 = (w**2.0) * lapl_phi

#Double well potential
term3 = phi-(phi**3.0)

#Phase Potential
term4 = lam*(u-u_eq)*(1.0-phi*phi)**2.0

phase_evol =term1-term2-term3

#Generate the C/C++ version of the code.
print('\n')
[(c_name, c_code), (h_name, c_header)] = codegen(
     ("f", phase_evol), "C", "test", header=False, empty=False)
print(c_code)
print('\n')


#Generate C/C++ code for term 4
[(c_name, c_code), (h_name, c_header)] = codegen(
     ("f", -term4), "C", "test", header=False, empty=False)
print(c_code)
print('\n')
